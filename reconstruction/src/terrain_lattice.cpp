#include "i76/terrain_lattice.h"

#include <cstddef>
#include <cstdint>

// -----------------------------------------------------------------------------
// Validate the owned TER allocation without reading untrusted page ordinals.
// -----------------------------------------------------------------------------
static bool lattice_scene_valid(const i76_terrain_scene& scene) noexcept
{
    const std::size_t expected =
        static_cast<std::size_t>(scene.page_count)
        * i76_retail_terrain_page_samples;

    return scene.packed_samples.size() == expected;
}

// -----------------------------------------------------------------------------
// Resolve signed global lattice coordinates through the shifted pointer grid.
// -----------------------------------------------------------------------------
i76_terrain_lattice_result i76_terrain_lattice_at(
    const i76_terrain_scene& scene,
    std::int32_t global_x,
    std::int32_t global_z,
    i76_terrain_lattice_sample& output) noexcept
{
    constexpr std::int64_t shift = 24 * 128;
    constexpr std::int64_t grid_side = 128 * 128;
    constexpr std::int32_t page_side = 128;
    constexpr std::int32_t zmap_first = 24;
    constexpr std::int32_t zmap_last = 104;
    const std::int64_t shifted_x =
        static_cast<std::int64_t>(global_x) + shift;
    const std::int64_t shifted_z =
        static_cast<std::int64_t>(global_z) + shift;
    i76_terrain_lattice_sample candidate = {};

    if (shifted_x < 0 || shifted_z < 0
        || shifted_x >= grid_side || shifted_z >= grid_side) {
        return i76_terrain_lattice_result::invalid_coordinate;
    }
    if (!lattice_scene_valid(scene)) {
        return i76_terrain_lattice_result::invalid_scene;
    }

    const std::int32_t runtime_x =
        static_cast<std::int32_t>(shifted_x / page_side);
    const std::int32_t runtime_z =
        static_cast<std::int32_t>(shifted_z / page_side);
    const std::int32_t local_x =
        static_cast<std::int32_t>(shifted_x % page_side);
    const std::int32_t local_z =
        static_cast<std::int32_t>(shifted_z % page_side);
    std::uint8_t page_ordinal = 0xffU;

    candidate.lattice_x = global_x;
    candidate.lattice_z = global_z;
    candidate.runtime_col = static_cast<std::uint8_t>(runtime_x);
    candidate.runtime_row = static_cast<std::uint8_t>(runtime_z);
    candidate.local_x = static_cast<std::uint8_t>(local_x);
    candidate.local_z = static_cast<std::uint8_t>(local_z);

    if (runtime_x >= zmap_first && runtime_x < zmap_last
        && runtime_z >= zmap_first && runtime_z < zmap_last) {
        const std::int32_t source_x = runtime_x - zmap_first;
        const std::int32_t source_z = runtime_z - zmap_first;
        const std::size_t cell_index =
            static_cast<std::size_t>(source_z * 80 + source_x);

        candidate.source_col = static_cast<std::int16_t>(source_x);
        candidate.source_row = static_cast<std::int16_t>(source_z);
        page_ordinal = scene.cell_pages[cell_index];
    }

    if (page_ordinal == 0xffU) {
        output = candidate;
        return i76_terrain_lattice_result::default_page;
    }
    if (page_ordinal >= scene.page_count) {
        return i76_terrain_lattice_result::invalid_scene;
    }

    const std::size_t sample_index =
        static_cast<std::size_t>(local_z * page_side + local_x);
    const std::size_t absolute_index =
        static_cast<std::size_t>(page_ordinal)
        * i76_retail_terrain_page_samples + sample_index;

    if (absolute_index >= scene.packed_samples.size()) {
        return i76_terrain_lattice_result::invalid_scene;
    }
    const std::uint16_t word = scene.packed_samples[absolute_index];

    candidate.page_ordinal = page_ordinal;
    candidate.packed_word = word;
    candidate.attributes.height = word & 0x0fffU;
    candidate.attributes.surface_flag = (word & 0x1000U) != 0U;
    candidate.attributes.surface_class =
        static_cast<std::uint8_t>((word >> 13U) & 7U);
    output = candidate;
    return i76_terrain_lattice_result::ok;
}

// -----------------------------------------------------------------------------
// Convert one valid global sample to documented conceptual world coordinates.
// -----------------------------------------------------------------------------
i76_terrain_lattice_result i76_terrain_lattice_position_at(
    const i76_terrain_scene& scene,
    std::int32_t global_x,
    std::int32_t global_z,
    i76_terrain_lattice_position& output) noexcept
{
    i76_terrain_lattice_sample sample = {};
    const i76_terrain_lattice_result status =
        i76_terrain_lattice_at(scene, global_x, global_z, sample);

    if (status != i76_terrain_lattice_result::ok
        && status != i76_terrain_lattice_result::default_page) {
        return status;
    }
    i76_terrain_lattice_position candidate = {};

    candidate.x = static_cast<double>(global_x) * 5.0;
    candidate.y = static_cast<double>(sample.attributes.height)
                  * static_cast<double>(0.1F);
    candidate.z = static_cast<double>(global_z) * 5.0;
    candidate.source = sample;
    output = candidate;
    return status;
}

// -----------------------------------------------------------------------------
// Fetch each of the four independently addressed global lattice cell corners.
// -----------------------------------------------------------------------------
i76_terrain_lattice_result i76_terrain_lattice_quad_at(
    const i76_terrain_scene& scene,
    std::int32_t global_x,
    std::int32_t global_z,
    i76_terrain_lattice_quad& output) noexcept
{
    constexpr std::int64_t minimum = -3072;
    constexpr std::int64_t last_cell = 13310;
    const std::int64_t x = global_x;
    const std::int64_t z = global_z;
    i76_terrain_lattice_quad candidate = {};

    if (x < minimum || z < minimum
        || x > last_cell || z > last_cell) {
        return i76_terrain_lattice_result::invalid_coordinate;
    }

    constexpr std::int32_t deltas[4U][2U] = {
        {0, 0}, {1, 0}, {0, 1}, {1, 1}
    };
    for (std::size_t index = 0U; index < 4U; ++index) {
        const i76_terrain_lattice_result status = i76_terrain_lattice_at(
            scene, global_x + deltas[index][0U],
            global_z + deltas[index][1U], candidate.corners[index]);

        if (status == i76_terrain_lattice_result::invalid_coordinate
            || status == i76_terrain_lattice_result::invalid_scene) {
            return status;
        }
        if (status == i76_terrain_lattice_result::default_page) {
            candidate.includes_default = true;
        }
    }
    output = candidate;
    return candidate.includes_default ?
        i76_terrain_lattice_result::default_page :
        i76_terrain_lattice_result::ok;
}

// -----------------------------------------------------------------------------
// Provide stable diagnostics without conflating valid defaults with failures.
// -----------------------------------------------------------------------------
const char* i76_terrain_lattice_result_name(
    i76_terrain_lattice_result result) noexcept
{
    switch (result) {
    case i76_terrain_lattice_result::ok: return "ok";
    case i76_terrain_lattice_result::default_page: return "default page";
    case i76_terrain_lattice_result::invalid_coordinate:
        return "invalid coordinate";
    case i76_terrain_lattice_result::invalid_scene: return "invalid scene";
    }
    return "unknown lattice result";
}
