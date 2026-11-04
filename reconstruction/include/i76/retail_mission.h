#pragma once

#include "i76/bwd2.h"

#include <array>
#include <cstdint>
#include <span>
#include <string>
#include <string_view>
#include <vector>

// Read-only interpretation of a shipped BWD2 mission. This is separate from
// i76_level_definition and never prepares or activates the world.
enum class i76_retail_result : std::uint8_t {
    ok = 0,
    invalid_argument,
    not_initialized,
    resource_not_found,
    resource_error,
    invalid_structure,
    invalid_record,
    invalid_terrain_map,
    invalid_terrain_name,
    missing_terrain,
    invalid_terrain_size,
};

struct i76_retail_error {
    i76_retail_result code{};
    std::uint32_t offset{};
};

struct i76_retail_section {
    std::string tag{};
    std::uint32_t offset{};
    std::uint32_t bytes{};
    std::uint32_t direct_children{};
    bool has_revision{};
    std::uint32_t revision{};
};

struct i76_retail_terrain_definition {
    bool has_zmap{};
    bool has_zone{};
    std::uint8_t active_pages{};
    std::uint32_t mapped_cells{};
    std::uint32_t referenced_pages{};
    std::uint32_t zmap_offset{};
    std::uint32_t zone_offset{};
    // ZONE payload byte 0 is opaque; its loader uses the page count from ZMAP.
    std::uint8_t zone_prefix_byte{};
    std::string sidecar{};
    std::string resource_name{};
    std::array<std::uint8_t, 80U * 80U> page_indices{};
};

struct i76_retail_mission_definition {
    std::string name{};
    std::uint32_t byte_count{};
    std::uint32_t chunk_count{};
    bool has_revision{};
    std::uint32_t revision{};
    std::uint32_t wrld_records{};
    std::uint32_t object_records{};
    std::uint32_t route_records{};
    std::uint32_t fsm_records{};
    std::vector<i76_retail_section> sections{};
    i76_retail_terrain_definition terrain{};
};

struct i76_retail_terrain_samples {
    std::uint32_t pages{};
    std::uint64_t samples{};
    std::uint64_t surface_flags{};
    std::uint16_t height_min{};
    std::uint16_t height_max{};
    std::array<std::uint64_t, 8U> surface_classes{};
};

inline constexpr std::size_t i76_retail_terrain_width = 80U;
inline constexpr std::size_t i76_retail_terrain_page_samples = 128U * 128U;
inline constexpr std::size_t i76_retail_terrain_page_bytes = 2U *
    i76_retail_terrain_page_samples;

// Parse without retaining input data. On failure, previous output is unchanged.
i76_retail_result i76_retail_mission_decode(std::span<const std::uint8_t> bytes,
                                          std::string_view name,
                                          i76_retail_mission_definition& output,
                                          i76_retail_error& error);

// Acquire mission bytes, decode and release even on failure.
i76_retail_result i76_retail_mission_read(i76_resource_store& resources,
                                          std::string_view name,
                                          i76_retail_mission_definition& output,
                                          i76_retail_error& error);

// Resolve the known ZONE .TER sidecar relative to the mission directory and
// check all packed samples. No world state or renderer resource is modified.
i76_retail_result i76_retail_terrain_probe(i76_resource_store& resources,
                                   const i76_retail_mission_definition& mission,
                                   i76_retail_terrain_samples& output,
                                   i76_retail_error& error);

const char* i76_retail_result_name(i76_retail_result result) noexcept;
