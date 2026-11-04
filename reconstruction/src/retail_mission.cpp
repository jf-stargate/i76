#include "i76/retail_mission.h"

#include <cstring>
#include <limits>
#include <utility>

// -----------------------------------------------------------------------------
// Record the specific retail-data error and byte offset.
// -----------------------------------------------------------------------------
static i76_retail_result fail(i76_retail_error& error,
                              i76_retail_result code,
                              std::uint32_t offset) noexcept
{
    error.code = code;
    error.offset = offset;
    return code;
}

// -----------------------------------------------------------------------------
// Compare a decoded BWD2 record with an expected FourCC.
// -----------------------------------------------------------------------------
static bool is_tag(const i76_bwd2_chunk& chunk, const char* name) noexcept
{
    return std::strcmp(chunk.tag, name) == 0;
}

// -----------------------------------------------------------------------------
// Find the semantic section matching a source byte offset.
// -----------------------------------------------------------------------------
static i76_retail_section* find_section(i76_retail_mission_definition& mission,
                                        std::uint32_t offset) noexcept
{
    for (i76_retail_section& section : mission.sections) {
        if (section.offset == offset) {
            return &section;
        }
    }
    return nullptr;
}

// -----------------------------------------------------------------------------
// Validate the 80-by-80 terrain page map and collect page statistics.
// -----------------------------------------------------------------------------
static i76_retail_result decode_zmap(std::span<const std::uint8_t> bytes,
                                     const i76_bwd2_chunk& chunk,
                                     i76_retail_terrain_definition& terrain,
                                     i76_retail_error& error)
{
    std::array<bool, 256U> seen{};
    std::uint8_t index{};
    std::size_t position{};

    if (terrain.has_zmap
        || chunk.payload_size != 1U +
        terrain.page_indices.size()) {
        return fail(error, i76_retail_result::invalid_terrain_map,
            chunk.offset);
    }
    terrain.has_zmap = true;
    terrain.zmap_offset = chunk.offset;
    terrain.active_pages = bytes[chunk.payload_offset];
    for (position = 0U; position < terrain.page_indices.size(); ++position) {
        index = bytes[chunk.payload_offset + 1U + position];
        terrain.page_indices[position] = index;
        if (index == 0xffU) {
            continue;
        }
        if (index >= terrain.active_pages) {
            return fail(error, i76_retail_result::invalid_terrain_map,
                        chunk.payload_offset + 1U +
                        static_cast<std::uint32_t>(position));
        }
        ++terrain.mapped_cells;
        if (!seen[index]) {
            seen[index] = true;
            ++terrain.referenced_pages;
        }
    }
    return i76_retail_result::ok;
}

// -----------------------------------------------------------------------------
// Decode and validate the ZONE sidecar name and opaque prefix.
// -----------------------------------------------------------------------------
static i76_retail_result decode_zone(std::span<const std::uint8_t> bytes,
                                     const i76_bwd2_chunk& chunk,
                                     i76_retail_terrain_definition& terrain,
                                     i76_retail_error& error)
{
    std::size_t end{};
    std::string raw{};
    std::string normalized{};

    if (terrain.has_zone
        || chunk.payload_size != 14U) {
        return fail(error, i76_retail_result::invalid_terrain_name,
            chunk.offset);
    }
    terrain.has_zone = true;
    terrain.zone_offset = chunk.offset;
    // Retail ZONE handler 004939D0 reads the filename from payload +1;
    // it obtains its page count from the prior ZMAP handler's state.
    // The first ZONE payload byte is not a second validated page count.
    terrain.zone_prefix_byte = bytes[chunk.payload_offset];
    end = 0U;
    while (end < 13U
           && bytes[chunk.payload_offset + 1U + end] != 0U) {
        ++end;
    }
    raw.assign(reinterpret_cast<const char*>(bytes.data() + chunk.payload_offset
        + 1U), end);
    if (i76_resource_normalize_name(raw, normalized) != i76_resource_result::ok
            || normalized.find('/') != std::string::npos) {
        return fail(error, i76_retail_result::invalid_terrain_name,
            chunk.payload_offset + 1U);
    }
    terrain.sidecar = std::move(normalized);
    return i76_retail_result::ok;
}

// -----------------------------------------------------------------------------
// Build an owned retail mission description without modifying runtime state.
// -----------------------------------------------------------------------------
i76_retail_result i76_retail_mission_decode(std::span<const std::uint8_t> bytes,
                                          std::string_view name,
                                          i76_retail_mission_definition& output,
                                          i76_retail_error& error)
{
    i76_retail_mission_definition candidate{};
    i76_bwd2_document document{};
    i76_bwd2_error bwd2_error{};
    i76_retail_result status{i76_retail_result::ok};
    std::string normalized{};
    const i76_bwd2_chunk* parent{};
    i76_retail_section* section{};
    std::size_t separator{};
    std::size_t index{};

    error = {};
    if (i76_resource_normalize_name(name, normalized) !=
        i76_resource_result::ok) {
        return fail(error, i76_retail_result::invalid_argument, 0U);
    }
    if (i76_bwd2_parse(bytes, document, bwd2_error) != i76_bwd2_result::ok) {
        return fail(error, i76_retail_result::invalid_structure,
            bwd2_error.offset);
    }
    if (document.chunks.empty()
        || !is_tag(document.chunks[0], "BWD2")
        || document.chunks[0].size != 8U) {
        return fail(error, i76_retail_result::invalid_structure, 0U);
    }
    candidate.name = std::move(normalized);
    candidate.byte_count = document.byte_count;
    candidate.chunk_count = static_cast<std::uint32_t>(document.chunks.size());
    for (index = 1U; index < document.chunks.size(); ++index) {
        const i76_bwd2_chunk& chunk = document.chunks[index];
        if (chunk.parent != 0U) {
            continue;
        }
        if (is_tag(chunk, "REV")) {
            if (candidate.has_revision
                || !chunk.has_revision) {
                return fail(error, i76_retail_result::invalid_record,
                    chunk.offset);
            }
            candidate.has_revision = true;
            candidate.revision = chunk.revision;
        } else if (!is_tag(chunk, "EXIT")) {
            i76_retail_section entry{};
            entry.tag = chunk.tag;
            entry.offset = chunk.offset;
            entry.bytes = chunk.size;
            for (const i76_retail_section& existing : candidate.sections) {
                if (existing.tag == entry.tag) {
                    return fail(error, i76_retail_result::invalid_record,
                        chunk.offset);
                }
            }
            candidate.sections.push_back(std::move(entry));
        }
    }
    if (!candidate.has_revision) {
        return fail(error, i76_retail_result::invalid_record, 8U);
    }
    for (index = 1U; index < document.chunks.size(); ++index) {
        const i76_bwd2_chunk& chunk = document.chunks[index];
        if (chunk.parent == 0U
            || chunk.parent > document.chunks.size()) {
            continue;
        }
        parent = &document.chunks[chunk.parent - 1U];
        if (parent->parent != 0U) {
            continue;
        }
        section = find_section(candidate, parent->offset);
        if (section == nullptr) {
            continue;
        }
        ++section->direct_children;
        if (chunk.has_revision) {
            if (section->has_revision) {
                return fail(error, i76_retail_result::invalid_record,
                    chunk.offset);
            }
            section->has_revision = true;
            section->revision = chunk.revision;
        }
        if (section->tag == "WDEF"
            && is_tag(chunk, "WRLD")) {
            // Opaque until WRLD field offsets are validated.
            ++candidate.wrld_records;
        }
        if (section->tag == "ODEF"
            && is_tag(chunk, "OBJ")) {
            ++candidate.object_records;
        }
        if (section->tag == "RDEF"
            && is_tag(chunk, "RSEG")) {
            ++candidate.route_records;
        }
        if (section->tag == "ADEF"
            && is_tag(chunk, "FSM")) {
            ++candidate.fsm_records;
        }
        if (section->tag == "TDEF"
            && is_tag(chunk, "ZMAP")) {
            status = decode_zmap(bytes, chunk, candidate.terrain, error);
        } else if (section->tag == "TDEF"
                   && is_tag(chunk, "ZONE")) {
            status = decode_zone(bytes, chunk, candidate.terrain, error);
        }
        if (status != i76_retail_result::ok) {
            return status;
        }
    }
    if (candidate.terrain.has_zone) {
        separator = candidate.name.find_last_of('/');
        if (separator != std::string::npos) {
            candidate.terrain.resource_name = candidate.name.substr(0U,
                separator + 1U);
        }
        candidate.terrain.resource_name += candidate.terrain.sidecar;
        if (candidate.terrain.resource_name.size() >
            i76_resource_max_name_length) {
            return fail(error, i76_retail_result::invalid_terrain_name,
                        candidate.terrain.zone_offset);
        }
    }
    output = std::move(candidate);
    return i76_retail_result::ok;
}

// -----------------------------------------------------------------------------
// Acquire, decode, and release the selected retail mission bytes.
// -----------------------------------------------------------------------------
i76_retail_result i76_retail_mission_read(i76_resource_store& resources,
                                          std::string_view name,
                                          i76_retail_mission_definition& output,
                                          i76_retail_error& error)
{
    i76_resource_handle handle{};
    i76_resource_result acquisition{i76_resource_result::ok};
    const i76_resource_entry* entry{};
    i76_retail_result status{i76_retail_result::ok};

    error = {};
    if (!resources.initialized) {
        return fail(error, i76_retail_result::not_initialized, 0U);
    }
    acquisition = i76_resource_acquire(resources, name, handle);
    if (acquisition != i76_resource_result::ok) {
        if (acquisition == i76_resource_result::not_found) {
            return fail(error, i76_retail_result::resource_not_found, 0U);
        }
        if (acquisition == i76_resource_result::invalid_argument) {
            return fail(error, i76_retail_result::invalid_argument, 0U);
        }
        return fail(error, i76_retail_result::resource_error, 0U);
    }
    try {
        entry = i76_resource_lookup(resources, handle);
        if (entry == nullptr) {
            status = fail(error, i76_retail_result::resource_error, 0U);
        } else {
            status = i76_retail_mission_decode(entry->bytes, name, output,
                error);
        }
    } catch (...) {
        i76_resource_release(resources, handle);
        throw;
    }
    i76_resource_release(resources, handle);
    return status;
}

// -----------------------------------------------------------------------------
// Validate a TER sidecar and summarize its packed terrain samples.
// -----------------------------------------------------------------------------
i76_retail_result i76_retail_terrain_probe(i76_resource_store& resources,
                                   const i76_retail_mission_definition& mission,
                                   i76_retail_terrain_samples& output,
                                   i76_retail_error& error)
{
    i76_retail_terrain_samples candidate{};
    i76_resource_handle handle{};
    i76_resource_result acquisition{i76_resource_result::ok};
    const i76_resource_entry* entry{};
    i76_retail_result status{i76_retail_result::ok};
    std::size_t expected{};
    std::size_t index{};
    std::uint16_t word{};
    std::uint8_t surface_class{};

    error = {};
    if (!resources.initialized) {
        return fail(error, i76_retail_result::not_initialized, 0U);
    }
    if (!mission.terrain.has_zmap
        || !mission.terrain.has_zone) {
        return fail(error, i76_retail_result::missing_terrain, 0U);
    }
    acquisition = i76_resource_acquire(resources, mission.terrain.resource_name,
        handle);
    if (acquisition != i76_resource_result::ok) {
        if (acquisition == i76_resource_result::not_found) {
            return fail(error, i76_retail_result::resource_not_found, 0U);
        }
        return fail(error, i76_retail_result::resource_error, 0U);
    }
    try {
        entry = i76_resource_lookup(resources, handle);
        expected = static_cast<std::size_t>(mission.terrain.active_pages) *
                   i76_retail_terrain_page_bytes;
        if (entry == nullptr) {
            status = fail(error, i76_retail_result::resource_error, 0U);
        } else if (entry->bytes.size() != expected) {
            status = fail(error, i76_retail_result::invalid_terrain_size, 0U);
        } else {
            candidate.pages = mission.terrain.active_pages;
            candidate.samples = static_cast<std::uint64_t>(expected / 2U);
            candidate.height_min = std::numeric_limits<std::uint16_t>::max();
            for (index = 0U; index < expected; index += 2U) {
                word = static_cast<std::uint16_t>(entry->bytes[index]) |
                       static_cast<std::uint16_t>(entry->bytes[index + 1U]) <<
                           8U;
                const std::uint16_t height = word & 0x0fffU;
                if (height < candidate.height_min) {
                    candidate.height_min = height;
                }
                if (height > candidate.height_max) {
                    candidate.height_max = height;
                }
                if ((word & 0x1000U) != 0U) {
                    ++candidate.surface_flags;
                }
                surface_class = static_cast<std::uint8_t>((word >> 13U) & 7U);
                ++candidate.surface_classes[surface_class];
            }
            if (candidate.samples == 0U) {
                candidate.height_min = 0U;
            }
        }
    } catch (...) {
        i76_resource_release(resources, handle);
        throw;
    }
    i76_resource_release(resources, handle);
    if (status == i76_retail_result::ok) {
        output = std::move(candidate);
    }
    return status;
}

// -----------------------------------------------------------------------------
// Return a stable diagnostic name for a retail decode result.
// -----------------------------------------------------------------------------
const char* i76_retail_result_name(i76_retail_result result) noexcept
{
    switch (result) {
    case i76_retail_result::ok: return "ok";
    case i76_retail_result::invalid_argument: return "invalid mission name";
    case i76_retail_result::not_initialized: return
        "resource store not initialized";
    case i76_retail_result::resource_not_found: return "resource not found";
    case i76_retail_result::resource_error: return "resource read failure";
    case i76_retail_result::invalid_structure: return
        "invalid BWD2 mission structure";
    case i76_retail_result::invalid_record: return
        "invalid mission section or revision";
    case i76_retail_result::invalid_terrain_map: return
        "invalid ZMAP length, duplicate, or page index";
    case i76_retail_result::invalid_terrain_name: return
        "invalid ZONE terrain filename";
    case i76_retail_result::missing_terrain: return
        "missing ZMAP or ZONE metadata";
    case i76_retail_result::invalid_terrain_size: return
        "TER sidecar page count or byte size mismatch";
    }
    return "unknown retail mission reader error";
}
