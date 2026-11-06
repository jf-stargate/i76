#include "i76/command.h"
#include "i76/retail_scene.h"

#include <array>

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

static std::uint32_t failures = 0U;

// -----------------------------------------------------------------------------
// Record failed scene invariants while continuing the remaining diagnostics.
// -----------------------------------------------------------------------------
static void expect(bool condition, const char* message)
{
    if (!condition) {
        std::cerr << "FAIL: " << message << '\n';
        ++failures;
    }
}

// -----------------------------------------------------------------------------
// Serialize a little-endian integer into an authored BWD2 or VQM fixture.
// -----------------------------------------------------------------------------
static void add_u32(std::vector<std::uint8_t>& data, std::uint32_t value)
{
    for (std::uint32_t offset = 0U; offset < 32U; offset += 8U) {
        data.push_back(static_cast<std::uint8_t>(value >> offset));
    }
}

// -----------------------------------------------------------------------------
// Append one tagged BWD2 record with the serialized total byte length.
// -----------------------------------------------------------------------------
static void add_chunk(std::vector<std::uint8_t>& target,
                      std::string_view tag,
                      const std::vector<std::uint8_t>& body)
{
    for (std::size_t index = 0U; index < 4U; ++index) {
        target.push_back(static_cast<std::uint8_t>(tag[index]));
    }
    add_u32(target, static_cast<std::uint32_t>(body.size() + 8U));
    target.insert(target.end(), body.begin(), body.end());
}

// -----------------------------------------------------------------------------
// Append a revision-bearing BWD2 chunk for an authored nested container.
// -----------------------------------------------------------------------------
static void add_revision(std::vector<std::uint8_t>& data,
                         std::string_view tag,
                         std::uint32_t revision)
{
    std::vector<std::uint8_t> payload = {};

    add_u32(payload, revision);
    add_chunk(data, tag, payload);
}

// -----------------------------------------------------------------------------
// Fill one WRLD name slot with its validated 13-byte source representation.
// -----------------------------------------------------------------------------
static void put_name(std::vector<std::uint8_t>& payload,
                     std::size_t offset,
                     std::string_view name)
{
    for (std::size_t index = 0U;
         index < name.size()
         && index < 13U;
         ++index) {
        payload[offset + index] = static_cast<std::uint8_t>(name[index]);
    }
}

// -----------------------------------------------------------------------------
// Build a candidate WREV-9 WRLD/TDEF mission from independent synthetic data.
// -----------------------------------------------------------------------------
static std::vector<std::uint8_t> make_mission(
    std::string_view palette = "palette.act",
    std::string_view lum = "shade.lum",
    std::string_view tbl = "blend.tbl",
    std::uint32_t world_revision = 9U,
    std::size_t wrld_bytes = 331U,
    bool has_world = true,
    bool has_wrld = true,
    bool has_wrev = true,
    std::string_view ter_name = "M06.TER",
    bool bad_page = false,
    bool duplicate_world = false)
{
    std::vector<std::uint8_t> mission = {};
    std::vector<std::uint8_t> world = {};
    std::vector<std::uint8_t> terrain = {};
    std::vector<std::uint8_t> wrld(wrld_bytes, 0U);
    std::vector<std::uint8_t> map(6401U, 0xffU);
    std::vector<std::uint8_t> zone(14U, 0U);

    add_chunk(mission, "BWD2", {});
    add_revision(mission, "REV", 2U);
    if (has_world) {
        if (has_wrev) {
            add_revision(world, "WREV", world_revision);
        }
        if (has_wrld) {
            if (wrld.size() >= 69U) {
                put_name(wrld, 0x1eU, palette);
                put_name(wrld, 0x2bU, lum);
                put_name(wrld, 0x38U, tbl);
            }
            add_chunk(world, "WRLD", wrld);
        }
        add_chunk(world, "EXIT", {});
        add_chunk(mission, "WDEF", world);
        if (duplicate_world) {
            add_chunk(mission, "WDEF", world);
        }
    }
    add_revision(terrain, "TREV", 4U);
    map[0] = 1U;
    map[1] = bad_page ? 1U : 0U;
    add_chunk(terrain, "ZMAP", map);
    zone[0] = 0x5aU;
    put_name(zone, 1U, ter_name);
    add_chunk(terrain, "ZONE", zone);
    add_chunk(terrain, "EXIT", {});
    add_chunk(mission, "TDEF", terrain);
    add_chunk(mission, "EXIT", {});
    return mission;
}

// -----------------------------------------------------------------------------
// Supply a 128-by-128 terrain page with a known surface flag and height.
// -----------------------------------------------------------------------------
static std::vector<std::uint8_t> make_ter()
{
    std::vector<std::uint8_t> bytes(i76_retail_terrain_page_bytes, 0U);

    bytes[0] = 0x23U;
    bytes[1] = 0xf1U;
    return bytes;
}

// -----------------------------------------------------------------------------
// Supply a four-by-four indexed VQM and a single fully authored CBK tile.
// -----------------------------------------------------------------------------
static std::vector<std::uint8_t> make_vqm()
{
    std::vector<std::uint8_t> bytes = {};

    add_u32(bytes, 4U);
    add_u32(bytes, 4U);
    const std::string dependency = "b.cbk";
    for (std::size_t index = 0U; index < 16U; ++index) {
        bytes.push_back(index < dependency.size() ?
            static_cast<std::uint8_t>(dependency[index]) : 0U);
    }
    bytes.push_back(0U);
    bytes.push_back(0U);
    return bytes;
}

// -----------------------------------------------------------------------------
// Construct one named CBK tile with distinct output indices for sampling.
// -----------------------------------------------------------------------------
static std::vector<std::uint8_t> make_cbk()
{
    std::vector<std::uint8_t> bytes = {};

    add_u32(bytes, 1U);
    for (std::uint8_t index = 0U; index < 16U; ++index) {
        bytes.push_back(static_cast<std::uint8_t>(11U + index));
    }
    return bytes;
}

// -----------------------------------------------------------------------------
// Populate the memory resource store with all independent scene dependencies.
// -----------------------------------------------------------------------------
static void add_assets(i76_resource_store& resources,
                       std::string_view mission = "miss16/m06.msn",
                       std::string_view palette = "palette.act",
                       std::string_view lum = "shade.lum",
                       std::string_view tbl = "blend.tbl")
{
    const std::vector<std::uint8_t> bytes = make_mission(palette, lum, tbl);
    std::vector<std::uint8_t> act(768U, 0U);
    std::vector<std::uint8_t> light(65536U, 0U);
    std::vector<std::uint8_t> blend(65536U, 0U);
    const std::vector<std::uint8_t> ter = make_ter();
    const std::vector<std::uint8_t> vqm = make_vqm();
    const std::vector<std::uint8_t> cbk = make_cbk();

    act[0] = 31U;
    light[0x1f00U + 11U] = 64U;
    blend[(64U << 8U) | 19U] = 147U;
    expect(i76_resource_add_memory(resources, "builtin", mission, bytes) ==
               i76_resource_result::ok, "add mission");
    expect(i76_resource_add_memory(resources, "builtin", "miss16/m06.ter",
                                   ter) == i76_resource_result::ok,
           "add TER");
    expect(i76_resource_add_memory(resources, "builtin", "textures/a.vqm",
                                   vqm) == i76_resource_result::ok,
           "add VQM");
    expect(i76_resource_add_memory(resources, "builtin", "textures/b.cbk",
                                   cbk) == i76_resource_result::ok,
           "add CBK");
    expect(i76_resource_add_memory(resources, "builtin", "palette.act",
                                   act) == i76_resource_result::ok,
           "add ACT");
    expect(i76_resource_add_memory(resources, "builtin", "shade.lum",
                                   light) == i76_resource_result::ok,
           "add LUM");
    expect(i76_resource_add_memory(resources, "builtin", "blend.tbl",
                                   blend) == i76_resource_result::ok,
           "add TBL");
}

// -----------------------------------------------------------------------------
// Register a mission variant under a new logical resource name.
// -----------------------------------------------------------------------------
static void add_variant(i76_resource_store& store,
                        std::string_view name,
                        const std::vector<std::uint8_t>& bytes)
{
    expect(i76_resource_add_memory(store, "builtin", name, bytes) ==
               i76_resource_result::ok, "register WRLD variant");
}

// -----------------------------------------------------------------------------
// Check bounded WRLD revisions, malformed names, missing assets and rollback.
// -----------------------------------------------------------------------------
static void test_rejections()
{
    i76_resource_store resources = {};
    i76_prepared_retail_scene prepared = {};
    i76_retail_scene_error error = {};

    expect(i76_retail_scene_prepare(resources, "miss16/m06.msn",
                                    "textures/a.vqm", prepared, error) ==
               i76_retail_scene_result::not_initialized,
           "not initialized");
    expect(i76_resource_initialize(resources) == i76_resource_result::ok,
           "initialize store");
    expect(i76_resource_mount_memory(resources, "builtin") ==
               i76_resource_result::ok, "mount memory");
    expect(i76_retail_scene_prepare(resources, "miss16/m06.msn",
                                    "textures/a.vqm", prepared, error) ==
               i76_retail_scene_result::missing_mission,
           "missing mission");
    add_assets(resources);
    add_variant(resources, "miss16/v08.msn",
                make_mission("palette.act", "shade.lum", "blend.tbl", 8U));
    add_variant(resources, "miss16/short.msn",
                make_mission("palette.act", "shade.lum", "blend.tbl",
                             9U, 330U));
    add_variant(resources, "miss16/none.msn",
                make_mission("palette.act", "shade.lum", "blend.tbl",
                             9U, 331U, false));
    add_variant(resources, "miss16/no_wrld.msn",
                make_mission("palette.act", "shade.lum", "blend.tbl",
                             9U, 331U, true, false));
    add_variant(resources, "miss16/no_wrev.msn",
                make_mission("palette.act", "shade.lum", "blend.tbl",
                             9U, 331U, true, true, false));
    add_variant(resources, "miss16/blank.msn",
                make_mission("", "shade.lum", "blend.tbl"));
    add_variant(resources, "miss16/unsafe.msn",
                make_mission("../bad.act", "shade.lum", "blend.tbl"));
    add_variant(resources, "miss16/unterm.msn",
                make_mission("abcdefghijklm", "shade.lum", "blend.tbl"));
    add_variant(resources, "miss16/absent.msn",
                make_mission("missing.act", "shade.lum", "blend.tbl"));
    add_variant(resources, "miss16/whitespace.msn",
                make_mission("bad act", "shade.lum", "blend.tbl"));
    add_variant(resources, "miss16/double.msn",
                make_mission("palette.act", "shade.lum", "blend.tbl",
                             9U, 331U, true, true, true, "M06.TER",
                             false, true));
    add_variant(resources, "miss16/invalid.msn", {0U, 1U, 2U});
    add_variant(resources, "miss16/no_ter.msn",
                make_mission("palette.act", "shade.lum", "blend.tbl",
                             9U, 331U, true, true, true, "MISSING.TER"));
    add_variant(resources, "miss16/bad_page.msn",
                make_mission("palette.act", "shade.lum", "blend.tbl",
                             9U, 331U, true, true, true, "M06.TER", true));
    add_variant(resources, "miss16/bad_act.msn",
                make_mission("bad.act", "shade.lum", "blend.tbl"));
    add_variant(resources, "miss16/bad_lum.msn",
                make_mission("palette.act", "bad.lum", "blend.tbl"));
    add_variant(resources, "miss16/bad_tbl.msn",
                make_mission("palette.act", "shade.lum", "bad.tbl"));
    const std::vector<std::uint8_t> short_act(767U, 0U);
    const std::vector<std::uint8_t> short_lum(65535U, 0U);
    const std::vector<std::uint8_t> short_tbl(65535U, 0U);
    expect(i76_resource_add_memory(resources, "builtin", "bad.act",
                                   short_act) == i76_resource_result::ok,
           "register invalid ACT");
    expect(i76_resource_add_memory(resources, "builtin", "bad.lum",
                                   short_lum) == i76_resource_result::ok,
           "register invalid LUM");
    expect(i76_resource_add_memory(resources, "builtin", "bad.tbl",
                                   short_tbl) == i76_resource_result::ok,
           "register invalid TBL");
    std::vector<std::uint8_t> bad_vqm = make_vqm();
    bad_vqm[24U] = 1U;
    expect(i76_resource_add_memory(resources, "builtin", "textures/bad.vqm",
                                   bad_vqm) == i76_resource_result::ok,
           "register invalid VQM token");

    const std::string_view cases[] = {
        "miss16/v08.msn", "miss16/short.msn", "miss16/none.msn",
        "miss16/no_wrld.msn", "miss16/no_wrev.msn", "miss16/blank.msn",
        "miss16/unsafe.msn", "miss16/unterm.msn",
        "miss16/absent.msn", "miss16/whitespace.msn",
        "miss16/double.msn", "miss16/invalid.msn",
        "miss16/no_ter.msn", "miss16/bad_page.msn",
        "miss16/bad_act.msn", "miss16/bad_lum.msn",
        "miss16/bad_tbl.msn"
    };
    const i76_retail_scene_result codes[] = {
        i76_retail_scene_result::unsupported_world,
        i76_retail_scene_result::unsupported_world,
        i76_retail_scene_result::missing_world,
        i76_retail_scene_result::missing_world,
        i76_retail_scene_result::unsupported_world,
        i76_retail_scene_result::invalid_color,
        i76_retail_scene_result::invalid_color,
        i76_retail_scene_result::invalid_color,
        i76_retail_scene_result::missing_resource,
        i76_retail_scene_result::invalid_color,
        i76_retail_scene_result::unsupported_world,
        i76_retail_scene_result::unsupported_world,
        i76_retail_scene_result::missing_terrain,
        i76_retail_scene_result::invalid_terrain,
        i76_retail_scene_result::invalid_color,
        i76_retail_scene_result::invalid_color,
        i76_retail_scene_result::invalid_color,
    };
    for (std::size_t index = 0U; index < std::size(cases); ++index) {
        expect(i76_retail_scene_prepare(resources, cases[index],
                                        "textures/a.vqm", prepared, error) ==
                   codes[index], "reject unsupported WRLD or missing color");
        expect(prepared.scene == nullptr
               && i76_resource_get_stats(resources).references == 0U,
               "failed WRLD preparation leaves no leases");
    }
    expect(i76_retail_scene_prepare(resources, "miss16/m06.msn",
                                    "textures/absent.vqm", prepared, error) ==
               i76_retail_scene_result::missing_resource,
           "require an actual selected texture");
    expect(i76_retail_scene_prepare(resources, "miss16/m06.msn",
                                    "textures/bad.vqm", prepared, error) ==
               i76_retail_scene_result::invalid_texture,
           "reject an invalid selected VQM token");
    expect(i76_retail_scene_prepare(resources, "miss16/m06.msn", "",
                                    prepared, error) ==
               i76_retail_scene_result::invalid_argument,
           "empty explicit texture is not automatically inferred");
    expect(prepared.scene == nullptr
           && i76_resource_get_stats(resources).references == 0U,
           "missing texture unwinds complete preparation");
    expect(i76_resource_shutdown(resources) == i76_resource_result::ok,
           "shutdown rejected-fixture store");
}

// -----------------------------------------------------------------------------
// Validate the complete sample contract and transactional activation behavior.
// -----------------------------------------------------------------------------
static void test_loaded_scene()
{
    i76_resource_store resources = {};
    i76_prepared_retail_scene prepared = {};
    i76_active_retail_scene active = {};
    i76_retail_scene_error error = {};
    i76_retail_surface_sample sample = {};

    expect(i76_resource_initialize(resources) == i76_resource_result::ok,
           "initialize complete scene store");
    expect(i76_resource_mount_memory(resources, "builtin") ==
               i76_resource_result::ok, "mount complete scene store");
    add_assets(resources);
    expect(i76_retail_scene_prepare(resources, "miss16/m06.msn",
                                    "textures/a.vqm", prepared, error) ==
               i76_retail_scene_result::ok
           && prepared.scene != nullptr, "prepare combined scene");
    expect(prepared.scene->terrain.page_count == 1U
           && prepared.scene->sample_texture.width == 4U
           && prepared.scene->sample_texture.codebook == "textures/b.cbk"
           && prepared.scene->palette_name == "palette.act"
           && prepared.scene->luminance_name == "shade.lum"
           && prepared.scene->blend_name == "blend.tbl"
           && prepared.scene->colors.has_lum
           && prepared.scene->colors.has_tbl,
           "terrain, color and texture are owned together");
    expect(i76_resource_get_stats(resources).references == 0U,
           "no resource leases survive scene preparation");
    expect(i76_retail_scene_prepare(resources, "miss16/m06.msn",
                                    "textures/a.vqm", prepared, error) ==
               i76_retail_scene_result::busy,
           "prevent overwriting prepared scene");
    expect(i76_retail_scene_activate(prepared, active) ==
               i76_retail_scene_result::ok
           && prepared.scene == nullptr
           && active.scene != nullptr, "activate by moving owned scene");
    expect(i76_retail_scene_sample(*active.scene, 0U, 0U, 0, 0, 0x3f00U,
                                   19U, true, true, sample)
           && sample.terrain.height == 0x123U
           && sample.terrain.surface_flag
           && sample.terrain.surface_class == 7U
           && sample.texel == 11U
           && sample.shaded == 64U
           && sample.composite == 147U,
           "terrain word and shade/compose byte indices agree");
    sample.composite = 199U;
    expect(!i76_retail_scene_sample(*active.scene, 1U, 0U, 0, 0, 0U,
                                    19U, true, true, sample)
           && sample.composite == 199U,
           "unmapped page is rejected without modifying caller");
    expect(i76_retail_scene_sample(*active.scene, 0U, 0U, 0, 0,
                                   0U, 19U, true, false, sample)
           && sample.shaded == 0U
           && sample.composite == 0U,
           "zero-filled shade row remains deterministic");
    expect(i76_retail_scene_activate(prepared, active) ==
               i76_retail_scene_result::not_prepared
           && active.scene != nullptr,
           "failed activation retains old active scene");
    expect(i76_retail_scene_prepare(resources, "miss16/m06.msn",
                                    "textures/a.vqm", prepared, error) ==
               i76_retail_scene_result::ok, "prepare replacement scene");
    expect(i76_retail_scene_discard(prepared) ==
               i76_retail_scene_result::ok
           && active.scene != nullptr, "discard does not unload active");
    expect(i76_retail_scene_discard(prepared) ==
               i76_retail_scene_result::not_prepared, "repeat discard");
    expect(i76_retail_scene_unload(active) ==
               i76_retail_scene_result::ok
           && active.scene == nullptr, "unload clears owned scene");
    expect(i76_retail_scene_unload(active) ==
               i76_retail_scene_result::not_loaded, "repeat unload");
    expect(i76_resource_get_stats(resources).references == 0U,
           "scene teardown does not own resource leases");
    expect(i76_resource_shutdown(resources) == i76_resource_result::ok,
           "shutdown after scene lifecycle");
}

// -----------------------------------------------------------------------------
// Verify absent LUM/TBL are explicit and never silently synthesized.
// -----------------------------------------------------------------------------
static void test_optional_tables()
{
    i76_resource_store resources = {};
    i76_prepared_retail_scene prepared = {};
    i76_retail_scene_error error = {};
    i76_retail_surface_sample sample = {};

    expect(i76_resource_initialize(resources) == i76_resource_result::ok,
           "initialize optional-resource store");
    expect(i76_resource_mount_memory(resources, "builtin") ==
               i76_resource_result::ok, "mount optional-resource store");
    add_assets(resources, "miss16/optional.msn", "palette.act", "", "");
    expect(i76_retail_scene_prepare(resources, "miss16/optional.msn",
                                    "textures/a.vqm", prepared, error) ==
               i76_retail_scene_result::ok
           && !prepared.scene->colors.has_lum
           && !prepared.scene->colors.has_tbl,
           "absent serialized tables are not invented");
    expect(i76_retail_scene_sample(*prepared.scene, 0U, 0U,
                                   0, 0, 0x1f00U, 19U,
                                   false, false, sample)
           && sample.texel == 11U
           && sample.shaded == 11U
           && sample.composite == 11U,
           "explicit unshaded sample succeeds without tables");
    sample.composite = 200U;
    expect(!i76_retail_scene_sample(*prepared.scene, 0U, 0U,
                                    0, 0, 0x1f00U, 19U,
                                    true, false, sample)
           && sample.composite == 200U,
           "cannot shade without LUM");
    expect(!i76_retail_scene_sample(*prepared.scene, 0U, 0U,
                                    0, 0, 0x1f00U, 19U,
                                    false, true, sample)
           && sample.composite == 200U,
           "cannot compose without TBL");
    expect(i76_retail_scene_discard(prepared) ==
               i76_retail_scene_result::ok, "discard optional scene");
    expect(i76_resource_shutdown(resources) == i76_resource_result::ok,
           "shutdown optional store");
}

// -----------------------------------------------------------------------------
// Exercise console commands and runtime shutdown without any device backend.
// -----------------------------------------------------------------------------
static void test_commands()
{
    i76_runtime game = {};
    i76_runtime_config configuration = {};

    configuration.tick_rate = 60U;
    expect(i76_runtime_initialize(game, configuration,
                                  i76_make_null_outputs()) ==
               i76_result_code::ok, "initialize headless runtime");
    add_assets(game.resources);
    expect(i76_execute_command(game, "scene activate").code ==
               i76_result_code::invalid_argument,
           "reject scene activate without preparation");
    expect(i76_execute_command(game,
        "scene prepare miss16/m06.msn textures/a.vqm").code ==
               i76_result_code::ok, "prepare through console");
    expect(i76_execute_command(game, "scene status").message.find(
        "prepared=miss16/m06.msn") != std::string::npos,
        "pending scene is reported");
    expect(i76_execute_command(game, "scene activate").code ==
               i76_result_code::ok, "activate through console");
    expect(i76_execute_command(game, "scene status").message.find(
        "texture=textures/a.vqm") != std::string::npos,
        "active combined texture is reported");
    expect(i76_execute_command(game, "scene status").message.find(
        "ACT=palette.act LUM=present TBL=present") != std::string::npos,
        "active palette and tables are reported");
    expect(i76_world_count(game.world) == 0U
           && !game.active_level.loaded
           && !game.active_terrain.loaded,
           "scene stage does not fabricate level or world activation");
    expect(i76_execute_command(game, "scene unrecognized").code ==
               i76_result_code::invalid_argument,
           "unknown scene action is rejected");
    expect(i76_execute_command(game, "scene unload").code ==
               i76_result_code::ok, "unload through console");
    expect(i76_execute_command(game, "scene status").message.find(
        "active=none prepared=none") != std::string::npos,
        "empty scene status");
    expect(i76_execute_command(game,
        "scene prepare miss16/m06.msn textures/a.vqm").code ==
               i76_result_code::ok, "prepare pending scene for shutdown");
    expect(i76_runtime_shutdown(game) == i76_result_code::ok
           && game.prepared_retail_scene.scene == nullptr,
           "shutdown discards pending scene before resource store");
    expect(i76_runtime_initialize(game, configuration,
                                  i76_make_null_outputs()) ==
               i76_result_code::ok
           && game.active_retail_scene.scene == nullptr,
           "restart with an empty combined scene");
    expect(i76_runtime_shutdown(game) == i76_result_code::ok,
           "second clean shutdown");
}

// -----------------------------------------------------------------------------
// Persist only authored fixtures for a real-process headless integration test.
// -----------------------------------------------------------------------------
static bool write_file(const std::filesystem::path& path,
                       const std::vector<std::uint8_t>& bytes)
{
    std::ofstream stream(path, std::ios::binary | std::ios::trunc);

    if (!stream) {
        return false;
    }
    stream.write(reinterpret_cast<const char*>(bytes.data()),
                 static_cast<std::streamsize>(bytes.size()));
    stream.close();
    return stream.good();
}

// -----------------------------------------------------------------------------
// Create a synthetic directory representing all source-selected scene assets.
// -----------------------------------------------------------------------------
static bool make_fixture(const std::filesystem::path& root)
{
    std::error_code error = {};
    std::vector<std::uint8_t> act(768U, 0U);
    std::vector<std::uint8_t> lum(65536U, 0U);
    std::vector<std::uint8_t> tbl(65536U, 0U);

    std::filesystem::create_directories(root / "miss16", error);
    if (error) {
        return false;
    }
    std::filesystem::create_directories(root / "textures", error);
    if (error) {
        return false;
    }
    lum[0x1f00U + 11U] = 64U;
    tbl[(64U << 8U) | 19U] = 147U;
    return write_file(root / "miss16/m06.msn", make_mission())
           && write_file(root / "miss16/m06.ter", make_ter())
           && write_file(root / "textures/a.vqm", make_vqm())
           && write_file(root / "textures/b.cbk", make_cbk())
           && write_file(root / "palette.act", act)
           && write_file(root / "shade.lum", lum)
           && write_file(root / "blend.tbl", tbl);
}

// -----------------------------------------------------------------------------
// Run synthetic unit tests or emit reusable headless filesystem fixtures.
// -----------------------------------------------------------------------------
int main(int argc, char** argv)
{
    if (argc == 3
        && std::string(argv[1]) == "--make-fixture") {
        return make_fixture(argv[2]) ? 0 : 1;
    }
    test_rejections();
    test_loaded_scene();
    test_optional_tables();
    test_commands();
    if (failures != 0U) {
        std::cerr << failures << " retail scene tests failed\n";
        return 1;
    }
    std::cout << "combined retail scene tests passed\n";
    return 0;
}
