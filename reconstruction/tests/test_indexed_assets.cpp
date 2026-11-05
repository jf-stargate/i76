#include "i76/color.h"
#include "i76/command.h"
#include "i76/texture.h"

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

static std::uint32_t failures = 0U;

// -----------------------------------------------------------------------------
// Track every failed invariant without aborting the remaining test cases.
// -----------------------------------------------------------------------------
static void expect(bool condition, const char* label)
{
    if (!condition) {
        std::cerr << "FAIL: " << label << '\n';
        ++failures;
    }
}

// -----------------------------------------------------------------------------
// Append integer fields as little-endian bytes to an authored test resource.
// -----------------------------------------------------------------------------
static void append_u32(std::vector<std::uint8_t>& bytes,
                       std::uint32_t value)
{
    for (std::uint32_t shift = 0U; shift < 32U; shift += 8U) {
        bytes.push_back(static_cast<std::uint8_t>(value >> shift));
    }
}

// -----------------------------------------------------------------------------
// Append the encoded VQM token for one block in scanline tile order.
// -----------------------------------------------------------------------------
static void append_u16(std::vector<std::uint8_t>& bytes,
                       std::uint16_t value)
{
    bytes.push_back(static_cast<std::uint8_t>(value & 0xffU));
    bytes.push_back(static_cast<std::uint8_t>(value >> 8U));
}

// -----------------------------------------------------------------------------
// Create two distinguishable 4x4 CBK tiles and a declared tile count.
// -----------------------------------------------------------------------------
static std::vector<std::uint8_t> make_cbk()
{
    std::vector<std::uint8_t> bytes = {};

    append_u32(bytes, 2U);
    for (std::uint32_t tile = 0U; tile < 2U; ++tile) {
        for (std::uint32_t y = 0U; y < 4U; ++y) {
            for (std::uint32_t x = 0U; x < 4U; ++x) {
                bytes.push_back(static_cast<std::uint8_t>(
                    (tile == 0U ? 10U : 40U) + 4U * y + x));
            }
        }
    }
    return bytes;
}

// -----------------------------------------------------------------------------
// Build a 5x7 VQM with two partial right-edge blocks and bottom clipping.
// -----------------------------------------------------------------------------
static std::vector<std::uint8_t> make_vqm(
    const std::string& dependency = "base.cbk")
{
    std::vector<std::uint8_t> bytes = {};

    append_u32(bytes, 5U);
    append_u32(bytes, 7U);
    for (std::uint32_t i = 0U; i < 16U; ++i) {
        bytes.push_back(i < dependency.size() ?
            static_cast<std::uint8_t>(dependency[i]) : 0U);
    }
    append_u16(bytes, 0U);
    append_u16(bytes, 0x81feU);
    append_u16(bytes, 1U);
    append_u16(bytes, 0U);
    return bytes;
}

// -----------------------------------------------------------------------------
// Verify byte order, solid blocks, clipped tiles and stable failed output.
// -----------------------------------------------------------------------------
static void test_decoder()
{
    std::vector<std::uint8_t> vqm = make_vqm();
    std::vector<std::uint8_t> cbk = make_cbk();
    i76_indexed_texture decoded = {};
    i76_texture_error error = {};
    const i76_texture_result ok = i76_texture_result::ok;

    expect(i76_texture_decode(vqm, cbk, decoded, error) == ok,
           "decode mixed synthetic texture");
    expect(decoded.width == 5U
           && decoded.height == 7U
           && decoded.pixels.size() == 35U
           && decoded.codebook == "base.cbk", "decoded metadata");
    expect(decoded.pixels[0] == 10U
           && decoded.pixels[3] == 13U
           && decoded.pixels[4] == 254U
           && decoded.pixels[20] == 40U
           && decoded.pixels[24] == 10U
           && decoded.pixels[34] == 18U, "tile traversal and clipping");

    vqm[24U] = 2U;
    expect(i76_texture_decode(vqm, cbk, decoded, error) ==
               i76_texture_result::invalid_token
           && error.offset == 24U
           && decoded.width == 5U, "reject invalid codebook ordinal");
    vqm = make_vqm();
    vqm.pop_back();
    expect(i76_texture_decode(vqm, cbk, decoded, error) ==
               i76_texture_result::invalid_vqm
           && decoded.pixels[34U] == 18U, "reject short token plane");
    vqm = make_vqm();
    vqm.push_back(0U);
    expect(i76_texture_decode(vqm, cbk, decoded, error) ==
               i76_texture_result::invalid_vqm, "reject trailing bytes");
    vqm = make_vqm();
    vqm[7U] = 0x80U;
    expect(i76_texture_decode(vqm, cbk, decoded, error) ==
               i76_texture_result::invalid_dimensions,
           "reject flagged source height");
    vqm = make_vqm();
    vqm[0U] = 0U;
    expect(i76_texture_decode(vqm, cbk, decoded, error) ==
               i76_texture_result::invalid_dimensions,
           "reject zero width");
    vqm = make_vqm();
    vqm[0U] = 0xffU;
    vqm[1U] = 0xffU;
    vqm[2U] = 0xffU;
    vqm[3U] = 0xffU;
    expect(i76_texture_decode(vqm, cbk, decoded, error) ==
               i76_texture_result::invalid_dimensions,
           "reject unbounded output");
    vqm = make_vqm("abcdefghijklmnop");
    expect(i76_texture_decode(vqm, cbk, decoded, error) ==
               i76_texture_result::invalid_vqm, "require terminated CBK name");
    vqm = make_vqm();
    cbk[0U] = 1U;
    expect(i76_texture_decode(vqm, cbk, decoded, error) ==
               i76_texture_result::invalid_cbk, "validate CBK declared size");
    cbk = make_cbk();
    cbk.pop_back();
    expect(i76_texture_decode(vqm, cbk, decoded, error) ==
               i76_texture_result::invalid_cbk, "reject short codebook");
    cbk = make_cbk();
    vqm.resize(23U);
    expect(i76_texture_decode(vqm, cbk, decoded, error) ==
               i76_texture_result::invalid_vqm, "reject short header");
}

// -----------------------------------------------------------------------------
// Confirm signed fixed-point wrapping without inventing non-power-of-two math.
// -----------------------------------------------------------------------------
static void test_sampling()
{
    i76_indexed_texture texture = {};
    std::uint8_t texel = 201U;

    texture.width = 4U;
    texture.height = 4U;
    for (std::uint8_t index = 0U; index < 16U; ++index) {
        texture.pixels.push_back(index);
    }
    expect(i76_texture_sample(texture, -65536, 65536, texel)
           && texel == 7U, "negative fixed U wraps to last column");
    expect(i76_texture_sample(texture, -1, -1, texel)
           && texel == 15U, "negative fraction uses arithmetic shift");
    texture.width = 5U;
    expect(!i76_texture_sample(texture, 0, 0, texel)
           && texel == 15U, "non-power-of-two shape explicitly unsupported");
    texture.width = 4U;
    texture.pixels.pop_back();
    expect(!i76_texture_sample(texture, 0, 0, texel),
           "reject inconsistent pixel buffer");
}

// -----------------------------------------------------------------------------
// Verify ACT/LUM/TBL byte contracts and source-255 identity initialization.
// -----------------------------------------------------------------------------
static void test_color()
{
    std::vector<std::uint8_t> act(768U, 0U);
    std::vector<std::uint8_t> lum(65536U, 0U);
    std::vector<std::uint8_t> tbl(65536U, 0U);
    i76_indexed_color_tables tables = {};
    std::uint8_t value = 199U;

    act[0] = 1U;
    act[1] = 63U;
    act[2] = 255U;
    for (std::size_t row = 0U; row < 256U; ++row) {
        for (std::size_t column = 0U; column < 256U; ++column) {
            lum[row * 256U + column] = static_cast<std::uint8_t>(
                row + 3U * column);
            tbl[row * 256U + column] = static_cast<std::uint8_t>(
                row * 5U + column);
        }
    }
    expect(i76_color_decode(act, lum, tbl, tables) == i76_color_result::ok,
           "decode indexed color resources");
    expect(tables.palette.rgb[0] == 1U
           && tables.palette.rgb[1] == 63U
           && tables.palette.rgb[2] == 255U,
           "ACT copied as raw RGB8");
    expect(i76_color_shade(tables, 17U, 0x2f00U, value)
           && value == 66U, "LUM uses masked row plus source column");
    expect(i76_color_compose(tables, 7U, 19U, value)
           && value == 54U, "TBL uses source row and destination column");
    expect(i76_color_compose(tables, 255U, 19U, value)
           && value == 19U
           && tbl[255U * 256U + 19U] != 19U,
           "TBL runtime identity row leaves raw source unchanged");
    act.pop_back();
    expect(i76_color_decode(act, lum, tbl, tables) ==
               i76_color_result::invalid_act
           && tables.has_lum, "ACT error preserves prior state");
    act.push_back(0U);
    lum.pop_back();
    expect(i76_color_decode(act, lum, tbl, tables) ==
               i76_color_result::invalid_lum,
           "invalid LUM extent rejected");
    lum.push_back(0U);
    tbl.pop_back();
    expect(i76_color_decode(act, lum, tbl, tables) ==
               i76_color_result::invalid_tbl,
           "invalid TBL extent rejected");
    tbl.push_back(0U);
    expect(i76_color_decode(act, {}, {}, tables) == i76_color_result::ok
           && !tables.has_lum
           && !tables.has_tbl, "absence is distinct from generation");
    value = 83U;
    expect(!i76_color_shade(tables, 0U, 0U, value)
           && !i76_color_compose(tables, 0U, 0U, value)
           && value == 83U, "missing tables preserve the texel");
}

// -----------------------------------------------------------------------------
// Exercise mounted dependency lookup, failure cleanup and CLI inspection.
// -----------------------------------------------------------------------------
static void test_loader_and_commands()
{
    i76_runtime game = {};
    i76_runtime_config config = {};
    std::vector<std::uint8_t> vqm = make_vqm();
    std::vector<std::uint8_t> cbk = make_cbk();
    std::vector<std::uint8_t> act(768U, 0U);
    std::vector<std::uint8_t> lum(65536U, 7U);
    std::vector<std::uint8_t> tbl(65536U, 0U);
    i76_indexed_texture texture = {};
    i76_indexed_color_tables colors = {};
    i76_texture_error error = {};
    i76_resource_stats stats = {};

    config.tick_rate = 60U;
    expect(i76_runtime_initialize(game, config, i76_make_null_outputs()) ==
               i76_result_code::ok, "initialize fixture");
    expect(i76_resource_add_memory(game.resources, "builtin",
                                   "textures/a.vqm", vqm) ==
               i76_resource_result::ok, "add synthetic VQM");
    expect(i76_texture_read(game.resources, "textures/a.vqm",
                            texture, error) ==
               i76_texture_result::missing_cbk,
           "missing adjacent CBK reported");
    expect(i76_resource_get_stats(game.resources).references == 0U,
           "missing CBK releases VQM");
    expect(i76_resource_add_memory(game.resources, "builtin",
                                   "textures/base.cbk", cbk) ==
               i76_resource_result::ok, "add CBK dependency");
    expect(i76_texture_read(game.resources, "textures/a.vqm",
                            texture, error) == i76_texture_result::ok
           && texture.codebook == "textures/base.cbk"
           && texture.pixels[34U] == 18U, "resolved indexed asset");
    expect(i76_execute_command(game,
        "texture inspect textures/a.vqm").message.find("width=5 height=7")
        != std::string::npos, "inspect through console");
    expect(i76_execute_command(game,
        "texture inspect ../bad.vqm").code ==
               i76_result_code::invalid_argument,
           "reject unsafe texture command path");
    expect(i76_resource_add_memory(game.resources, "builtin",
                                   "palette.act", act) ==
               i76_resource_result::ok, "add ACT");
    expect(i76_resource_add_memory(game.resources, "builtin",
                                   "shade.lum", lum) ==
               i76_resource_result::ok, "add LUM");
    expect(i76_resource_add_memory(game.resources, "builtin",
                                   "blend.tbl", tbl) ==
               i76_resource_result::ok, "add TBL");
    expect(i76_color_read(game.resources, "palette.act", "shade.lum",
                          "blend.tbl", colors) == i76_color_result::ok
           && colors.has_lum
           && colors.has_tbl, "load owned color state");
    expect(i76_execute_command(game,
        "color inspect palette.act shade.lum blend.tbl").message.find(
            "lum=present tbl=present") != std::string::npos,
           "inspect color resources through console");
    expect(i76_color_read(game.resources, "palette.act", "missing.lum",
                          "", colors) == i76_color_result::missing_resource
           && colors.has_lum, "failed color load preserves output");
    stats = i76_resource_get_stats(game.resources);
    expect(stats.references == 0U
           && stats.cached_count == 0U, "all decode leases released");
    expect(i76_runtime_shutdown(game) == i76_result_code::ok,
           "shutdown after asset inspection");
}

// -----------------------------------------------------------------------------
// Write synthetic files for a full-process headless inspection smoke test.
// -----------------------------------------------------------------------------
static bool make_fixture(const std::filesystem::path& directory)
{
    std::error_code error = {};
    std::ofstream vqm = {};
    std::ofstream cbk = {};
    const std::vector<std::uint8_t> source = make_vqm();
    const std::vector<std::uint8_t> codebook = make_cbk();

    std::filesystem::create_directories(directory / "textures", error);
    if (error) {
        return false;
    }
    vqm.open(directory / "textures" / "a.vqm", std::ios::binary);
    vqm.write(reinterpret_cast<const char*>(source.data()),
              static_cast<std::streamsize>(source.size()));
    vqm.close();
    cbk.open(directory / "textures" / "base.cbk", std::ios::binary);
    cbk.write(reinterpret_cast<const char*>(codebook.data()),
              static_cast<std::streamsize>(codebook.size()));
    cbk.close();
    return vqm.good() && cbk.good();
}

// -----------------------------------------------------------------------------
// Run synthetic regression tests or emit a portable headless fixture.
// -----------------------------------------------------------------------------
int main(int argc, char** argv)
{
    if (argc == 3
        && std::string(argv[1]) == "--make-fixture") {
        return make_fixture(argv[2]) ? 0 : 1;
    }
    test_decoder();
    test_sampling();
    test_color();
    test_loader_and_commands();
    if (failures != 0U) {
        std::cerr << failures << " indexed asset test(s) failed\n";
        return 1;
    }
    std::cout << "indexed texture/color tests passed\n";
    return 0;
}
