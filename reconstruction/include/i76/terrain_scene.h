#pragma once

#include "i76/retail_mission.h"
#include "i76/resource.h"

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

// Renderer-neutral, owned terrain pages. Cell and page-sample indices remain
// serialized ordinals; no unverified world-coordinate orientation is implied.
struct i76_terrain_scene {
    std::string mission_name{};
    std::string terrain_name{};
    std::uint8_t page_count{};
    std::uint32_t mapped_cells{};
    std::uint32_t referenced_pages{};
    std::array<std::uint8_t, 80U * 80U> cell_pages{};
    std::vector<std::uint16_t> packed_samples{};
};

// Each 16-bit TER sample contains a 12-bit height, one flag and a 3-bit class.
struct i76_terrain_sample {
    std::uint16_t height{};
    std::uint8_t surface_class{};
    bool surface_flag{};
};

struct i76_prepared_terrain {
    bool ready{};
    i76_terrain_scene scene{};
};

struct i76_active_terrain {
    bool loaded{};
    i76_terrain_scene scene{};
};

enum class i76_terrain_result : std::uint8_t {
    ok = 0,
    not_initialized,
    invalid_argument,
    busy,
    missing_mission,
    missing_terrain,
    invalid_terrain,
    resource_error,
    not_prepared,
    not_loaded,
};

struct i76_terrain_error {
    i76_terrain_result code{};
    std::uint32_t offset{};
};

// Prepare a complete, owned terrain snapshot with no world or renderer side
// effects. A failure leaves the previous prepared scene unchanged.
i76_terrain_result i76_terrain_prepare(i76_resource_store& resources,
                                       std::string_view mission_name,
                                       i76_prepared_terrain& prepared,
                                       i76_terrain_error& error);

// Move an already validated terrain snapshot into the active scene slot.
// This does not activate world objects, simulation or a rendering backend.
i76_terrain_result i76_terrain_activate(i76_prepared_terrain& prepared,
                                        i76_active_terrain& active) noexcept;
i76_terrain_result i76_terrain_discard(i76_prepared_terrain& prepared) noexcept;
i76_terrain_result i76_terrain_unload(i76_active_terrain& active) noexcept;

// Resolve raw serialized cell ordinal and page-sample ordinal into attributes.
// An unmapped 0xFF cell or invalid index leaves the supplied result unchanged.
bool i76_terrain_sample_at(const i76_terrain_scene& scene,
                           std::size_t cell_index,
                           std::size_t sample_index,
                           i76_terrain_sample& output) noexcept;

const char* i76_terrain_result_name(i76_terrain_result result) noexcept;
