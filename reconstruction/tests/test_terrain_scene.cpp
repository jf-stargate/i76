#include "i76/command.h"
#include "i76/terrain_scene.h"

#include <array>
#include <cstdint>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

static std::uint32_t failures = 0U;

// -----------------------------------------------------------------------------
// Count test failures without hiding later lifecycle or validation failures.
// -----------------------------------------------------------------------------
static void expect(bool condition, const char* label)
{
    if (!condition) {
        std::cerr << "FAIL: " << label << '\n';
        ++failures;
    }
}

// -----------------------------------------------------------------------------
// Append a little-endian 32-bit integer to a synthetic BWD2 fixture.
// -----------------------------------------------------------------------------
static void append_u32(std::vector<std::uint8_t>& bytes,
                       std::uint32_t value)
{
    for (std::uint32_t shift = 0U; shift < 32U; shift += 8U) {
        bytes.push_back(static_cast<std::uint8_t>(value >> shift));
    }
}

// -----------------------------------------------------------------------------
// Append a BWD2 record, explicitly zero-padding short FourCC views.
// -----------------------------------------------------------------------------
static void append_chunk(std::vector<std::uint8_t>& destination,
                         std::string_view tag,
                         const std::vector<std::uint8_t>& body)
{
    for (std::size_t index = 0U; index < 4U; ++index) {
        destination.push_back(index < tag.size() ?
            static_cast<std::uint8_t>(tag[index]) : 0U);
    }
    append_u32(destination, static_cast<std::uint32_t>(body.size() + 8U));
    destination.insert(destination.end(), body.begin(), body.end());
}

// -----------------------------------------------------------------------------
// Check FourCC padding without relying on a terminator beyond the input view.
// -----------------------------------------------------------------------------
static void test_chunk_tags()
{
    const std::array<char, 4U> storage = {'R', 'E', 'V', '!'};
    std::vector<std::uint8_t> bytes = {};
    const std::vector<std::uint8_t> revision = {
        'R', 'E', 'V', 0U, 12U, 0U, 0U, 0U, 2U, 0U, 0U, 0U
    };
    const std::vector<std::uint8_t> full = {
        'R', 'E', 'V', '!', 8U, 0U, 0U, 0U
    };
    const std::vector<std::uint8_t> empty = {
        0U, 0U, 0U, 0U, 8U, 0U, 0U, 0U
    };

    append_chunk(bytes, std::string_view(storage.data(), 3U),
                 {2U, 0U, 0U, 0U});
    expect(bytes == revision, "short FourCC is padded inside fixture writer");
    bytes.clear();
    append_chunk(bytes, std::string_view(storage.data(), storage.size()), {});
    expect(bytes == full, "four-byte FourCC is preserved without terminator");
    bytes.clear();
    append_chunk(bytes, std::string_view{}, {});
    expect(bytes == empty, "empty FourCC is zero-padded without reading it");
}

// -----------------------------------------------------------------------------
// Construct a four-byte revision record for the BWD2 container.
// -----------------------------------------------------------------------------
static void append_revision(std::vector<std::uint8_t>& destination,
                            std::string_view tag,
                            std::uint32_t version)
{
    std::vector<std::uint8_t> value = {};

    append_u32(value, version);
    append_chunk(destination, tag, value);
}

// -----------------------------------------------------------------------------
// Build a minimal retail-shaped mission containing ZMAP and ZONE records.
// -----------------------------------------------------------------------------
static std::vector<std::uint8_t> make_mission(
    std::string_view terrain_name,
    bool include_map = true,
    bool include_zone = true,
    bool invalid_page = false)
{
    std::vector<std::uint8_t> mission = {};
    std::vector<std::uint8_t> terrain = {};
    std::vector<std::uint8_t> zmap(6401U, 0xffU);
    std::vector<std::uint8_t> zone(14U, 0U);

    append_chunk(mission, "BWD2", {});
    append_revision(mission, "REV", 2U);
    append_revision(terrain, "TREV", 4U);
    zmap[0] = 2U;
    zmap[1] = invalid_page ? 2U : 1U;
    zmap[2] = 0U;
    if (include_map) {
        append_chunk(terrain, "ZMAP", zmap);
    }
    zone[0] = 0xa5U;
    for (std::size_t index = 0U;
         index < terrain_name.size()
         && index < 13U;
         ++index) {
        zone[1U + index] = static_cast<std::uint8_t>(terrain_name[index]);
    }
    if (include_zone) {
        append_chunk(terrain, "ZONE", zone);
    }
    append_chunk(terrain, "EXIT", {});
    append_chunk(mission, "TDEF", terrain);
    append_chunk(mission, "EXIT", {});
    return mission;
}

// -----------------------------------------------------------------------------
// Build two packed terrain pages with distinguishable sample attributes.
// -----------------------------------------------------------------------------
static std::vector<std::uint8_t> make_ter()
{
    std::vector<std::uint8_t> ter(2U * i76_retail_terrain_page_bytes, 0U);
    std::size_t second = i76_retail_terrain_page_bytes;

    ter[0] = 0x23U;
    ter[1] = 0xf1U; // Page 0 sample 0: height291, flag1, class7.
    ter[second] = 0xbcU;
    ter[second + 1U] = 0x8aU; // Page 1: height2748, flag0, class4.
    return ter;
}

// -----------------------------------------------------------------------------
// Populate the existing memory provider with a synthetic retail mission.
// -----------------------------------------------------------------------------
static void add_mission(i76_resource_store& resources,
                        std::string_view name,
                        std::string_view sidecar,
                        bool include_map = true,
                        bool include_zone = true,
                        bool bad_page = false)
{
    const std::vector<std::uint8_t> bytes =
        make_mission(sidecar, include_map, include_zone, bad_page);

    expect(i76_resource_add_memory(resources, "builtin", name, bytes) ==
               i76_resource_result::ok, "register synthetic mission");
}

// -----------------------------------------------------------------------------
// Verify missing resources and malformed ZMAP/TER leave state unchanged.
// -----------------------------------------------------------------------------
static void test_failures()
{
    i76_resource_store resources = {};
    i76_prepared_terrain prepared = {};
    i76_terrain_error error = {};
    const std::vector<std::uint8_t> ter = make_ter();
    std::vector<std::uint8_t> short_ter = ter;

    expect(i76_terrain_prepare(resources, "miss16/m06.msn", prepared,
                               error) == i76_terrain_result::not_initialized,
           "reject uninitialized resource store");
    expect(i76_resource_initialize(resources) == i76_resource_result::ok,
           "initialize resource store");
    expect(i76_resource_mount_memory(resources, "builtin") ==
               i76_resource_result::ok, "mount memory fixture");
    expect(i76_terrain_prepare(resources, "miss16/m06.msn", prepared,
                               error) == i76_terrain_result::missing_mission,
           "reject missing mission");
    add_mission(resources, "miss16/m06.msn", "M06.TER");
    expect(i76_terrain_prepare(resources, "miss16/m06.msn", prepared,
                               error) == i76_terrain_result::missing_terrain,
           "reject missing TER sidecar");
    short_ter.pop_back();
    add_mission(resources, "miss16/m07.msn", "M07.TER");
    expect(i76_resource_add_memory(resources, "builtin", "miss16/m07.ter",
                                   short_ter) == i76_resource_result::ok,
           "register truncated TER");
    expect(i76_terrain_prepare(resources, "miss16/m07.msn", prepared,
                               error) == i76_terrain_result::invalid_terrain,
           "reject truncated TER before publication");
    add_mission(resources, "miss16/m08.msn", "M08.TER", true, true, true);
    expect(i76_terrain_prepare(resources, "miss16/m08.msn", prepared,
                               error) == i76_terrain_result::invalid_terrain,
           "reject out-of-range ZMAP page reference");
    add_mission(resources, "miss16/m09.msn", "M09.TER", false);
    expect(i76_terrain_prepare(resources, "miss16/m09.msn", prepared,
                               error) == i76_terrain_result::missing_terrain,
           "reject missing ZMAP without guessing page count");
    expect(!prepared.ready
           && prepared.scene.packed_samples.empty()
           && i76_resource_get_stats(resources).references == 0U,
           "failed preparation leaves no scene or leases");
    expect(i76_resource_shutdown(resources) == i76_resource_result::ok,
           "shutdown cleanly after failures");
}

// -----------------------------------------------------------------------------
// Validate owned samples, serialized ordinals, commit and repeat teardown.
// -----------------------------------------------------------------------------
static void test_lifecycle()
{
    i76_resource_store resources = {};
    i76_prepared_terrain prepared = {};
    i76_active_terrain active = {};
    i76_terrain_error error = {};
    i76_terrain_sample sample = {};
    const std::vector<std::uint8_t> ter = make_ter();

    expect(i76_resource_initialize(resources) == i76_resource_result::ok,
           "initialize lifecycle resource store");
    expect(i76_resource_mount_memory(resources, "builtin") ==
               i76_resource_result::ok, "mount lifecycle memory");
    add_mission(resources, "miss16/m06.msn", "M06.TER");
    expect(i76_resource_add_memory(resources, "builtin", "miss16/m06.ter",
                                   ter) == i76_resource_result::ok,
           "register complete TER sidecar");
    expect(i76_terrain_prepare(resources, "miss16/m06.msn", prepared,
                               error) == i76_terrain_result::ok,
           "prepare owned packed scene");
    expect(prepared.ready
           && prepared.scene.mission_name == "miss16/m06.msn"
           && prepared.scene.terrain_name == "miss16/m06.ter"
           && prepared.scene.page_count == 2U
           && prepared.scene.mapped_cells == 2U
           && prepared.scene.referenced_pages == 2U
           && prepared.scene.packed_samples.size() ==
               2U * i76_retail_terrain_page_samples,
           "prepare typed terrain map and both declared pages");
    expect(i76_resource_get_stats(resources).references == 0U,
           "prepared scene owns sample data rather than resource leases");
    expect(i76_terrain_prepare(resources, "miss16/m06.msn", prepared,
                               error) == i76_terrain_result::busy,
           "prevent overwrite of pending scene");
    expect(i76_terrain_activate(prepared, active) == i76_terrain_result::ok
           && active.loaded
           && !prepared.ready, "activate prepared scene without copying");
    expect(i76_terrain_sample_at(active.scene, 0U, 0U, sample)
           && sample.height == 0xabcU
           && !sample.surface_flag
           && sample.surface_class == 4U,
           "page 1 first sample decoded from selected cell");
    expect(i76_terrain_sample_at(active.scene, 1U, 0U, sample)
           && sample.height == 0x123U
           && sample.surface_flag
           && sample.surface_class == 7U,
           "page 0 special flag and class are preserved");
    sample.height = 77U;
    expect(!i76_terrain_sample_at(active.scene, 2U, 0U, sample)
           && sample.height == 77U, "unmapped cell does not mutate result");
    expect(!i76_terrain_sample_at(active.scene, 6400U, 0U, sample)
           && !i76_terrain_sample_at(active.scene, 0U,
                                      i76_retail_terrain_page_samples, sample)
           && sample.height == 77U, "all indexing errors are bounded");
    expect(i76_terrain_activate(prepared, active) ==
               i76_terrain_result::not_prepared
           && active.loaded, "failed activation preserves active scene");
    expect(i76_terrain_prepare(resources, "miss16/m06.msn", prepared,
                               error) == i76_terrain_result::ok,
           "prepare replacement without disturbing active scene");
    expect(i76_terrain_discard(prepared) == i76_terrain_result::ok
           && active.loaded, "discard pending replacement only");
    expect(i76_terrain_discard(prepared) ==
               i76_terrain_result::not_prepared,
           "repeat discard has defined status");
    expect(i76_terrain_unload(active) == i76_terrain_result::ok
           && !active.loaded
           && active.scene.packed_samples.empty(),
           "unload active scene clears page storage");
    expect(i76_terrain_unload(active) == i76_terrain_result::not_loaded,
           "repeat unload has defined status");
    expect(i76_resource_shutdown(resources) == i76_resource_result::ok,
           "terrain-owned data requires no persistent leases");
}

// -----------------------------------------------------------------------------
// Exercise terrain commands and automatic cleanup through the headless runtime.
// -----------------------------------------------------------------------------
static void test_runtime()
{
    i76_runtime game = {};
    i76_runtime_config config = {};
    const std::vector<std::uint8_t> ter = make_ter();

    config.tick_rate = 60U;
    expect(i76_runtime_initialize(game, config, i76_make_null_outputs()) ==
               i76_result_code::ok, "initialize runtime");
    add_mission(game.resources, "miss16/m06.msn", "M06.TER");
    expect(i76_resource_add_memory(game.resources, "builtin",
                                   "miss16/m06.ter", ter) ==
               i76_resource_result::ok, "register runtime TER");
    expect(i76_execute_command(game, "terrain activate").code ==
               i76_result_code::invalid_argument,
           "reject activation without prepared terrain");
    expect(i76_execute_command(game,
        "terrain prepare miss16/m06.msn").code == i76_result_code::ok,
           "prepare through developer console");
    expect(i76_execute_command(game, "terrain status").message.find(
        "prepared=miss16/m06.msn") != std::string::npos,
           "console reports pending terrain");
    expect(i76_execute_command(game, "terrain activate").code ==
               i76_result_code::ok,
           "activate through developer console");
    expect(i76_execute_command(game, "terrain status").message.find(
        "pages=2 cells=2 samples=32768") != std::string::npos,
           "report active terrain without renderer");
    expect(i76_world_count(game.world) == 0U
           && !game.active_level.loaded,
           "retail terrain activation does not fabricate world objects");
    expect(i76_execute_command(game, "terrain invalid").code ==
               i76_result_code::invalid_argument,
           "reject unknown terrain command");
    expect(i76_runtime_shutdown(game) == i76_result_code::ok
           && !game.active_terrain.loaded,
           "shutdown clears active terrain without a device");
    expect(i76_runtime_initialize(game, config, i76_make_null_outputs()) ==
               i76_result_code::ok
           && !game.prepared_terrain.ready,
           "repeat initialization starts with empty scene");
    expect(i76_runtime_shutdown(game) == i76_result_code::ok,
           "repeat runtime shutdown");
}

// -----------------------------------------------------------------------------
// Execute independent terrain preparation and lifecycle regression coverage.
// -----------------------------------------------------------------------------
int main()
{
    test_chunk_tags();
    test_failures();
    test_lifecycle();
    test_runtime();
    if (failures != 0U) {
        std::cerr << failures << " terrain scene test(s) failed\n";
        return 1;
    }
    std::cout << "terrain scene tests passed\n";
    return 0;
}
