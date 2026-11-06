#pragma once

#include "i76/color.h"
#include "i76/terrain_scene.h"
#include "i76/texture.h"

#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>

// An owned, renderer-neutral diagnostic surface that pairs a real mission's
// terrain with WRLD-selected indexed colors and one explicitly named texture.
// It is not yet the game's automatic TMT/MAP terrain-material selector.
struct i76_retail_scene {
    i76_terrain_scene terrain{};
    std::string palette_name{};
    std::string luminance_name{};
    std::string blend_name{};
    i76_indexed_texture sample_texture{};
    i76_indexed_color_tables colors{};
};

struct i76_prepared_retail_scene {
    std::unique_ptr<i76_retail_scene> scene{};
};

struct i76_active_retail_scene {
    std::unique_ptr<i76_retail_scene> scene{};
};

enum class i76_retail_scene_result : std::uint8_t {
    ok = 0,
    not_initialized,
    invalid_argument,
    busy,
    missing_mission,
    missing_world,
    unsupported_world,
    missing_terrain,
    invalid_terrain,
    invalid_color,
    invalid_texture,
    missing_resource,
    resource_error,
    not_prepared,
    not_loaded,
};

struct i76_retail_scene_error {
    i76_retail_scene_result code{};
    std::uint32_t offset{};
};

// These are independently supplied coordinates, NOT derived terrain UVs.
// Output includes both original 16-bit terrain attributes and indexed pixels.
struct i76_retail_surface_sample {
    i76_terrain_sample terrain{};
    std::uint8_t texel{};
    std::uint8_t shaded{};
    std::uint8_t composite{};
};

// Prepare all selected resources as one transaction. A failed call retains
// any previously prepared scene, and no resource lease escapes the function.
// WREV-9 WRLD resource strings choose ACT/LUM/TBL; the caller chooses VQM.
i76_retail_scene_result i76_retail_scene_prepare(
    i76_resource_store& resources,
    std::string_view mission_name,
    std::string_view sample_texture,
    i76_prepared_retail_scene& prepared,
    i76_retail_scene_error& error);

i76_retail_scene_result i76_retail_scene_activate(
    i76_prepared_retail_scene& prepared,
    i76_active_retail_scene& active) noexcept;

i76_retail_scene_result i76_retail_scene_discard(
    i76_prepared_retail_scene& prepared) noexcept;

i76_retail_scene_result i76_retail_scene_unload(
    i76_active_retail_scene& active) noexcept;

// Sample an explicit source-cell/page ordinal and caller-provided 16.16 UV.
// Requested shade and composition require the corresponding supplied table.
// A failure preserves the result argument.
bool i76_retail_scene_sample(const i76_retail_scene& scene,
                             std::size_t cell_index,
                             std::size_t sample_index,
                             std::int32_t fixed_u,
                             std::int32_t fixed_v,
                             std::uint32_t shade_accumulator,
                             std::uint8_t destination,
                             bool apply_shade,
                             bool apply_composite,
                             i76_retail_surface_sample& output) noexcept;

const char* i76_retail_scene_result_name(
    i76_retail_scene_result result) noexcept;
