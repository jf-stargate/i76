#pragma once

#include "i76/terrain_scene.h"

#include <array>
#include <cstdint>

// Safe source-lattice access, separate from the original unchecked helper.
// All results refer to the 128x128 runtime page grid, not a page-ordinal map.
enum class i76_terrain_lattice_result : std::uint8_t {
    ok = 0,
    default_page,
    invalid_coordinate,
    invalid_scene,
};

// A zero default page is a VALID source, distinct from TER page ordinal zero.
// source_col/source_row are -1 outside the embedded 80x80 ZMAP.
struct i76_terrain_lattice_sample {
    std::int32_t lattice_x{};
    std::int32_t lattice_z{};
    std::int16_t source_col{-1};
    std::int16_t source_row{-1};
    std::uint8_t runtime_col{};
    std::uint8_t runtime_row{};
    std::uint8_t local_x{};
    std::uint8_t local_z{};
    std::uint8_t page_ordinal{0xffU};
    std::uint16_t packed_word{};
    i76_terrain_sample attributes{};
};

// Conceptual world coordinates. The original source geometry initially keeps
// lattice X/Z and low12 height and applies scale during its view transform.
struct i76_terrain_lattice_position {
    double x{};
    double y{};
    double z{};
    i76_terrain_lattice_sample source{};
};

// Original height-query corner order: (X,Z), (X+1,Z), (X,Z+1), (X+1,Z+1).
// Each corner resolves its OWN runtime page reference; no edge duplication.
struct i76_terrain_lattice_quad {
    std::array<i76_terrain_lattice_sample, 4U> corners{};
    bool includes_default{};
};

// Valid lattice X/Z domain: [-3072, 13311], the 128x128 runtime page grid.
// Return ok or default_page with valid output; errors preserve the output.
// A malformed active page ID or inconsistent packed array is invalid_scene.
// This checked boundary intentionally excludes original flattened-row spill.
i76_terrain_lattice_result i76_terrain_lattice_at(
    const i76_terrain_scene& scene,
    std::int32_t global_x,
    std::int32_t global_z,
    i76_terrain_lattice_sample& output) noexcept;

// Same source resolution with world X/Z = lattice * 5 and Y = low12 * 0.1f.
// No interpolated height query or native x87 parity is asserted.
i76_terrain_lattice_result i76_terrain_lattice_position_at(
    const i76_terrain_scene& scene,
    std::int32_t global_x,
    std::int32_t global_z,
    i76_terrain_lattice_position& output) noexcept;

// Resolve the four corners of a global lattice cell atomically. A cell whose
// X+1 or Z+1 is outside the checked grid is invalid_coordinate.
i76_terrain_lattice_result i76_terrain_lattice_quad_at(
    const i76_terrain_scene& scene,
    std::int32_t global_x,
    std::int32_t global_z,
    i76_terrain_lattice_quad& output) noexcept;

const char* i76_terrain_lattice_result_name(
    i76_terrain_lattice_result result) noexcept;
