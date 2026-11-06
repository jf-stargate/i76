#include "i76/terrain_lattice.h"

#include <cstdint>
#include <iostream>
#include <limits>
#include <string_view>
#include <utility>

static std::uint32_t failures = 0U;

// -----------------------------------------------------------------------------
// Keep testing independent failure cases instead of aborting on first mismatch.
// -----------------------------------------------------------------------------
static void expect(bool condition, const char* message)
{
    if (!condition) {
        std::cerr << "FAIL: " << message << '\n';
        ++failures;
    }
}

// -----------------------------------------------------------------------------
// Author distinct adjacent pages and an aliased reference without game bytes.
// -----------------------------------------------------------------------------
static i76_terrain_scene make_scene()
{
    i76_terrain_scene scene = {};
    constexpr std::size_t samples = i76_retail_terrain_page_samples;

    scene.page_count = 3U;
    scene.cell_pages.fill(0xffU);
    scene.cell_pages[0U] = 0U;
    scene.cell_pages[1U] = 1U;
    scene.cell_pages[80U] = 2U;
    scene.cell_pages[81U] = 0U;
    scene.packed_samples.resize(3U * samples, 0U);

    scene.packed_samples[0U] = 0xf123U;
    scene.packed_samples[127U * 128U + 127U] = 0x6123U;
    scene.packed_samples[samples] = 0x8abcU;
    scene.packed_samples[samples + 127U * 128U] = 0x4001U;
    scene.packed_samples[2U * samples + 127U] = 0x2fedU;
    return scene;
}

// -----------------------------------------------------------------------------
// Check source row/column orientation, local strides, raw words and attributes.
// -----------------------------------------------------------------------------
static void test_source_coordinates()
{
    const i76_terrain_scene scene = make_scene();
    i76_terrain_lattice_sample sample = {};

    expect(i76_terrain_lattice_at(scene, 0, 0, sample) ==
               i76_terrain_lattice_result::ok,
           "origin resolves active page zero");
    expect(sample.lattice_x == 0 && sample.lattice_z == 0
           && sample.source_col == 0 && sample.source_row == 0
           && sample.runtime_col == 24U && sample.runtime_row == 24U
           && sample.local_x == 0U && sample.local_z == 0U
           && sample.page_ordinal == 0U && sample.packed_word == 0xf123U
           && sample.attributes.height == 0x123U
           && sample.attributes.surface_flag
           && sample.attributes.surface_class == 7U,
           "origin has exact byte-derived attributes and provenance");

    expect(i76_terrain_lattice_at(scene, 128, 0, sample) ==
               i76_terrain_lattice_result::ok
           && sample.source_col == 1 && sample.source_row == 0
           && sample.runtime_col == 25U && sample.page_ordinal == 1U
           && sample.packed_word == 0x8abcU
           && sample.attributes.height == 0xabcU
           && !sample.attributes.surface_flag
           && sample.attributes.surface_class == 4U,
           "increasing X selects the next serialized column");

    expect(i76_terrain_lattice_at(scene, 127, 128, sample) ==
               i76_terrain_lattice_result::ok
           && sample.source_col == 0 && sample.source_row == 1
           && sample.local_x == 127U && sample.local_z == 0U
           && sample.page_ordinal == 2U && sample.packed_word == 0x2fedU
           && sample.attributes.height == 0xfedU
           && sample.attributes.surface_class == 1U,
           "increasing Z selects the next row with 256-byte row stride");

    expect(i76_terrain_lattice_at(scene, 127, 127, sample) ==
               i76_terrain_lattice_result::ok
           && sample.packed_word == 0x6123U
           && sample.local_x == 127U && sample.local_z == 127U,
           "end of page is sample 127, never a duplicated sample 128");

    expect(i76_terrain_lattice_at(scene, 128, 128, sample) ==
               i76_terrain_lattice_result::ok
           && sample.page_ordinal == 0U
           && sample.packed_word == 0xf123U
           && sample.source_col == 1 && sample.source_row == 1,
           "repeated page ID reuses data with a distinct world origin");
}

// -----------------------------------------------------------------------------
// Require explicit default-page provenance across source and grid boundaries.
// -----------------------------------------------------------------------------
static void test_default_pages()
{
    const i76_terrain_scene scene = make_scene();
    i76_terrain_lattice_sample sample = {};

    expect(i76_terrain_lattice_at(scene, 256, 0, sample) ==
               i76_terrain_lattice_result::default_page
           && sample.source_col == 2 && sample.source_row == 0
           && sample.page_ordinal == 0xffU
           && sample.packed_word == 0U
           && sample.attributes.height == 0U
           && sample.attributes.surface_class == 0U,
           "unmapped ZMAP cell is the zero default, not page zero");

    expect(i76_terrain_lattice_at(scene, -1, 0, sample) ==
               i76_terrain_lattice_result::default_page
           && sample.source_col == -1 && sample.source_row == -1
           && sample.runtime_col == 23U && sample.runtime_row == 24U
           && sample.local_x == 127U && sample.local_z == 0U,
           "negative lattice inside runtime grid uses default backing");

    expect(i76_terrain_lattice_at(scene, 10240, 0, sample) ==
               i76_terrain_lattice_result::default_page
           && sample.source_col == -1 && sample.runtime_col == 104U,
           "lattice 10240 is a valid runtime-grid default");

    expect(i76_terrain_lattice_at(scene, -3072, -3072, sample) ==
               i76_terrain_lattice_result::default_page
           && sample.runtime_col == 0U && sample.runtime_row == 0U
           && sample.local_x == 0U && sample.local_z == 0U,
           "lowest runtime grid lattice coordinate is valid");

    expect(i76_terrain_lattice_at(scene, 13311, 13311, sample) ==
               i76_terrain_lattice_result::default_page
           && sample.runtime_col == 127U && sample.runtime_row == 127U
           && sample.local_x == 127U && sample.local_z == 127U,
           "highest runtime grid lattice coordinate is valid");

    expect(i76_terrain_lattice_at(scene, 0, -1, sample) ==
               i76_terrain_lattice_result::default_page
           && sample.runtime_col == 24U && sample.runtime_row == 23U,
           "Z default region uses a distinct runtime row");
}

// -----------------------------------------------------------------------------
// Show world axes, page-origin spacing and exact float32 height coefficient.
// -----------------------------------------------------------------------------
static void test_world_positions()
{
    const i76_terrain_scene scene = make_scene();
    i76_terrain_lattice_position position = {};

    expect(i76_terrain_lattice_position_at(scene, 0, 0, position) ==
               i76_terrain_lattice_result::ok
           && position.x == 0.0 && position.z == 0.0
           && position.y == 291.0 * static_cast<double>(0.1F)
           && position.source.packed_word == 0xf123U,
           "height scale is the exact widened float32 constant");
    expect(i76_terrain_lattice_position_at(scene, 128, 128, position) ==
               i76_terrain_lattice_result::ok
           && position.x == 640.0 && position.z == 640.0
           && position.source.packed_word == 0xf123U,
           "repeated page payload does not reuse the original position");
    expect(i76_terrain_lattice_position_at(scene, -1, 0, position) ==
               i76_terrain_lattice_result::default_page
           && position.x == -5.0 && position.z == 0.0
           && position.y == 0.0 && position.source.page_ordinal == 0xffU,
           "default page converts to valid zero-height world position");
    expect(i76_terrain_lattice_position_at(scene, 13311, -3072, position) ==
               i76_terrain_lattice_result::default_page
           && position.x == 66555.0 && position.z == -15360.0,
           "runtime-grid extrema convert without integer overflow");
}

// -----------------------------------------------------------------------------
// Resolve both axes of a diagonal seam using four independent page addresses.
// -----------------------------------------------------------------------------
static void test_page_seams()
{
    i76_terrain_scene scene = make_scene();
    i76_terrain_lattice_quad quad = {};

    expect(i76_terrain_lattice_quad_at(scene, 127, 127, quad) ==
               i76_terrain_lattice_result::ok
           && !quad.includes_default
           && quad.corners[0U].packed_word == 0x6123U
           && quad.corners[1U].packed_word == 0x4001U
           && quad.corners[2U].packed_word == 0x2fedU
           && quad.corners[3U].packed_word == 0xf123U,
           "four diagonal seam corners use four independent page lookups");
    expect(quad.corners[0U].lattice_x == 127
           && quad.corners[1U].lattice_x == 128
           && quad.corners[2U].lattice_z == 128
           && quad.corners[3U].lattice_x == 128
           && quad.corners[3U].lattice_z == 128,
           "corner order is h00 h10 h01 h11");

    expect(i76_terrain_lattice_quad_at(scene, 255, 0, quad) ==
               i76_terrain_lattice_result::default_page
           && quad.includes_default
           && quad.corners[0U].page_ordinal == 1U
           && quad.corners[1U].page_ordinal == 0xffU
           && quad.corners[2U].page_ordinal == 1U
           && quad.corners[3U].page_ordinal == 0xffU,
           "active-to-default horizontal seam is a valid cell");

    expect(i76_terrain_lattice_quad_at(scene, 0, 255, quad) ==
               i76_terrain_lattice_result::default_page
           && quad.corners[0U].page_ordinal == 2U
           && quad.corners[2U].page_ordinal == 0xffU,
           "active-to-default vertical seam is a valid cell");

    scene.cell_pages[1U] = 0U;
    expect(i76_terrain_lattice_quad_at(scene, 127, 0, quad) ==
               i76_terrain_lattice_result::ok
           && quad.corners[0U].page_ordinal == 0U
           && quad.corners[1U].page_ordinal == 0U
           && quad.corners[0U].local_x == 127U
           && quad.corners[1U].local_x == 0U,
           "alias resets local sample index without duplicating a border");
}

// -----------------------------------------------------------------------------
// Ensure overflow, malformed scenes and partial quad reads are transactional.
// -----------------------------------------------------------------------------
static void test_failures()
{
    i76_terrain_scene scene = make_scene();
    i76_terrain_lattice_sample sample = {};
    i76_terrain_lattice_position position = {};
    i76_terrain_lattice_quad quad = {};

    sample.packed_word = 0xbeefU;
    position.x = 7123.0;
    quad.corners[0U].packed_word = 0xbeefU;

    constexpr std::int32_t minimum = std::numeric_limits<
        std::int32_t>::min();
    constexpr std::int32_t maximum = std::numeric_limits<
        std::int32_t>::max();
    const std::int32_t invalid_x[] = {
        -3073, 13312, minimum, maximum
    };

    for (std::int32_t x : invalid_x) {
        expect(i76_terrain_lattice_at(scene, x, 0, sample) ==
                   i76_terrain_lattice_result::invalid_coordinate
               && sample.packed_word == 0xbeefU,
               "invalid X cannot mutate lattice output");
        expect(i76_terrain_lattice_position_at(scene, x, 0, position) ==
                   i76_terrain_lattice_result::invalid_coordinate
               && position.x == 7123.0,
               "invalid X cannot mutate world output");
        expect(i76_terrain_lattice_quad_at(scene, x, 0, quad) ==
                   i76_terrain_lattice_result::invalid_coordinate
               && quad.corners[0U].packed_word == 0xbeefU,
               "invalid X cannot mutate quad output");
        expect(i76_terrain_lattice_at(scene, 0, x, sample) ==
                   i76_terrain_lattice_result::invalid_coordinate
               && sample.packed_word == 0xbeefU,
               "invalid Z cannot mutate lattice output");
    }
    expect(i76_terrain_lattice_quad_at(scene, 13311, 0, quad) ==
               i76_terrain_lattice_result::invalid_coordinate
           && i76_terrain_lattice_quad_at(scene, 0, 13311, quad) ==
               i76_terrain_lattice_result::invalid_coordinate
           && quad.corners[0U].packed_word == 0xbeefU,
           "last sample is valid, but cannot start a full cell");

    scene.cell_pages[1U] = 3U;
    expect(i76_terrain_lattice_at(scene, 128, 0, sample) ==
               i76_terrain_lattice_result::invalid_scene
           && sample.packed_word == 0xbeefU,
           "bad active page ordinal is not a default page");
    expect(i76_terrain_lattice_quad_at(scene, 127, 127, quad) ==
               i76_terrain_lattice_result::invalid_scene
           && quad.corners[0U].packed_word == 0xbeefU,
           "quad rollback after successful first corner");

    scene = make_scene();
    scene.packed_samples.pop_back();
    expect(i76_terrain_lattice_at(scene, 0, 0, sample) ==
               i76_terrain_lattice_result::invalid_scene
           && sample.packed_word == 0xbeefU,
           "truncated owned TER allocation fails closed");
    expect(i76_terrain_lattice_at(scene, -1, -1, sample) ==
               i76_terrain_lattice_result::invalid_scene
           && sample.packed_word == 0xbeefU,
           "even default lookup requires consistent owned TER size");
    expect(i76_terrain_lattice_position_at(scene, 0, 0, position) ==
               i76_terrain_lattice_result::invalid_scene
           && position.x == 7123.0,
           "malformed scene preserves world output");
    expect(i76_terrain_lattice_quad_at(scene, 127, 127, quad) ==
               i76_terrain_lattice_result::invalid_scene
           && quad.corners[0U].packed_word == 0xbeefU,
           "malformed scene preserves whole quad");
}

// -----------------------------------------------------------------------------
// Ensure all results distinguish valid default backing from invalid states.
// -----------------------------------------------------------------------------
static void test_result_names()
{
    expect(std::string_view(i76_terrain_lattice_result_name(
        i76_terrain_lattice_result::ok)) == "ok", "name successful sample");
    expect(std::string_view(i76_terrain_lattice_result_name(
        i76_terrain_lattice_result::default_page)) == "default page",
        "name valid default sample");
    expect(std::string_view(i76_terrain_lattice_result_name(
        i76_terrain_lattice_result::invalid_coordinate)) ==
            "invalid coordinate", "name coordinate failure");
    expect(std::string_view(i76_terrain_lattice_result_name(
        i76_terrain_lattice_result::invalid_scene)) == "invalid scene",
        "name corrupted scene failure");
    expect(std::string_view(i76_terrain_lattice_result_name(
        static_cast<i76_terrain_lattice_result>(255U))) ==
            "unknown lattice result", "name unknown result");
}

// -----------------------------------------------------------------------------
// Test the entire safe global lattice API without a renderer or private files.
// -----------------------------------------------------------------------------
int main()
{
    test_source_coordinates();
    test_default_pages();
    test_world_positions();
    test_page_seams();
    test_failures();
    test_result_names();
    if (failures != 0U) {
        std::cerr << failures << " terrain lattice test(s) failed\n";
        return 1;
    }
    std::cout << "terrain lattice tests passed\n";
    return 0;
}
