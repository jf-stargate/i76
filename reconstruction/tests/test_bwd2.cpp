#include "i76/bwd2.h"

#include <cstdint>
#include <iostream>
#include <limits>
#include <string_view>
#include <vector>

static std::uint32_t failures = 0;

// -----------------------------------------------------------------------------
// Record a test failure when an assertion does not hold.
// -----------------------------------------------------------------------------
static void expect(bool condition, const char* label)
{
    if (!condition) {
        std::cerr << "FAIL: " << label << '\n';
        ++failures;
    }
}

// -----------------------------------------------------------------------------
// Append a little-endian 32-bit integer to a test byte buffer.
// -----------------------------------------------------------------------------
static void write_u32(std::vector<std::uint8_t>& bytes, std::uint32_t value)
{
    bytes.push_back(static_cast<std::uint8_t>(value & 0xffU));
    bytes.push_back(static_cast<std::uint8_t>((value >> 8U) & 0xffU));
    bytes.push_back(static_cast<std::uint8_t>((value >> 16U) & 0xffU));
    bytes.push_back(static_cast<std::uint8_t>((value >> 24U) & 0xffU));
}

// -----------------------------------------------------------------------------
// Encode a BWD2 chunk with a bounded size and FourCC header.
// -----------------------------------------------------------------------------
static std::vector<std::uint8_t> chunk(std::string_view tag,
                                       const std::vector<std::uint8_t>& payload)
{
    std::vector<std::uint8_t> bytes = {};
    std::uint32_t index = 0;

    bytes.reserve(8U + payload.size());
    for (index = 0; index < 4U; ++index) {
        bytes.push_back(index < tag.size() ?
            static_cast<std::uint8_t>(tag[index]) : 0U);
    }
    write_u32(bytes, static_cast<std::uint32_t>(8U + payload.size()));
    bytes.insert(bytes.end(), payload.begin(), payload.end());
    return bytes;
}

// -----------------------------------------------------------------------------
// Append one fixture byte sequence to another.
// -----------------------------------------------------------------------------
static void append(std::vector<std::uint8_t>& target,
                   const std::vector<std::uint8_t>& bytes)
{
    target.insert(target.end(), bytes.begin(), bytes.end());
}

// -----------------------------------------------------------------------------
// Construct a four-byte BWD2 revision record.
// -----------------------------------------------------------------------------
static std::vector<std::uint8_t> revision(std::string_view tag,
                                          std::uint32_t value)
{
    std::vector<std::uint8_t> payload = {};

    write_u32(payload, value);
    return chunk(tag, payload);
}

// -----------------------------------------------------------------------------
// Build a nested BWD2 fixture for structural parser tests.
// -----------------------------------------------------------------------------
static std::vector<std::uint8_t> example()
{
    std::vector<std::uint8_t> root = {};
    std::vector<std::uint8_t> world = {};
    std::vector<std::uint8_t> missions = {};
    const std::vector<std::uint8_t> empty = {};

    append(root, revision("REV", 2U));
    append(world, revision("WREV", 9U));
    append(world, chunk("WRLD", empty));
    append(world, chunk("EXIT", empty));
    append(root, chunk("WDEF", world));
    append(root, chunk("TDEF", revision("TREV", 4U)));
    append(missions, revision("AREV", 1U));
    append(missions, chunk("FSM", empty));
    append(missions, chunk("EXIT", empty));
    append(root, chunk("ADEF", missions));
    append(root, chunk("EXIT", empty));
    return chunk("BWD2", root);
}

// The retail writer emits an eight-byte BWD2 marker followed by sibling
// records.

// -----------------------------------------------------------------------------
// Build a retail-style marker stream from the synthetic fixture.
// -----------------------------------------------------------------------------
static std::vector<std::uint8_t> retail_example()
{
    std::vector<std::uint8_t> enclosed = example();
    std::vector<std::uint8_t> bytes = chunk("BWD2", {});

    bytes.insert(bytes.end(), enclosed.begin() + 8U, enclosed.end());
    return bytes;
}

// The stock mission layout is a flat top-level stream with bounded section
// bodies.

// -----------------------------------------------------------------------------
// Verify full retail layout behavior and error cases.
// -----------------------------------------------------------------------------
static void test_full_retail_layout()
{
    std::vector<std::uint8_t> bytes = chunk("BWD2", {});
    std::vector<std::uint8_t> adef = {};
    i76_bwd2_document document = {};
    i76_bwd2_error error = {};

    append(bytes, revision("REV", 2U));
    append(bytes, chunk("WDEF", revision("WREV", 9U)));
    append(bytes, chunk("TDEF", revision("TREV", 4U)));
    append(bytes, chunk("RDEF", revision("RREV", 1U)));
    append(bytes, chunk("ODEF", revision("OREV", 3U)));
    append(bytes, chunk("LDEF", revision("LREV", 1U)));
    append(adef, revision("AREV", 1U));
    append(adef, chunk("FSM", {}));
    append(adef, chunk("EXIT", {}));
    append(bytes, chunk("ADEF", adef));
    append(bytes, chunk("EXIT", {}));

    expect(i76_bwd2_parse(bytes, document, error) == i76_bwd2_result::ok &&
               document.chunks.size() == 17U && document.byte_count ==
                   bytes.size(),
           "full retail-style outer stream parses with bounded sections");
    expect(std::string_view(document.chunks[0].tag) == "BWD2" &&
               std::string_view(document.chunks[1].tag) == "REV" &&
               std::string_view(document.chunks[2].tag) == "WDEF" &&
               std::string_view(document.chunks[4].tag) == "TDEF" &&
               std::string_view(document.chunks[6].tag) == "RDEF" &&
               std::string_view(document.chunks[8].tag) == "ODEF" &&
               std::string_view(document.chunks[10].tag) == "LDEF" &&
               std::string_view(document.chunks[12].tag) == "ADEF" &&
               std::string_view(document.chunks[16].tag) == "EXIT",
           "original observed section ordering remains visible");
    expect(document.chunks[12].parent == 0U &&
               document.chunks[13].parent == 13U &&
               document.chunks[14].parent == 13U &&
               document.chunks[16].parent == 0U &&
               document.chunks[16].offset + document.chunks[16].size ==
                   bytes.size(),
           "section depths and terminal EXIT bounds are preserved");
}

// -----------------------------------------------------------------------------
// Verify retail marker behavior and error cases.
// -----------------------------------------------------------------------------
static void test_retail_marker()
{
    std::vector<std::uint8_t> bytes = retail_example();
    i76_bwd2_document document = {};
    i76_bwd2_document again = {};
    i76_bwd2_error error = {};

    expect(i76_bwd2_parse(bytes, document, error) == i76_bwd2_result::ok &&
               document.byte_count == bytes.size() && document.chunks.size() ==
                   13U,
           "retail marker followed by sibling records parsed to EOF");
    expect(std::string_view(document.chunks[0].tag) == "BWD2" &&
               document.chunks[0].size == 8U &&
               document.chunks[0].parent == 0U && document.chunks[0].depth ==
                   0U,
           "BWD2 header remains an eight-byte marker");
    expect(std::string_view(document.chunks[1].tag) == "REV" &&
               document.chunks[1].offset == 8U &&
               document.chunks[1].parent == 0U && document.chunks[1].depth == 0U
                   &&
               document.chunks[1].has_revision && document.chunks[1].revision ==
                   2U,
           "outer REV is a top-level sibling of the marker");
    expect(std::string_view(document.chunks[2].tag) == "WDEF" &&
               document.chunks[2].parent == 0U && document.chunks[2].depth == 0U
                   &&
               std::string_view(document.chunks[3].tag) == "WREV" &&
               document.chunks[3].parent == 3U && document.chunks[3].depth ==
                   1U,
           "container children retain correct one-based parent indices");
    expect(std::string_view(document.chunks[8].tag) == "ADEF" &&
               document.chunks[8].parent == 0U && document.chunks[9].parent ==
                   9U &&
               std::string_view(document.chunks[10].tag) == "FSM" &&
               document.chunks[10].payload_size == 0U,
           "retail ADEF and empty FSM are inventoried");
    expect(i76_bwd2_parse(bytes, again, error) == i76_bwd2_result::ok &&
               again.chunks.size() == document.chunks.size() &&
               again.chunks[1].offset == 8U,
           "repeated marker inspection is deterministic");
}

// -----------------------------------------------------------------------------
// Verify structure behavior and error cases.
// -----------------------------------------------------------------------------
static void test_structure()
{
    std::vector<std::uint8_t> bytes = example();
    i76_bwd2_document document = {};
    i76_bwd2_document again = {};
    i76_bwd2_error error = {};
    i76_bwd2_result result = i76_bwd2_result::ok;
    std::size_t index = 0;

    expect(document.chunks.empty() && document.byte_count == 0U &&
               error.code == i76_bwd2_result::ok && error.offset == 0U,
           "zero initialized document and diagnostic");
    result = i76_bwd2_parse(bytes, document, error);
    expect(result == i76_bwd2_result::ok && error.code == i76_bwd2_result::ok,
           "parse BWD2 structure");
    expect(document.chunks.size() == 13U && document.byte_count == bytes.size(),
           "all nested sections accounted for");
    expect(document.chunks[0].parent == 0U && document.chunks[0].depth == 0U &&
               std::string_view(document.chunks[0].tag) == "BWD2",
           "root has one-based parent sentinel");
    expect(std::string_view(document.chunks[1].tag) == "REV" &&
               document.chunks[1].parent == 1U && document.chunks[1].depth == 1U
                   &&
               document.chunks[1].revision == 2U &&
                   document.chunks[1].has_revision,
           "root revision and little endian");
    expect(std::string_view(document.chunks[2].tag) == "WDEF" &&
               document.chunks[2].parent == 1U && document.chunks[2].depth == 1U
                   &&
               std::string_view(document.chunks[3].tag) == "WREV" &&
               document.chunks[3].parent == 3U && document.chunks[3].depth == 2U
                   &&
               document.chunks[3].revision == 9U,
           "nested WDEF child and revision");
    expect(std::string_view(document.chunks[8].tag) == "ADEF" &&
               document.chunks[9].parent == 9U &&
               std::string_view(document.chunks[10].tag) == "FSM" &&
               document.chunks[10].payload_size == 0U,
           "nested empty FSM chunk accepted");
    for (index = 0; index < document.chunks.size(); ++index) {
        expect(document.chunks[index].offset + document.chunks[index].size <=
            bytes.size(),
               "reported span is bounded");
    }
    expect(i76_bwd2_parse(bytes, again, error) == i76_bwd2_result::ok &&
               again.chunks.size() == document.chunks.size() &&
               again.chunks[3].offset == document.chunks[3].offset,
           "repeated inspection is stateless and deterministic");
    expect(std::string_view(
               i76_bwd2_result_name(i76_bwd2_result::invalid_revision)) ==
               "revision chunk must have four payload bytes",
           "named diagnostics");
    for (std::uint32_t code = 0; code <=
         static_cast<std::uint32_t>(i76_bwd2_result::excessive_depth); ++code) {
        expect(!std::string_view(i76_bwd2_result_name(
                    static_cast<i76_bwd2_result>(code))).empty(),
               "every documented BWD2 status has a diagnostic name");
    }
    expect(std::string_view(i76_bwd2_result_name(
               static_cast<i76_bwd2_result>(255U))) ==
                   "unknown BWD2 reader error",
           "unexpected error code is never left uninitialized");
}

// -----------------------------------------------------------------------------
// Check that malformed BWD2 input yields the expected error and offset.
// -----------------------------------------------------------------------------
static void check_failure(const std::vector<std::uint8_t>& bytes,
                          i76_bwd2_result expected,
                          std::uint32_t offset,
                          const char* label)
{
    i76_bwd2_document document = {};
    i76_bwd2_error error = {};

    document.byte_count = 77U;
    document.chunks.push_back({});
    error.offset = 23U;
    error.code = i76_bwd2_result::resource_error;
    expect(i76_bwd2_parse(bytes, document, error) == expected &&
               error.code == expected && error.offset == offset,
           label);
    expect(document.byte_count == 77U && document.chunks.size() == 1U,
           "rejected input does not overwrite prior report");
}

// -----------------------------------------------------------------------------
// Verify invalid inputs behavior and error cases.
// -----------------------------------------------------------------------------
static void test_invalid_inputs()
{
    std::vector<std::uint8_t> bytes = {};
    std::vector<std::uint8_t> payload = {};
    const std::vector<std::uint8_t> empty = {};
    std::uint32_t index = 0;
    i76_bwd2_document future = {};
    i76_bwd2_document revised = {};
    i76_bwd2_error error = {};

    check_failure({}, i76_bwd2_result::truncated_header, 0U,
        "empty input rejected");
    bytes = {'B','W','D','2',8,0,0};
    check_failure(bytes, i76_bwd2_result::truncated_header, 0U,
                  "short root header rejected");
    bytes = chunk("NOPE", {});
    check_failure(bytes, i76_bwd2_result::invalid_root, 0U,
                  "unexpected root rejected");
    bytes = chunk("BWD2", {});
    bytes[4] = 7U;
    check_failure(bytes, i76_bwd2_result::invalid_length, 0U,
                  "root length below header rejected");
    bytes = chunk("BWD2", {});
    bytes[4] = 32U;
    check_failure(bytes, i76_bwd2_result::out_of_bounds, 0U,
                  "root length outside supplied bytes rejected");
    bytes = chunk("BWD2", {});
    bytes.push_back(0U);
    check_failure(bytes, i76_bwd2_result::truncated_header, 8U,
                  "retail marker followed by incomplete sibling rejected");
    bytes = chunk("BWD2", chunk("EXIT", {}));
    bytes.push_back(0U);
    check_failure(bytes, i76_bwd2_result::trailing_data, 16U,
                  "enclosing-root compatibility fixture still rejects "
                  "trailing bytes");
    bytes = retail_example();
    bytes[8U + 4U] = 7U;
    check_failure(bytes, i76_bwd2_result::invalid_length, 8U,
                  "retail sibling length below eight bytes rejected");
    bytes = retail_example();
    bytes.push_back(0U);
    check_failure(bytes, i76_bwd2_result::truncated_header,
                  static_cast<std::uint32_t>(bytes.size() - 1U),
                  "retail stream rejects trailing incomplete header");
    bytes = chunk("BWD2", {0U});
    check_failure(bytes, i76_bwd2_result::truncated_header, 8U,
                  "truncated nested header rejected");
    bytes = chunk("BWD2", chunk("ZMAP", {}));
    bytes[8U + 4U] = 7U;
    check_failure(bytes, i76_bwd2_result::invalid_length, 8U,
                  "nested chunk size below header rejected");
    bytes = chunk("BWD2", chunk("ZMAP", {}));
    bytes[8U + 4U] = 80U;
    check_failure(bytes, i76_bwd2_result::out_of_bounds, 8U,
                  "nested chunk exceeds parent rejected");
    bytes = chunk("BWD2", chunk("REV", {}));
    check_failure(bytes, i76_bwd2_result::invalid_revision, 8U,
                  "known revision requires exactly one uint32");
    bytes = chunk("BWD2", chunk("ZMAP", {}));
    bytes[8U] = 0xffU;
    check_failure(bytes, i76_bwd2_result::invalid_tag, 8U,
                  "non-ASCII tag rejected");
    bytes = chunk("BWD2", chunk("FSM", {}));
    bytes[8U + 1U] = 0U;
    check_failure(bytes, i76_bwd2_result::invalid_tag, 8U,
                  "nontrailing NUL tag rejected");
    bytes = chunk("BWD2", chunk("ZMAP", {}));
    bytes[8U] = 0U;
    bytes[9U] = 0U;
    bytes[10U] = 0U;
    bytes[11U] = 0U;
    check_failure(bytes, i76_bwd2_result::invalid_tag, 8U,
                  "empty FourCC rejected");
    bytes = chunk("BWD2", chunk("FUTR", empty));
    expect(i76_bwd2_parse(bytes, future, error) == i76_bwd2_result::ok &&
               std::string_view(future.chunks[1].tag) == "FUTR" &&
               future.chunks[1].payload_size == 0U,
           "unknown ASCII tag retained as opaque leaf");
    bytes = chunk("BWD2", revision("REV", 0x01020304U));
    expect(i76_bwd2_parse(bytes, revised, error) == i76_bwd2_result::ok &&
               revised.chunks[1].revision == 0x01020304U,
           "endianness conversion verified");
    // More than the configured chunk count must be bounded without allocating
    // a record for every attacker-controlled header.
    payload = {};
    for (index = 0; index < i76_bwd2_max_chunks; ++index) {
        append(payload, chunk("EXIT", empty));
    }
    bytes = chunk("BWD2", payload);
    check_failure(bytes, i76_bwd2_result::too_many_chunks,
                  8U + 8U * (i76_bwd2_max_chunks - 1U),
                  "bounded chunk count");
    bytes = chunk("EXIT", empty);
    for (index = 0; index < static_cast<std::uint32_t>(i76_bwd2_max_depth) + 1U;
        ++index) {
        bytes = chunk("WDEF", bytes);
    }
    bytes = chunk("BWD2", bytes);
    check_failure(bytes, i76_bwd2_result::excessive_depth,
                  8U * (static_cast<std::uint32_t>(i76_bwd2_max_depth) + 1U),
                  "bounded recursion depth");
    bytes.assign(i76_bwd2_max_bytes + 1U, 0U);
    check_failure(bytes, i76_bwd2_result::too_large, 0U,
                  "oversized resource rejected before header access");
}

// -----------------------------------------------------------------------------
// Verify resource lifetime behavior and error cases.
// -----------------------------------------------------------------------------
static void test_resource_lifetime()
{
    i76_resource_store store = {};
    i76_resource_handle handle = {};
    i76_bwd2_document document = {};
    i76_bwd2_error error = {};
    std::vector<std::uint8_t> bytes = retail_example();
    std::vector<std::uint8_t> bad = chunk("NOPE", {});
    i76_resource_stats stats = {};

    expect(i76_bwd2_read(store, "example.msn", document, error) ==
               i76_bwd2_result::not_initialized,
                   "provider requires initialization");
    expect(i76_resource_initialize(store) == i76_resource_result::ok,
           "initialize resource provider");
    expect(i76_resource_mount_memory(store, "test") == i76_resource_result::ok,
           "mount memory provider");
    expect(i76_resource_add_memory(store, "test", "example.msn", bytes) ==
               i76_resource_result::ok, "add valid BWD2 fixture");
    expect(i76_resource_add_memory(store, "test", "bad.msn", bad) ==
               i76_resource_result::ok, "add invalid BWD2 fixture");
    expect(i76_bwd2_read(store, "../bad.msn", document, error) ==
               i76_bwd2_result::invalid_argument,
                   "unsafe resource name rejected");
    expect(i76_bwd2_read(store, "missing.msn", document, error) ==
               i76_bwd2_result::resource_not_found,
                   "missing resource reported");
    expect(i76_bwd2_read(store, "example.msn", document, error) ==
               i76_bwd2_result::ok && document.chunks.size() == 13U,
           "inspect through memory provider");
    stats = i76_resource_get_stats(store);
    expect(stats.references == 0U && stats.cached_bytes == 0U,
           "successful inspection releases byte lease");
    expect(i76_bwd2_read(store, "bad.msn", document, error) ==
               i76_bwd2_result::invalid_root && document.chunks.size() == 13U,
           "failed inspection preserves last valid document");
    stats = i76_resource_get_stats(store);
    expect(stats.references == 0U && stats.cached_bytes == 0U,
           "failed inspection releases byte lease");
    expect(i76_resource_acquire(store, "example.msn", handle) ==
        i76_resource_result::ok,
           "external reference to BWD2 bytes");
    expect(i76_bwd2_read(store, "example.msn", document, error) ==
               i76_bwd2_result::ok, "multiple borrowers share resource entry");
    stats = i76_resource_get_stats(store);
    expect(stats.references == 1U, "inspector retains external ref count");
    expect(i76_resource_release(store, handle) == i76_resource_result::ok,
           "cleanup external reference");
    expect(i76_resource_shutdown(store) == i76_resource_result::ok,
           "resource store shutdown clean");
}

// -----------------------------------------------------------------------------
// Run the test cases and return a failure status when any assertion fails.
// -----------------------------------------------------------------------------
int main()
{
    test_structure();
    test_retail_marker();
    test_full_retail_layout();
    test_invalid_inputs();
    test_resource_lifetime();
    return failures == 0U ? 0 : 1;
}
