#pragma once

#include "i76/resource.h"

#include <array>
#include <cstddef>
#include <cstdint>
#include <span>
#include <string_view>

// An ACT is 256 RGB8 triples, with no implicit six-bit scaling or alpha.
struct i76_palette_rgb8 {
    std::array<std::uint8_t, 768U> rgb{};
};

// Serialized LUM and TBL are different tables. The active TBL source-255
// identity row is initialized on load and must not mutate source assets.
struct i76_indexed_color_tables {
    i76_palette_rgb8 palette{};
    std::array<std::uint8_t, 65536U> lum{};
    std::array<std::uint8_t, 65536U> tbl{};
    bool has_lum{};
    bool has_tbl{};
};

enum class i76_color_result : std::uint8_t {
    ok = 0,
    invalid_act,
    invalid_lum,
    invalid_tbl,
    missing_resource,
    resource_error,
};

// Parse all supplied bytes transactionally. Empty LUM/TBL means absent;
// generated LUM and CRT-dependent gamma adjustment are not performed here.
i76_color_result i76_color_decode(
    std::span<const std::uint8_t> act,
    std::span<const std::uint8_t> lum,
    std::span<const std::uint8_t> tbl,
    i76_indexed_color_tables& output);

// Acquire the ACT and any explicitly requested LUM/TBL files using the
// resource store, then release each lease even after a validation failure.
i76_color_result i76_color_read(i76_resource_store& resources,
                                std::string_view act_name,
                                std::string_view lum_name,
                                std::string_view tbl_name,
                                i76_indexed_color_tables& output);

// Original indexed software shade and composition lookups. A missing table
// returns false without overwriting the caller's texel.
bool i76_color_shade(const i76_indexed_color_tables& tables,
                     std::uint8_t source,
                     std::uint32_t accumulator,
                     std::uint8_t& result) noexcept;
bool i76_color_compose(const i76_indexed_color_tables& tables,
                       std::uint8_t source,
                       std::uint8_t destination,
                       std::uint8_t& result) noexcept;

const char* i76_color_result_name(i76_color_result code) noexcept;
