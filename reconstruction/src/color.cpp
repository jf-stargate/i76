#include "i76/color.h"

#include <algorithm>
#include <array>
#include <utility>

// -----------------------------------------------------------------------------
// Copy validated ACT/LUM/TBL payloads into independently owned color state.
// -----------------------------------------------------------------------------
i76_color_result i76_color_decode(
    std::span<const std::uint8_t> act,
    std::span<const std::uint8_t> lum,
    std::span<const std::uint8_t> tbl,
    i76_indexed_color_tables& output)
{
    i76_indexed_color_tables candidate = {};

    if (act.size() != candidate.palette.rgb.size()) {
        return i76_color_result::invalid_act;
    }
    if (!lum.empty()
        && lum.size() != candidate.lum.size()) {
        return i76_color_result::invalid_lum;
    }
    if (!tbl.empty()
        && tbl.size() != candidate.tbl.size()) {
        return i76_color_result::invalid_tbl;
    }
    std::copy(act.begin(), act.end(), candidate.palette.rgb.begin());
    if (!lum.empty()) {
        std::copy(lum.begin(), lum.end(), candidate.lum.begin());
        candidate.has_lum = true;
    }
    if (!tbl.empty()) {
        std::copy(tbl.begin(), tbl.end(), candidate.tbl.begin());
        candidate.has_tbl = true;
        // The runtime replaces source row 255 with an identity mapping.
        // Serial data is preserved in the resource provider's leased bytes.
        for (std::size_t destination = 0U; destination < 256U;
             ++destination) {
            candidate.tbl[255U * 256U + destination] =
                static_cast<std::uint8_t>(destination);
        }
    }
    output = std::move(candidate);
    return i76_color_result::ok;
}

// -----------------------------------------------------------------------------
// Acquire an ACT and optional LUM/TBL through the existing resource store.
// -----------------------------------------------------------------------------
i76_color_result i76_color_read(i76_resource_store& resources,
                                std::string_view act_name,
                                std::string_view lum_name,
                                std::string_view tbl_name,
                                i76_indexed_color_tables& output)
{
    std::array<std::string_view, 3U> names = {
        act_name, lum_name, tbl_name
    };
    std::array<i76_resource_handle, 3U> handles = {};
    std::array<std::span<const std::uint8_t>, 3U> buffers = {};
    i76_resource_result status = i76_resource_result::ok;
    i76_color_result result = i76_color_result::ok;
    const i76_resource_entry* entry = nullptr;

    if (act_name.empty()) {
        return i76_color_result::invalid_act;
    }
    for (std::size_t index = 0U; index < names.size(); ++index) {
        if (names[index].empty()) {
            continue;
        }
        status = i76_resource_acquire(resources, names[index],
                                      handles[index]);
        if (status != i76_resource_result::ok) {
            result = status == i76_resource_result::not_found ?
                i76_color_result::missing_resource :
                i76_color_result::resource_error;
            break;
        }
    }
    if (result == i76_color_result::ok) {
        // Acquire all entries only after cache insertion can no longer
        // invalidate pointers into its vector.
        for (std::size_t index = 0U; index < handles.size(); ++index) {
            if (handles[index].slot == 0U) {
                continue;
            }
            entry = i76_resource_lookup(resources, handles[index]);
            if (entry == nullptr) {
                result = i76_color_result::resource_error;
                break;
            }
            buffers[index] = entry->bytes;
        }
    }
    if (result == i76_color_result::ok) {
        result = i76_color_decode(buffers[0], buffers[1], buffers[2], output);
    }
    for (std::size_t index = handles.size(); index != 0U; --index) {
        if (handles[index - 1U].slot != 0U) {
            i76_resource_release(resources, handles[index - 1U]);
        }
    }
    return result;
}

// -----------------------------------------------------------------------------
// Look up a shaded index with the original accumulator's row-selection mask.
// -----------------------------------------------------------------------------
bool i76_color_shade(const i76_indexed_color_tables& tables,
                     std::uint8_t source,
                     std::uint32_t accumulator,
                     std::uint8_t& result) noexcept
{
    if (!tables.has_lum) {
        return false;
    }
    result = tables.lum[(accumulator & 0x1f00U) + source];
    return true;
}

// -----------------------------------------------------------------------------
// Compose the source index over an existing indexed destination through TBL.
// -----------------------------------------------------------------------------
bool i76_color_compose(const i76_indexed_color_tables& tables,
                       std::uint8_t source,
                       std::uint8_t destination,
                       std::uint8_t& result) noexcept
{
    if (!tables.has_tbl) {
        return false;
    }
    result = tables.tbl[(static_cast<std::size_t>(source) << 8U)
                        | destination];
    return true;
}

// -----------------------------------------------------------------------------
// Name resource and payload errors for callers without renderer dependencies.
// -----------------------------------------------------------------------------
const char* i76_color_result_name(i76_color_result code) noexcept
{
    switch (code) {
    case i76_color_result::ok: return "ok";
    case i76_color_result::invalid_act: return "invalid ACT";
    case i76_color_result::invalid_lum: return "invalid LUM";
    case i76_color_result::invalid_tbl: return "invalid TBL";
    case i76_color_result::missing_resource: return "missing color resource";
    case i76_color_result::resource_error: return "resource error";
    }
    return "unknown color error";
}
