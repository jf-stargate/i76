#include "i76/bwd2.h"

#include <cstring>
#include <limits>
#include <utility>

static std::uint32_t read_le_u32(const std::uint8_t* bytes) noexcept
{
    std::uint32_t value = 0;

    value = static_cast<std::uint32_t>(bytes[0]);
    value |= static_cast<std::uint32_t>(bytes[1]) << 8U;
    value |= static_cast<std::uint32_t>(bytes[2]) << 16U;
    value |= static_cast<std::uint32_t>(bytes[3]) << 24U;
    return value;
}

static bool decode_tag(const std::uint8_t* bytes, char (&tag)[5]) noexcept
{
    std::uint32_t index = 0;
    bool terminated = false;
    bool present = false;
    std::uint8_t character = 0;

    for (index = 0; index < 4U; ++index) {
        character = bytes[index];
        if (character == 0U) {
            terminated = true;
            continue;
        }
        if (terminated || character < 32U || character > 126U) {
            return false;
        }
        tag[index] = static_cast<char>(character);
        present = true;
    }
    tag[4] = '\0';
    return present;
}

static bool container_tag(const char* tag) noexcept
{
    return std::strcmp(tag, "BWD2") == 0 || std::strcmp(tag, "WDEF") == 0 ||
           std::strcmp(tag, "TDEF") == 0 || std::strcmp(tag, "RDEF") == 0 ||
           std::strcmp(tag, "ODEF") == 0 || std::strcmp(tag, "LDEF") == 0 ||
           std::strcmp(tag, "ADEF") == 0;
}

static bool revision_tag(const char* tag) noexcept
{
    return std::strcmp(tag, "REV") == 0 || std::strcmp(tag, "WREV") == 0 ||
           std::strcmp(tag, "TREV") == 0 || std::strcmp(tag, "RREV") == 0 ||
           std::strcmp(tag, "OREV") == 0 || std::strcmp(tag, "LREV") == 0 ||
           std::strcmp(tag, "AREV") == 0;
}

static i76_bwd2_result fail(i76_bwd2_error& error, i76_bwd2_result code,
                            std::uint32_t offset) noexcept
{
    error.code = code;
    error.offset = offset;
    return code;
}

static i76_bwd2_result parse_range(std::span<const std::uint8_t> bytes,
                                    std::uint32_t start, std::uint32_t end,
                                    std::uint32_t parent, std::uint8_t depth,
                                    i76_bwd2_document& candidate,
                                    i76_bwd2_error& error)
{
    std::uint32_t cursor = start;
    std::uint32_t length = 0;
    std::uint32_t index = 0;
    std::uint32_t child_start = 0;
    i76_bwd2_chunk chunk = {};
    i76_bwd2_result result = i76_bwd2_result::ok;
    bool nested = false;

    if (depth > i76_bwd2_max_depth) {
        return fail(error, i76_bwd2_result::excessive_depth, start);
    }
    while (cursor < end) {
        if (end - cursor < 8U) {
            return fail(error, i76_bwd2_result::truncated_header, cursor);
        }
        chunk = {};
        if (!decode_tag(bytes.data() + cursor, chunk.tag)) {
            return fail(error, i76_bwd2_result::invalid_tag, cursor);
        }
        length = read_le_u32(bytes.data() + cursor + 4U);
        if (length < 8U) {
            return fail(error, i76_bwd2_result::invalid_length, cursor);
        }
        // Subtraction avoids unsigned wrap in `cursor + length`.
        if (length > end - cursor) {
            return fail(error, i76_bwd2_result::out_of_bounds, cursor);
        }
        if (candidate.chunks.size() >= i76_bwd2_max_chunks) {
            return fail(error, i76_bwd2_result::too_many_chunks, cursor);
        }
        chunk.offset = cursor;
        chunk.size = length;
        chunk.payload_offset = cursor + 8U;
        chunk.payload_size = length - 8U;
        chunk.parent = parent;
        chunk.depth = depth;
        if (revision_tag(chunk.tag)) {
            if (chunk.payload_size != 4U) {
                return fail(error, i76_bwd2_result::invalid_revision, cursor);
            }
            chunk.has_revision = true;
            chunk.revision = read_le_u32(bytes.data() + chunk.payload_offset);
        }
        nested = container_tag(chunk.tag);
        index = static_cast<std::uint32_t>(candidate.chunks.size() + 1U);
        candidate.chunks.push_back(chunk);
        if (nested && chunk.payload_size != 0U) {
            child_start = chunk.payload_offset;
            result = parse_range(bytes, child_start, cursor + length, index,
                                 static_cast<std::uint8_t>(depth + 1U), candidate, error);
            if (result != i76_bwd2_result::ok) {
                return result;
            }
        }
        cursor += length;
    }
    return i76_bwd2_result::ok;
}

i76_bwd2_result i76_bwd2_parse(std::span<const std::uint8_t> bytes,
                                i76_bwd2_document& document,
                                i76_bwd2_error& error)
{
    i76_bwd2_document candidate = {};
    i76_bwd2_result result = i76_bwd2_result::ok;
    std::uint32_t root_size = 0;

    error = {};
    if (bytes.size() > i76_bwd2_max_bytes ||
        bytes.size() > std::numeric_limits<std::uint32_t>::max()) {
        return fail(error, i76_bwd2_result::too_large, 0U);
    }
    if (bytes.size() < 8U) {
        return fail(error, i76_bwd2_result::truncated_header, 0U);
    }
    if (std::memcmp(bytes.data(), "BWD2", 4U) != 0) {
        return fail(error, i76_bwd2_result::invalid_root, 0U);
    }
    root_size = read_le_u32(bytes.data() + 4U);
    if (root_size < 8U) {
        return fail(error, i76_bwd2_result::invalid_length, 0U);
    }
    if (root_size > bytes.size()) {
        return fail(error, i76_bwd2_result::out_of_bounds, 0U);
    }
    if (root_size < bytes.size()) {
        return fail(error, i76_bwd2_result::trailing_data, root_size);
    }
    candidate.byte_count = root_size;
    result = parse_range(bytes, 0U, root_size, 0U, 0U, candidate, error);
    if (result != i76_bwd2_result::ok) {
        return result;
    }
    document = std::move(candidate);
    return i76_bwd2_result::ok;
}

i76_bwd2_result i76_bwd2_read(i76_resource_store& store, std::string_view name,
                               i76_bwd2_document& document, i76_bwd2_error& error)
{
    i76_resource_handle handle = {};
    i76_resource_result acquisition = i76_resource_result::ok;
    i76_bwd2_result result = i76_bwd2_result::ok;
    const i76_resource_entry* entry = nullptr;

    error = {};
    if (!store.initialized) {
        return fail(error, i76_bwd2_result::not_initialized, 0U);
    }
    acquisition = i76_resource_acquire(store, name, handle);
    if (acquisition != i76_resource_result::ok) {
        if (acquisition == i76_resource_result::not_found) {
            return fail(error, i76_bwd2_result::resource_not_found, 0U);
        }
        if (acquisition == i76_resource_result::too_large) {
            return fail(error, i76_bwd2_result::too_large, 0U);
        }
        if (acquisition == i76_resource_result::invalid_argument) {
            return fail(error, i76_bwd2_result::invalid_argument, 0U);
        }
        return fail(error, i76_bwd2_result::resource_error, 0U);
    }
    try {
        entry = i76_resource_lookup(store, handle);
        if (entry == nullptr) {
            result = fail(error, i76_bwd2_result::resource_error, 0U);
        } else {
            result = i76_bwd2_parse(entry->bytes, document, error);
        }
    } catch (...) {
        i76_resource_release(store, handle);
        throw;
    }
    i76_resource_release(store, handle);
    return result;
}

const char* i76_bwd2_result_name(i76_bwd2_result result) noexcept
{
    switch (result) {
    case i76_bwd2_result::ok: return "ok";
    case i76_bwd2_result::invalid_argument: return "invalid resource name";
    case i76_bwd2_result::not_initialized: return "resource store not initialized";
    case i76_bwd2_result::resource_not_found: return "resource not found";
    case i76_bwd2_result::resource_error: return "resource read failure";
    case i76_bwd2_result::too_large: return "BWD2 resource exceeds size limit";
    case i76_bwd2_result::invalid_root: return "expected BWD2 root";
    case i76_bwd2_result::trailing_data: return "bytes after BWD2 root";
    case i76_bwd2_result::truncated_header: return "truncated 8-byte chunk header";
    case i76_bwd2_result::invalid_length: return "chunk total size smaller than header";
    case i76_bwd2_result::out_of_bounds: return "chunk exceeds parent or resource bounds";
    case i76_bwd2_result::invalid_tag: return "invalid printable ASCII FourCC";
    case i76_bwd2_result::invalid_revision: return "revision chunk must have four payload bytes";
    case i76_bwd2_result::too_many_chunks: return "BWD2 chunk-count limit exceeded";
    case i76_bwd2_result::excessive_depth: return "BWD2 nesting-depth limit exceeded";
    }
    return "unknown BWD2 reader error";
}
