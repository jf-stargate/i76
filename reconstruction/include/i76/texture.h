#pragma once

#include "i76/resource.h"

#include <cstddef>
#include <cstdint>
#include <span>
#include <string>
#include <string_view>
#include <vector>

// An owned indexed image. Pixels have exactly width*height bytes, in row order.
// This is a decoded asset, not a renderer command or a native retail cache row.
struct i76_indexed_texture {
    std::string name{};
    std::string codebook{};
    std::uint32_t width{};
    std::uint32_t height{};
    std::vector<std::uint8_t> pixels{};
};

enum class i76_texture_result : std::uint8_t {
    ok = 0,
    invalid_argument,
    invalid_vqm,
    invalid_cbk,
    invalid_dimensions,
    invalid_token,
    missing_vqm,
    missing_cbk,
    resource_error,
};

struct i76_texture_error {
    i76_texture_result code{};
    std::size_t offset{};
};

inline constexpr std::size_t i76_texture_max_pixels = 4U * 1024U * 1024U;

// Strict, allocation-bounded VQM/CBK decode. Input leases are never retained.
// On error the previous output object is unchanged.
i76_texture_result i76_texture_decode(
    std::span<const std::uint8_t> vqm,
    std::span<const std::uint8_t> cbk,
    i76_indexed_texture& output,
    i76_texture_error& error);

// Resolve a specific .vqm and its adjacent CBK dependency through the mounted
// resource providers; all transient leases are released on every return.
i76_texture_result i76_texture_read(i76_resource_store& resources,
                                    std::string_view name,
                                    i76_indexed_texture& output,
                                    i76_texture_error& error);

// Sampling contract for software-indexed callbacks: signed 16.16 coordinates
// shifted arithmetically, then masked. Only power-of-two shapes are supported.
bool i76_texture_sample(const i76_indexed_texture& texture,
                        std::int32_t fixed_u,
                        std::int32_t fixed_v,
                        std::uint8_t& texel) noexcept;

const char* i76_texture_result_name(i76_texture_result code) noexcept;
