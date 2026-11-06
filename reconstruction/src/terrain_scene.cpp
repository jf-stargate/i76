#include "i76/terrain_scene.h"

#include <utility>

// -----------------------------------------------------------------------------
// Attach a typed failure and source offset to the terrain preparation result.
// -----------------------------------------------------------------------------
static i76_terrain_result terrain_fail(i76_terrain_error& error,
                                      i76_terrain_result result,
                                      std::uint32_t offset) noexcept
{
    error.code = result;
    error.offset = offset;
    return result;
}

// -----------------------------------------------------------------------------
// Translate an existing retail mission decode failure into terrain status.
// -----------------------------------------------------------------------------
static i76_terrain_result mission_failure(i76_retail_result result) noexcept
{
    if (result == i76_retail_result::not_initialized) {
        return i76_terrain_result::not_initialized;
    }
    if (result == i76_retail_result::resource_not_found) {
        return i76_terrain_result::missing_mission;
    }
    if (result == i76_retail_result::invalid_argument) {
        return i76_terrain_result::invalid_argument;
    }
    if (result == i76_retail_result::resource_error) {
        return i76_terrain_result::resource_error;
    }
    return i76_terrain_result::invalid_terrain;
}

// -----------------------------------------------------------------------------
// Load a validated retail ZMAP/ZONE/TER snapshot into a pending scene.
// -----------------------------------------------------------------------------
i76_terrain_result i76_terrain_prepare(i76_resource_store& resources,
                                       std::string_view mission_name,
                                       i76_prepared_terrain& prepared,
                                       i76_terrain_error& error)
{
    i76_retail_mission_definition mission = {};
    i76_retail_error mission_error = {};
    i76_retail_result decode_status = i76_retail_result::ok;
    i76_resource_result resource_status = i76_resource_result::ok;
    i76_resource_handle lease = {};
    const i76_resource_entry* entry = nullptr;
    i76_prepared_terrain candidate = {};
    std::size_t expected_bytes = 0U;
    std::size_t index = 0U;

    error = {};
    if (!resources.initialized) {
        return terrain_fail(error, i76_terrain_result::not_initialized, 0U);
    }
    if (prepared.ready) {
        return terrain_fail(error, i76_terrain_result::busy, 0U);
    }
    decode_status = i76_retail_mission_read(resources, mission_name, mission,
                                             mission_error);
    if (decode_status != i76_retail_result::ok) {
        return terrain_fail(error, mission_failure(decode_status),
                            mission_error.offset);
    }
    if (!mission.terrain.has_zmap
        || !mission.terrain.has_zone) {
        return terrain_fail(error, i76_terrain_result::missing_terrain, 0U);
    }
    expected_bytes = static_cast<std::size_t>(mission.terrain.active_pages)
                     * i76_retail_terrain_page_bytes;
    resource_status = i76_resource_acquire(
        resources, mission.terrain.resource_name, lease);
    if (resource_status != i76_resource_result::ok) {
        return terrain_fail(error,
                            resource_status == i76_resource_result::not_found ?
                                i76_terrain_result::missing_terrain :
                                i76_terrain_result::resource_error,
                            mission.terrain.zone_offset);
    }

    try {
        entry = i76_resource_lookup(resources, lease);
        if (entry == nullptr) {
            resource_status = i76_resource_result::io_error;
        } else if (entry->bytes.size() != expected_bytes) {
            resource_status = i76_resource_result::too_large;
        } else {
            candidate.scene.mission_name = mission.name;
            candidate.scene.terrain_name = mission.terrain.resource_name;
            candidate.scene.page_count = mission.terrain.active_pages;
            candidate.scene.mapped_cells = mission.terrain.mapped_cells;
            candidate.scene.referenced_pages = mission.terrain.referenced_pages;
            candidate.scene.cell_pages = mission.terrain.page_indices;
            candidate.scene.packed_samples.resize(expected_bytes / 2U);
            for (index = 0U; index < expected_bytes; index += 2U) {
                candidate.scene.packed_samples[index / 2U] =
                    static_cast<std::uint16_t>(entry->bytes[index])
                    | (static_cast<std::uint16_t>(entry->bytes[index + 1U])
                       << 8U);
            }
            candidate.ready = true;
        }
    } catch (...) {
        i76_resource_release(resources, lease);
        throw;
    }
    i76_resource_release(resources, lease);
    if (resource_status == i76_resource_result::io_error) {
        return terrain_fail(error, i76_terrain_result::resource_error, 0U);
    }
    if (resource_status == i76_resource_result::too_large) {
        return terrain_fail(error, i76_terrain_result::invalid_terrain, 0U);
    }
    prepared = std::move(candidate);
    return i76_terrain_result::ok;
}

// -----------------------------------------------------------------------------
// Commit only fully prepared terrain data, preserving active state on failure.
// -----------------------------------------------------------------------------
i76_terrain_result i76_terrain_activate(i76_prepared_terrain& prepared,
                                        i76_active_terrain& active) noexcept
{
    if (!prepared.ready) {
        return i76_terrain_result::not_prepared;
    }
    active.scene = std::move(prepared.scene);
    active.loaded = true;
    prepared = {};
    return i76_terrain_result::ok;
}

// -----------------------------------------------------------------------------
// Discard prepared terrain without changing an already active scene.
// -----------------------------------------------------------------------------
i76_terrain_result i76_terrain_discard(i76_prepared_terrain& prepared) noexcept
{
    if (!prepared.ready) {
        return i76_terrain_result::not_prepared;
    }
    prepared = {};
    return i76_terrain_result::ok;
}

// -----------------------------------------------------------------------------
// Unload owned terrain pages independently of world and resource mounts.
// -----------------------------------------------------------------------------
i76_terrain_result i76_terrain_unload(i76_active_terrain& active) noexcept
{
    if (!active.loaded) {
        return i76_terrain_result::not_loaded;
    }
    active = {};
    return i76_terrain_result::ok;
}

// -----------------------------------------------------------------------------
// Resolve a serialized page reference to bounded packed terrain attributes.
// -----------------------------------------------------------------------------
bool i76_terrain_sample_at(const i76_terrain_scene& scene,
                           std::size_t cell_index,
                           std::size_t sample_index,
                           i76_terrain_sample& output) noexcept
{
    std::size_t page_index = 0U;
    std::size_t absolute_index = 0U;
    std::uint16_t raw = 0U;
    i76_terrain_sample decoded = {};

    if (cell_index >= scene.cell_pages.size()
        || sample_index >= i76_retail_terrain_page_samples) {
        return false;
    }
    page_index = scene.cell_pages[cell_index];
    if (page_index == 0xffU
        || page_index >= scene.page_count) {
        return false;
    }
    absolute_index = page_index * i76_retail_terrain_page_samples
                     + sample_index;
    if (absolute_index >= scene.packed_samples.size()) {
        return false;
    }
    raw = scene.packed_samples[absolute_index];
    decoded.height = raw & 0x0fffU;
    decoded.surface_flag = (raw & 0x1000U) != 0U;
    decoded.surface_class = static_cast<std::uint8_t>((raw >> 13U) & 7U);
    output = decoded;
    return true;
}

// -----------------------------------------------------------------------------
// Return a stable diagnostic description of each terrain lifecycle result.
// -----------------------------------------------------------------------------
const char* i76_terrain_result_name(i76_terrain_result result) noexcept
{
    switch (result) {
    case i76_terrain_result::ok: return "ok";
    case i76_terrain_result::not_initialized: return "not initialized";
    case i76_terrain_result::invalid_argument: return "invalid mission name";
    case i76_terrain_result::busy: return "terrain already prepared";
    case i76_terrain_result::missing_mission: return "mission not found";
    case i76_terrain_result::missing_terrain: return "missing ZMAP/ZONE/TER";
    case i76_terrain_result::invalid_terrain: return "invalid TER size";
    case i76_terrain_result::resource_error: return "resource error";
    case i76_terrain_result::not_prepared: return "terrain not prepared";
    case i76_terrain_result::not_loaded: return "terrain not loaded";
    }
    return "unknown terrain result";
}
