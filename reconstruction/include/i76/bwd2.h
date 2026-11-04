#pragma once

#include "i76/resource.h"

#include <cstddef>
#include <cstdint>
#include <span>
#include <string_view>
#include <vector>

// Read-only structural inventory. No game callbacks, asset decoding, or runtime mutation.
enum class i76_bwd2_result : std::uint8_t {
    ok = 0,
    invalid_argument,
    not_initialized,
    resource_not_found,
    resource_error,
    too_large,
    invalid_root,
    trailing_data,
    truncated_header,
    invalid_length,
    out_of_bounds,
    invalid_tag,
    invalid_revision,
    too_many_chunks,
    excessive_depth,
};

struct i76_bwd2_error {
    i76_bwd2_result code{};
    std::uint32_t offset{};
};

struct i76_bwd2_chunk {
    // ASCII FourCC with trailing NULs removed; a fifth byte always terminates.
    char tag[5]{};
    std::uint32_t offset{};
    std::uint32_t size{};
    std::uint32_t payload_offset{};
    std::uint32_t payload_size{};
    // One-based enclosing-chunk index; zero means a top-level record.
    // Retail BWD2 is an eight-byte top-level marker, not an enclosing chunk.
    std::uint32_t parent{};
    std::uint8_t depth{};
    bool has_revision{};
    std::uint32_t revision{};
};

struct i76_bwd2_document {
    std::uint32_t byte_count{};
    std::vector<i76_bwd2_chunk> chunks{};
};

inline constexpr std::size_t i76_bwd2_max_bytes = i76_resource_max_bytes;
inline constexpr std::uint32_t i76_bwd2_max_chunks = 16384U;
inline constexpr std::uint8_t i76_bwd2_max_depth = 16U;

// Parse a BWD2 stream (retail eight-byte marker or legacy synthetic enclosing root).
// On failure, `document` is unchanged;
// `error` contains a stable error class and the offending byte offset.
i76_bwd2_result i76_bwd2_parse(std::span<const std::uint8_t> bytes,
                                i76_bwd2_document& document,
                                i76_bwd2_error& error);

// Acquire via existing in-memory or directory mounts, inspect, then release.
// This never retains resource handles or modifies the active level/world.
i76_bwd2_result i76_bwd2_read(i76_resource_store& store, std::string_view name,
                               i76_bwd2_document& document, i76_bwd2_error& error);

const char* i76_bwd2_result_name(i76_bwd2_result result) noexcept;
