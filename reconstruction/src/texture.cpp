#include "i76/texture.h"

#include <algorithm>
#include <utility>

// -----------------------------------------------------------------------------
// Read an unsigned little-endian 32-bit field from a validated span.
// -----------------------------------------------------------------------------
static std::uint32_t read_u32(std::span<const std::uint8_t> bytes,
                              std::size_t offset) noexcept
{
    return static_cast<std::uint32_t>(bytes[offset])
           | (static_cast<std::uint32_t>(bytes[offset + 1U]) << 8U)
           | (static_cast<std::uint32_t>(bytes[offset + 2U]) << 16U)
           | (static_cast<std::uint32_t>(bytes[offset + 3U]) << 24U);
}

// -----------------------------------------------------------------------------
// Read an unsigned little-endian block token from the VQM token plane.
// -----------------------------------------------------------------------------
static std::uint16_t read_u16(std::span<const std::uint8_t> bytes,
                              std::size_t offset) noexcept
{
    return static_cast<std::uint16_t>(bytes[offset])
           | static_cast<std::uint16_t>(bytes[offset + 1U] << 8U);
}

// -----------------------------------------------------------------------------
// Preserve the caller's output and record a precise validation failure.
// -----------------------------------------------------------------------------
static i76_texture_result fail(i76_texture_error& error,
                               i76_texture_result code,
                               std::size_t offset) noexcept
{
    error.code = code;
    error.offset = offset;
    return code;
}

// -----------------------------------------------------------------------------
// Decode bounded VQM blocks against an explicitly supplied codebook.
// -----------------------------------------------------------------------------
i76_texture_result i76_texture_decode(
    std::span<const std::uint8_t> vqm,
    std::span<const std::uint8_t> cbk,
    i76_indexed_texture& output,
    i76_texture_error& error)
{
    std::uint32_t width = 0U;
    std::uint32_t height_word = 0U;
    std::uint32_t height = 0U;
    std::uint32_t tile_count = 0U;
    std::size_t columns = 0U;
    std::size_t rows = 0U;
    std::size_t token_count = 0U;
    std::size_t name_end = 8U;
    i76_indexed_texture decoded = {};

    error = {};
    if (vqm.size() < 24U) {
        return fail(error, i76_texture_result::invalid_vqm, vqm.size());
    }
    if (cbk.size() < 4U) {
        return fail(error, i76_texture_result::invalid_cbk, cbk.size());
    }
    width = read_u32(vqm, 0U);
    height_word = read_u32(vqm, 4U);
    height = height_word & 0x1fffffffU;
    if (width == 0U
        || height == 0U
        || (height_word & 0xe0000000U) != 0U
        || height > i76_texture_max_pixels
        || width > i76_texture_max_pixels / height) {
        return fail(error, i76_texture_result::invalid_dimensions, 0U);
    }
    for (; name_end < 24U; ++name_end) {
        if (vqm[name_end] == 0U) {
            break;
        }
    }
    if (name_end == 24U
        || name_end == 8U) {
        return fail(error, i76_texture_result::invalid_vqm, 8U);
    }
    tile_count = read_u32(cbk, 0U);
    if (tile_count > 32768U
        || cbk.size() != 4U + static_cast<std::size_t>(tile_count) * 16U) {
        return fail(error, i76_texture_result::invalid_cbk, 0U);
    }
    columns = (static_cast<std::size_t>(width) + 3U) / 4U;
    rows = (static_cast<std::size_t>(height) + 3U) / 4U;
    token_count = columns * rows;
    if (vqm.size() != 24U + 2U * token_count) {
        return fail(error, i76_texture_result::invalid_vqm, 24U);
    }
    decoded.width = width;
    decoded.height = height;
    decoded.codebook.assign(
        reinterpret_cast<const char*>(vqm.data() + 8U),
        name_end - 8U);
    decoded.pixels.resize(static_cast<std::size_t>(width) * height);

    for (std::size_t by = 0U; by < rows; ++by) {
        for (std::size_t bx = 0U; bx < columns; ++bx) {
            const std::size_t token_offset =
                24U + 2U * (by * columns + bx);
            const std::uint16_t token = read_u16(vqm, token_offset);
            const bool solid = (token & 0x8000U) != 0U;
            if (!solid
                && token >= tile_count) {
                return fail(error, i76_texture_result::invalid_token,
                            token_offset);
            }
            for (std::size_t y = 0U;
                 y < std::min<std::size_t>(4U, height - by * 4U);
                 ++y) {
                for (std::size_t x = 0U;
                     x < std::min<std::size_t>(4U, width - bx * 4U);
                     ++x) {
                    const std::size_t target =
                        (by * 4U + y) * width + bx * 4U + x;
                    const std::size_t source =
                        4U + static_cast<std::size_t>(token) * 16U
                        + y * 4U + x;
                    decoded.pixels[target] = solid ?
                        static_cast<std::uint8_t>(token & 0xffU) :
                        cbk[source];
                }
            }
        }
    }
    output = std::move(decoded);
    return i76_texture_result::ok;
}

// -----------------------------------------------------------------------------
// Decode a named VQM using mounted resource bytes and a relative CBK lease.
// -----------------------------------------------------------------------------
i76_texture_result i76_texture_read(i76_resource_store& resources,
                                    std::string_view name,
                                    i76_indexed_texture& output,
                                    i76_texture_error& error)
{
    std::string key = {};
    std::string dependency = {};
    std::string cbk_key = {};
    i76_resource_handle vqm_handle = {};
    i76_resource_handle cbk_handle = {};
    i76_resource_result status = i76_resource_result::ok;
    i76_texture_result result = i76_texture_result::ok;
    const i76_resource_entry* entry = nullptr;
    const i76_resource_entry* codebook = nullptr;
    i76_indexed_texture decoded = {};
    std::size_t end = 8U;

    error = {};
    if (i76_resource_normalize_name(name, key) != i76_resource_result::ok
        || !key.ends_with(".vqm")) {
        return fail(error, i76_texture_result::invalid_argument, 0U);
    }
    status = i76_resource_acquire(resources, key, vqm_handle);
    if (status != i76_resource_result::ok) {
        return fail(error, status == i76_resource_result::not_found ?
                    i76_texture_result::missing_vqm :
                    i76_texture_result::resource_error, 0U);
    }
    entry = i76_resource_lookup(resources, vqm_handle);
    if (entry == nullptr
        || entry->bytes.size() < 24U) {
        result = fail(error, i76_texture_result::invalid_vqm, 0U);
    } else {
        for (; end < 24U; ++end) {
            if (entry->bytes[end] == 0U) {
                break;
            }
        }
        if (end == 8U
            || end == 24U) {
            result = fail(error, i76_texture_result::invalid_vqm, 8U);
        } else {
            dependency.assign(
                reinterpret_cast<const char*>(entry->bytes.data() + 8U),
                end - 8U);
            status = i76_resource_normalize_name(dependency, cbk_key);
            if (status != i76_resource_result::ok) {
                result = fail(error, i76_texture_result::invalid_vqm, 8U);
            } else {
                const std::size_t slash = key.rfind('/');
                if (slash != std::string::npos) {
                    cbk_key = key.substr(0U, slash + 1U) + cbk_key;
                }
            }
        }
    }
    if (result == i76_texture_result::ok) {
        status = i76_resource_acquire(resources, cbk_key, cbk_handle);
        if (status != i76_resource_result::ok) {
            result = fail(error, status == i76_resource_result::not_found ?
                          i76_texture_result::missing_cbk :
                          i76_texture_result::resource_error, 8U);
        } else {
            // Reacquire entry pointers: the cache vector may have grown.
            entry = i76_resource_lookup(resources, vqm_handle);
            codebook = i76_resource_lookup(resources, cbk_handle);
            if (entry == nullptr
                || codebook == nullptr) {
                result = fail(error, i76_texture_result::resource_error, 0U);
            } else {
                result = i76_texture_decode(entry->bytes, codebook->bytes,
                                            decoded, error);
                if (result == i76_texture_result::ok) {
                    decoded.name = key;
                    decoded.codebook = cbk_key;
                    output = std::move(decoded);
                }
            }
        }
    }
    if (cbk_handle.slot != 0U) {
        i76_resource_release(resources, cbk_handle);
    }
    i76_resource_release(resources, vqm_handle);
    return result;
}

// -----------------------------------------------------------------------------
// Sample a decoded power-of-two texture using signed fixed-point bit masks.
// -----------------------------------------------------------------------------
bool i76_texture_sample(const i76_indexed_texture& texture,
                        std::int32_t fixed_u,
                        std::int32_t fixed_v,
                        std::uint8_t& texel) noexcept
{
    std::uint32_t x = 0U;
    std::uint32_t y = 0U;

    if (texture.width == 0U
        || texture.height == 0U
        || (texture.width & (texture.width - 1U)) != 0U
        || (texture.height & (texture.height - 1U)) != 0U
        || texture.height > i76_texture_max_pixels
        || texture.width > i76_texture_max_pixels / texture.height
        || texture.pixels.size() !=
            static_cast<std::size_t>(texture.width) * texture.height) {
        return false;
    }
    x = static_cast<std::uint32_t>(fixed_u >> 16) & (texture.width - 1U);
    y = static_cast<std::uint32_t>(fixed_v >> 16) & (texture.height - 1U);
    texel = texture.pixels[static_cast<std::size_t>(y) * texture.width + x];
    return true;
}

// -----------------------------------------------------------------------------
// Name texture load and decode results for command and test diagnostics.
// -----------------------------------------------------------------------------
const char* i76_texture_result_name(i76_texture_result code) noexcept
{
    switch (code) {
    case i76_texture_result::ok: return "ok";
    case i76_texture_result::invalid_argument: return "invalid name";
    case i76_texture_result::invalid_vqm: return "invalid VQM";
    case i76_texture_result::invalid_cbk: return "invalid CBK";
    case i76_texture_result::invalid_dimensions: return "invalid dimensions";
    case i76_texture_result::invalid_token: return "invalid VQM token";
    case i76_texture_result::missing_vqm: return "VQM not found";
    case i76_texture_result::missing_cbk: return "CBK not found";
    case i76_texture_result::resource_error: return "resource error";
    }
    return "unknown texture error";
}
