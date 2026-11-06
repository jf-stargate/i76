#include "i76/retail_scene.h"

#include "i76/bwd2.h"

#include <array>
#include <cstring>
#include <span>
#include <utility>

// -----------------------------------------------------------------------------
// Record one typed scene error without changing the caller's prepared state.
// -----------------------------------------------------------------------------
static i76_retail_scene_result scene_fail(i76_retail_scene_error& error,
                                          i76_retail_scene_result code,
                                          std::uint32_t offset) noexcept
{
    error.code = code;
    error.offset = offset;
    return code;
}

// -----------------------------------------------------------------------------
// Identify a parsed FourCC without interpreting retail payload structures.
// -----------------------------------------------------------------------------
static bool scene_tag(const i76_bwd2_chunk& chunk,
                      const char* tag) noexcept
{
    return std::strcmp(chunk.tag, tag) == 0;
}

// -----------------------------------------------------------------------------
// Extract a bounded, ASCII resource name from a 13-byte WREV-9 name slot.
// -----------------------------------------------------------------------------
static bool scene_name(std::span<const std::uint8_t> payload,
                       std::size_t start,
                       bool required,
                       std::string& output)
{
    std::size_t end = start;
    std::string normalized = {};

    if (start + 13U > payload.size()) {
        return false;
    }
    while (end < start + 13U
           && payload[end] != 0U) {
        if (payload[end] < 33U
            || payload[end] > 126U) {
            return false;
        }
        ++end;
    }
    if (end == start + 13U) {
        return false;
    }
    if (end == start) {
        if (required) {
            return false;
        }
        output.clear();
        return true;
    }
    const std::string_view raw(
        reinterpret_cast<const char*>(payload.data() + start),
        end - start);
    if (i76_resource_normalize_name(raw, normalized) !=
        i76_resource_result::ok) {
        return false;
    }
    output = std::move(normalized);
    return true;
}

// -----------------------------------------------------------------------------
// Find the WDEF child WRLD and its sibling WREV, requiring the proven layout.
// -----------------------------------------------------------------------------
static i76_retail_scene_result scene_world_names(
    std::span<const std::uint8_t> bytes,
    const i76_bwd2_document& document,
    std::array<std::string, 3U>& output,
    i76_retail_scene_error& error)
{
    const i76_bwd2_chunk* world = nullptr;
    const i76_bwd2_chunk* revision = nullptr;
    std::uint32_t parent_id = 0U;
    std::uint32_t world_count = 0U;
    std::uint32_t revision_count = 0U;
    std::array<std::string, 3U> candidate = {};

    for (std::size_t index = 0U; index < document.chunks.size(); ++index) {
        const i76_bwd2_chunk& chunk = document.chunks[index];
        if (chunk.parent == 0U
            && scene_tag(chunk, "WDEF")) {
            if (parent_id != 0U) {
                return scene_fail(error,
                                  i76_retail_scene_result::unsupported_world,
                                  chunk.offset);
            }
            parent_id = static_cast<std::uint32_t>(index + 1U);
        }
    }
    if (parent_id == 0U) {
        return scene_fail(error, i76_retail_scene_result::missing_world, 0U);
    }
    for (const i76_bwd2_chunk& chunk : document.chunks) {
        if (chunk.parent != parent_id) {
            continue;
        }
        if (scene_tag(chunk, "WRLD")) {
            world = &chunk;
            ++world_count;
        } else if (scene_tag(chunk, "WREV")) {
            revision = &chunk;
            ++revision_count;
        }
    }
    if (world_count == 0U) {
        return scene_fail(error, i76_retail_scene_result::missing_world, 0U);
    }
    if (world_count != 1U
        || revision_count != 1U
        || revision == nullptr
        || !revision->has_revision
        || revision->revision != 9U
        || world->payload_size != 331U) {
        return scene_fail(error,
                          i76_retail_scene_result::unsupported_world,
                          world->offset);
    }
    const std::span<const std::uint8_t> payload =
        bytes.subspan(world->payload_offset, world->payload_size);
    constexpr std::array<std::size_t, 3U> offsets = {
        0x1eU, 0x2bU, 0x38U
    };

    for (std::size_t index = 0U; index < offsets.size(); ++index) {
        if (!scene_name(payload, offsets[index], index == 0U,
                        candidate[index])) {
            return scene_fail(error, i76_retail_scene_result::invalid_color,
                              world->payload_offset +
                              static_cast<std::uint32_t>(offsets[index]));
        }
    }
    output = std::move(candidate);
    return i76_retail_scene_result::ok;
}

// -----------------------------------------------------------------------------
// Read only mission WRLD color names, releasing the mission resource lease.
// -----------------------------------------------------------------------------
static i76_retail_scene_result scene_read_world(
    i76_resource_store& resources,
    std::string_view mission_name,
    std::array<std::string, 3U>& names,
    i76_retail_scene_error& error)
{
    i76_resource_handle lease = {};
    const i76_resource_entry* entry = nullptr;
    i76_bwd2_document document = {};
    i76_bwd2_error bwd_error = {};
    i76_retail_scene_result result = i76_retail_scene_result::ok;
    const i76_resource_result acquired =
        i76_resource_acquire(resources, mission_name, lease);

    if (acquired != i76_resource_result::ok) {
        return scene_fail(error,
                          acquired == i76_resource_result::not_found ?
                              i76_retail_scene_result::missing_mission :
                              i76_retail_scene_result::resource_error, 0U);
    }
    try {
        entry = i76_resource_lookup(resources, lease);
        if (entry == nullptr) {
            result = scene_fail(error,
                                i76_retail_scene_result::resource_error, 0U);
        } else if (i76_bwd2_parse(entry->bytes, document, bwd_error) !=
                   i76_bwd2_result::ok) {
            result = scene_fail(error,
                                i76_retail_scene_result::unsupported_world,
                                bwd_error.offset);
        } else {
            result = scene_world_names(entry->bytes, document, names, error);
        }
    } catch (...) {
        i76_resource_release(resources, lease);
        throw;
    }
    i76_resource_release(resources, lease);
    return result;
}

// -----------------------------------------------------------------------------
// Translate terrain preparation failures into the combined scene vocabulary.
// -----------------------------------------------------------------------------
static i76_retail_scene_result scene_terrain_error(
    i76_terrain_result code) noexcept
{
    switch (code) {
    case i76_terrain_result::not_initialized:
        return i76_retail_scene_result::not_initialized;
    case i76_terrain_result::invalid_argument:
        return i76_retail_scene_result::invalid_argument;
    case i76_terrain_result::missing_mission:
        return i76_retail_scene_result::missing_mission;
    case i76_terrain_result::missing_terrain:
        return i76_retail_scene_result::missing_terrain;
    case i76_terrain_result::resource_error:
        return i76_retail_scene_result::resource_error;
    default:
        return i76_retail_scene_result::invalid_terrain;
    }
}

// -----------------------------------------------------------------------------
// Prepare an owned terrain/color/texture scene without committing active data.
// -----------------------------------------------------------------------------
i76_retail_scene_result i76_retail_scene_prepare(
    i76_resource_store& resources,
    std::string_view mission_name,
    std::string_view sample_texture,
    i76_prepared_retail_scene& prepared,
    i76_retail_scene_error& error)
{
    std::array<std::string, 3U> names = {};
    i76_prepared_terrain terrain = {};
    i76_terrain_error terrain_error = {};
    i76_color_result color_error = i76_color_result::ok;
    i76_texture_result texture_error = i76_texture_result::ok;
    i76_texture_error texture_details = {};
    i76_retail_scene_result result = i76_retail_scene_result::ok;
    std::unique_ptr<i76_retail_scene> candidate = {};

    error = {};
    if (!resources.initialized) {
        return scene_fail(error, i76_retail_scene_result::not_initialized, 0U);
    }
    if (prepared.scene != nullptr) {
        return scene_fail(error, i76_retail_scene_result::busy, 0U);
    }
    if (sample_texture.empty()) {
        return scene_fail(error, i76_retail_scene_result::invalid_argument,
                          0U);
    }
    result = scene_read_world(resources, mission_name, names, error);
    if (result != i76_retail_scene_result::ok) {
        return result;
    }
    const i76_terrain_result terrain_status =
        i76_terrain_prepare(resources, mission_name, terrain, terrain_error);
    if (terrain_status != i76_terrain_result::ok) {
        return scene_fail(error, scene_terrain_error(terrain_status),
                          terrain_error.offset);
    }

    candidate = std::make_unique<i76_retail_scene>();
    candidate->terrain = std::move(terrain.scene);
    candidate->palette_name = names[0];
    candidate->luminance_name = names[1];
    candidate->blend_name = names[2];
    color_error = i76_color_read(resources, names[0], names[1], names[2],
                                 candidate->colors);
    if (color_error != i76_color_result::ok) {
        result = color_error == i76_color_result::missing_resource ?
            i76_retail_scene_result::missing_resource :
            color_error == i76_color_result::resource_error ?
                i76_retail_scene_result::resource_error :
                i76_retail_scene_result::invalid_color;
        return scene_fail(error, result, 0U);
    }
    texture_error = i76_texture_read(resources, sample_texture,
                                     candidate->sample_texture,
                                     texture_details);
    if (texture_error != i76_texture_result::ok) {
        result = texture_error == i76_texture_result::invalid_argument ?
            i76_retail_scene_result::invalid_argument :
            (texture_error == i76_texture_result::missing_vqm
             || texture_error == i76_texture_result::missing_cbk) ?
                i76_retail_scene_result::missing_resource :
            texture_error == i76_texture_result::resource_error ?
                i76_retail_scene_result::resource_error :
                i76_retail_scene_result::invalid_texture;
        return scene_fail(error, result,
                          static_cast<std::uint32_t>(texture_details.offset));
    }
    prepared.scene = std::move(candidate);
    return i76_retail_scene_result::ok;
}

// -----------------------------------------------------------------------------
// Atomically move a completed diagnostic scene into its active runtime slot.
// -----------------------------------------------------------------------------
i76_retail_scene_result i76_retail_scene_activate(
    i76_prepared_retail_scene& prepared,
    i76_active_retail_scene& active) noexcept
{
    if (prepared.scene == nullptr) {
        return i76_retail_scene_result::not_prepared;
    }
    active.scene = std::move(prepared.scene);
    return i76_retail_scene_result::ok;
}

// -----------------------------------------------------------------------------
// Discard only the pending scene without changing the current active scene.
// -----------------------------------------------------------------------------
i76_retail_scene_result i76_retail_scene_discard(
    i76_prepared_retail_scene& prepared) noexcept
{
    if (prepared.scene == nullptr) {
        return i76_retail_scene_result::not_prepared;
    }
    prepared.scene.reset();
    return i76_retail_scene_result::ok;
}

// -----------------------------------------------------------------------------
// Release the active scene and its owned terrain/texture/palette allocations.
// -----------------------------------------------------------------------------
i76_retail_scene_result i76_retail_scene_unload(
    i76_active_retail_scene& active) noexcept
{
    if (active.scene == nullptr) {
        return i76_retail_scene_result::not_loaded;
    }
    active.scene.reset();
    return i76_retail_scene_result::ok;
}

// -----------------------------------------------------------------------------
// Sample terrain and explicit 16.16 texture coordinates with optional remaps.
// -----------------------------------------------------------------------------
bool i76_retail_scene_sample(const i76_retail_scene& scene,
                             std::size_t cell_index,
                             std::size_t sample_index,
                             std::int32_t fixed_u,
                             std::int32_t fixed_v,
                             std::uint32_t shade_accumulator,
                             std::uint8_t destination,
                             bool apply_shade,
                             bool apply_composite,
                             i76_retail_surface_sample& output) noexcept
{
    i76_retail_surface_sample candidate = {};

    if (!i76_terrain_sample_at(scene.terrain, cell_index,
                               sample_index, candidate.terrain)
        || !i76_texture_sample(scene.sample_texture, fixed_u, fixed_v,
                               candidate.texel)) {
        return false;
    }
    candidate.shaded = candidate.texel;
    if (apply_shade
        && !i76_color_shade(scene.colors, candidate.texel,
                            shade_accumulator, candidate.shaded)) {
        return false;
    }
    candidate.composite = candidate.shaded;
    if (apply_composite
        && !i76_color_compose(scene.colors, candidate.shaded,
                              destination, candidate.composite)) {
        return false;
    }
    output = candidate;
    return true;
}

// -----------------------------------------------------------------------------
// Name every combined-scene loading and lifecycle status for diagnostics.
// -----------------------------------------------------------------------------
const char* i76_retail_scene_result_name(
    i76_retail_scene_result result) noexcept
{
    switch (result) {
    case i76_retail_scene_result::ok: return "ok";
    case i76_retail_scene_result::not_initialized:
        return "not initialized";
    case i76_retail_scene_result::invalid_argument:
        return "invalid argument";
    case i76_retail_scene_result::busy: return "scene already prepared";
    case i76_retail_scene_result::missing_mission: return "missing mission";
    case i76_retail_scene_result::missing_world: return "missing WRLD";
    case i76_retail_scene_result::unsupported_world:
        return "unsupported WRLD layout";
    case i76_retail_scene_result::missing_terrain: return "missing terrain";
    case i76_retail_scene_result::invalid_terrain: return "invalid terrain";
    case i76_retail_scene_result::invalid_color: return "invalid color data";
    case i76_retail_scene_result::invalid_texture:
        return "invalid indexed texture";
    case i76_retail_scene_result::missing_resource:
        return "missing color/texture resource";
    case i76_retail_scene_result::resource_error: return "resource error";
    case i76_retail_scene_result::not_prepared: return "scene not prepared";
    case i76_retail_scene_result::not_loaded: return "scene not loaded";
    }
    return "unknown scene result";
}
