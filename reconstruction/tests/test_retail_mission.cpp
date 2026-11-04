#include "i76/command.h"
#include "i76/retail_mission.h"

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

static std::uint32_t failures{};

static void expect(bool condition, const char* message)
{
    if (!condition) {
        std::cerr << "FAIL: " << message << '\n';
        ++failures;
    }
}

static void add_u32(std::vector<std::uint8_t>& bytes, std::uint32_t value)
{
    bytes.push_back(static_cast<std::uint8_t>(value & 0xffU));
    bytes.push_back(static_cast<std::uint8_t>((value >> 8U) & 0xffU));
    bytes.push_back(static_cast<std::uint8_t>((value >> 16U) & 0xffU));
    bytes.push_back(static_cast<std::uint8_t>((value >> 24U) & 0xffU));
}

static void append(std::vector<std::uint8_t>& bytes,
                   const std::vector<std::uint8_t>& extra)
{
    bytes.insert(bytes.end(), extra.begin(), extra.end());
}

static std::vector<std::uint8_t> chunk(std::string_view tag,
                                        const std::vector<std::uint8_t>& body)
{
    std::vector<std::uint8_t> data{};

    for (std::size_t index = 0U; index < 4U; ++index) {
        data.push_back(index < tag.size() ? static_cast<std::uint8_t>(tag[index]) : 0U);
    }
    add_u32(data, static_cast<std::uint32_t>(8U + body.size()));
    append(data, body);
    return data;
}

static std::vector<std::uint8_t> revision(std::string_view tag, std::uint32_t version)
{
    std::vector<std::uint8_t> payload{};
    add_u32(payload, version);
    return chunk(tag, payload);
}

static std::vector<std::uint8_t> sample_ter()
{
    std::vector<std::uint8_t> bytes(i76_retail_terrain_page_bytes, 0U);
    bytes[0] = 0x23U;
    bytes[1] = 0xf1U; // height 0x123, bit 12, class 7
    bytes[2] = 0U;
    bytes[3] = 4U; // height 1024
    return bytes;
}

static std::vector<std::uint8_t> sample_mission(
    std::uint8_t zmap_pages = 1U, std::uint8_t cell_page = 0U,
    std::uint8_t zone_prefix_byte = 0U, std::string_view zone_name = "M06.TER",
    bool include_zmap = true, bool include_zone = true, bool short_zmap = false,
    bool repeat_zmap = false)
{
    std::vector<std::uint8_t> result = chunk("BWD2", {});
    std::vector<std::uint8_t> world{};
    std::vector<std::uint8_t> terrain{};
    std::vector<std::uint8_t> roads{};
    std::vector<std::uint8_t> objects{};
    std::vector<std::uint8_t> labels{};
    std::vector<std::uint8_t> script{};
    std::vector<std::uint8_t> map(1U + (short_zmap ? 40U : 6400U), 0xffU);
    std::vector<std::uint8_t> zone(14U, 0U);
    std::vector<std::uint8_t> packed_opaque(7U, 0xaaU);

    map[0] = zmap_pages;
    if (!short_zmap) {
        map[1] = cell_page;
        map[100U] = cell_page;
    }
    zone[0] = zone_prefix_byte;
    for (std::size_t index = 0U; index < zone_name.size() && index < 13U; ++index) {
        zone[index + 1U] = static_cast<std::uint8_t>(zone_name[index]);
    }
    append(result, revision("REV", 2U));

    append(world, revision("WREV", 9U));
    append(world, chunk("WRLD", packed_opaque));
    append(world, chunk("EXIT", {}));
    append(result, chunk("WDEF", world));

    append(terrain, revision("TREV", 4U));
    if (include_zmap) {
        append(terrain, chunk("ZMAP", map));
        if (repeat_zmap) {
            append(terrain, chunk("ZMAP", map));
        }
    }
    if (include_zone) {
        append(terrain, chunk("ZONE", zone));
    }
    append(terrain, chunk("EXIT", {}));
    append(result, chunk("TDEF", terrain));

    append(roads, revision("RREV", 1U));
    append(roads, chunk("RSEG", {}));
    append(roads, chunk("EXIT", {}));
    append(result, chunk("RDEF", roads));

    append(objects, revision("OREV", 3U));
    append(objects, chunk("OBJ", std::vector<std::uint8_t>(100U, 0U)));
    append(objects, chunk("EXIT", {}));
    append(result, chunk("ODEF", objects));

    append(labels, revision("LREV", 1U));
    append(labels, chunk("EXIT", {}));
    append(result, chunk("LDEF", labels));

    append(script, revision("AREV", 1U));
    append(script, chunk("FSM", {}));
    append(script, chunk("EXIT", {}));
    append(result, chunk("ADEF", script));
    append(result, chunk("EXIT", {}));
    return result;
}

static bool write_bytes(const std::filesystem::path& destination,
                        const std::vector<std::uint8_t>& bytes)
{
    std::ofstream stream(destination, std::ios::binary | std::ios::trunc);
    if (!stream) {
        return false;
    }
    stream.write(reinterpret_cast<const char*>(bytes.data()),
                 static_cast<std::streamsize>(bytes.size()));
    stream.close();
    return stream.good();
}

static bool write_fixture(const std::filesystem::path& root)
{
    std::error_code error{};
    const std::filesystem::path mission = root / "MISS16" / "M06.MSN";
    const std::filesystem::path terrain = root / "MISS16" / "M06.TER";

    std::filesystem::create_directories(mission.parent_path(), error);
    return !error && write_bytes(mission, sample_mission()) &&
           write_bytes(terrain, sample_ter());
}

static void test_decode()
{
    i76_retail_mission_definition document{};
    i76_retail_mission_definition unchanged{};
    i76_retail_error error{};
    std::vector<std::uint8_t> bytes = sample_mission();

    expect(i76_retail_mission_decode(bytes, "MISS16/M06.MSN", document, error) ==
               i76_retail_result::ok, "decode synthetic retail mission marker stream");
    expect(document.name == "miss16/m06.msn" && document.revision == 2U &&
               document.chunk_count > 20U && document.sections.size() == 6U,
           "typed mission owns normalized identity and all six sections");
    expect(document.wrld_records == 1U && document.object_records == 1U &&
               document.route_records == 1U && document.fsm_records == 1U,
           "recognized record counts");
    expect(document.sections[0].tag == "WDEF" &&
               document.sections[0].has_revision && document.sections[0].revision == 9U &&
               document.sections[1].tag == "TDEF" &&
               document.sections[1].has_revision && document.sections[1].revision == 4U,
           "section revision tags interpreted without consuming opaque bytes");
    expect(document.terrain.has_zmap && document.terrain.has_zone &&
               document.terrain.active_pages == 1U &&
               document.terrain.mapped_cells == 2U &&
               document.terrain.referenced_pages == 1U &&
               document.terrain.page_indices[0] == 0U &&
               document.terrain.page_indices[1] == 0xffU &&
               document.terrain.resource_name == "miss16/m06.ter" &&
               document.terrain.zone_prefix_byte == 0U,
           "ZMAP/ZONE parsed and sidecar name normalized relative to mission");

    unchanged = document;
    bytes = sample_mission(1U, 1U);
    expect(i76_retail_mission_decode(bytes, "miss16/m06.msn", document, error) ==
               i76_retail_result::invalid_terrain_map &&
               error.offset > 0U &&
               document.terrain.resource_name == unchanged.terrain.resource_name,
           "out-of-range ZMAP index rejected without output mutation");
    bytes = sample_mission(1U, 0U, 2U);
    expect(i76_retail_mission_decode(bytes, "miss16/m06.msn", document, error) ==
               i76_retail_result::ok &&
               document.terrain.active_pages == 1U &&
               document.terrain.zone_prefix_byte == 2U &&
               document.terrain.resource_name == "miss16/m06.ter",
           "ZONE prefix is not a second ZMAP page count");
    bytes = sample_mission(1U, 0U, 0xffU);
    expect(i76_retail_mission_decode(bytes, "miss16/m06.msn", document, error) ==
               i76_retail_result::ok &&
               document.terrain.active_pages == 1U &&
               document.terrain.zone_prefix_byte == 0xffU,
           "opaque ZONE prefix preserves arbitrary byte value");
    bytes = sample_mission(1U, 0U, 1U, "../x.ter");
    expect(i76_retail_mission_decode(bytes, "miss16/m06.msn", document, error) ==
               i76_retail_result::invalid_terrain_name,
           "traversal through ZONE filename rejected");
    bytes = sample_mission(1U, 0U, 1U, "M06.TER", true, true, true);
    expect(i76_retail_mission_decode(bytes, "miss16/m06.msn", document, error) ==
               i76_retail_result::invalid_terrain_map,
           "truncated ZMAP payload rejected");
    bytes = sample_mission(1U, 0U, 1U, "M06.TER", true, true, false, true);
    expect(i76_retail_mission_decode(bytes, "miss16/m06.msn", document, error) ==
               i76_retail_result::invalid_terrain_map,
           "duplicate ZMAP rejected");
    bytes = sample_mission(1U, 0U, 1U, "M06.TER", false);
    expect(i76_retail_mission_decode(bytes, "miss16/m06.msn", document, error) ==
               i76_retail_result::ok && !document.terrain.has_zmap &&
               document.terrain.has_zone, "missing ZMAP is reported as incomplete, not invented");
    bytes = sample_mission(1U, 0U, 1U, "M06.TER", true, false);
    expect(i76_retail_mission_decode(bytes, "miss16/m06.msn", document, error) ==
               i76_retail_result::ok && document.terrain.has_zmap &&
               !document.terrain.has_zone, "missing ZONE is reported as incomplete");
    bytes = sample_mission();
    bytes[4] = static_cast<std::uint8_t>(bytes.size());
    expect(i76_retail_mission_decode(bytes, "miss16/m06.msn", document, error) ==
               i76_retail_result::invalid_structure, "invalid BWD2 marker rejected");
    bytes = sample_mission();
    expect(i76_retail_mission_decode(bytes, "../m06.msn", document, error) ==
               i76_retail_result::invalid_argument, "unsafe mission key rejected");
    expect(!std::string_view(i76_retail_result_name(i76_retail_result::invalid_terrain_size))
                .empty(), "named semantic errors");
}

static void test_resource_and_commands()
{
    i76_resource_store store{};
    i76_resource_handle held{};
    i76_resource_stats stats{};
    i76_retail_mission_definition mission{};
    i76_retail_terrain_samples samples{};
    i76_retail_error error{};
    i76_runtime game{};
    i76_runtime_config config{};
    i76_command_result response{};
    i76_recording_outputs record{};

    expect(i76_retail_mission_read(store, "miss16/m06.msn", mission, error) ==
               i76_retail_result::not_initialized, "read requires provider init");
    expect(i76_resource_initialize(store) == i76_resource_result::ok &&
               i76_resource_mount_memory(store, "fixture") == i76_resource_result::ok,
           "create in-memory resource store");
    expect(i76_resource_add_memory(store, "fixture", "miss16/m06.msn", sample_mission()) ==
               i76_resource_result::ok, "register synthetic mission");
    expect(i76_resource_add_memory(store, "fixture", "miss16/m06.ter", sample_ter()) ==
               i76_resource_result::ok, "register synthetic terrain page");
    expect(i76_retail_mission_read(store, "MISS16/M06.MSN", mission, error) ==
               i76_retail_result::ok, "read through provider and release mission lease");
    stats = i76_resource_get_stats(store);
    expect(stats.references == 0U && stats.cached_bytes == 0U,
           "mission decoding does not retain resource bytes");
    expect(i76_retail_terrain_probe(store, mission, samples, error) ==
               i76_retail_result::ok && samples.pages == 1U &&
               samples.samples == i76_retail_terrain_page_samples &&
               samples.height_min == 0U && samples.height_max == 1024U &&
               samples.surface_flags == 1U && samples.surface_classes[7] == 1U &&
               samples.surface_classes[0] == i76_retail_terrain_page_samples - 1U,
           "TER little-endian packed samples and surface classes");
    stats = i76_resource_get_stats(store);
    expect(stats.references == 0U && stats.cached_bytes == 0U,
           "TER scan releases resource lease");

    expect(i76_resource_acquire(store, "miss16/m06.ter", held) == i76_resource_result::ok,
           "external retained TER lease");
    expect(i76_retail_terrain_probe(store, mission, samples, error) == i76_retail_result::ok &&
               i76_resource_get_stats(store).references == 1U,
           "reader does not release externally held reference");
    expect(i76_resource_release(store, held) == i76_resource_result::ok,
           "release external reference");

    expect(i76_resource_add_memory(store, "fixture", "miss16/absent.msn",
                                   sample_mission(1U, 0U, 1U, "absent.ter")) ==
               i76_resource_result::ok, "register mission with missing sidecar");
    expect(i76_retail_mission_read(store, "miss16/absent.msn", mission, error) ==
               i76_retail_result::ok &&
               i76_retail_terrain_probe(store, mission, samples, error) ==
                   i76_retail_result::resource_not_found &&
               i76_resource_get_stats(store).references == 0U,
           "missing TER is distinct from valid mission decode and leaks no resource lease");
    expect(i76_resource_add_memory(store, "fixture", "miss16/prefix.msn",
                                   sample_mission(1U, 0U, 0xffU, "m06.ter")) ==
               i76_resource_result::ok, "register mission with unrelated ZONE prefix");
    expect(i76_retail_mission_read(store, "miss16/prefix.msn", mission, error) ==
               i76_retail_result::ok &&
               mission.terrain.zone_prefix_byte == 0xffU &&
               i76_retail_terrain_probe(store, mission, samples, error) ==
                   i76_retail_result::ok &&
               samples.pages == 1U &&
               i76_resource_get_stats(store).references == 0U,
           "valid TER page count comes from ZMAP and lease releases after probe");
    expect(i76_resource_add_memory(store, "fixture", "miss16/short.ter",
                                   std::vector<std::uint8_t>(64U, 0U)) ==
               i76_resource_result::ok, "register truncated sidecar");
    expect(i76_resource_add_memory(store, "fixture", "miss16/short.msn",
                                   sample_mission(1U, 0U, 1U, "short.ter")) ==
               i76_resource_result::ok, "register sidecar referencing mission");
    expect(i76_retail_mission_read(store, "miss16/short.msn", mission, error) ==
               i76_retail_result::ok, "decode short-sidecar mission");
    samples.pages = 99U;
    expect(i76_retail_terrain_probe(store, mission, samples, error) ==
               i76_retail_result::invalid_terrain_size && samples.pages == 99U,
           "invalid sidecar size rejected transactionally");
    stats = i76_resource_get_stats(store);
    expect(stats.references == 0U, "failing sidecar scan releases lease");
    expect(i76_retail_mission_read(store, "miss16/missing.msn", mission, error) ==
               i76_retail_result::resource_not_found, "missing mission is distinguished");
    expect(i76_retail_mission_decode(sample_mission(1U, 1U), "miss16/bad.msn",
                                     mission, error) == i76_retail_result::invalid_terrain_map,
           "pure decode can reject invalid blob independently of store");
    expect(i76_resource_shutdown(store) == i76_resource_result::ok,
           "temporary store cleanup");

    config.tick_rate = 60U;
    expect(i76_runtime_initialize(game, config, i76_make_recording_outputs(record)) ==
               i76_result_code::ok, "initialize runtime");
    expect(i76_resource_add_memory(game.resources, "builtin", "miss16/m06.msn",
                                   sample_mission()) == i76_resource_result::ok &&
               i76_resource_add_memory(game.resources, "builtin", "miss16/m06.ter",
                                       sample_ter()) == i76_resource_result::ok,
           "register retail style fixture with runtime");
    expect(i76_execute_command(game, "level load demo.level").code == i76_result_code::ok,
           "start synthetic level to verify read-only inspection");
    const std::uint64_t object_generation = game.world.last_generation;
    const std::uint64_t tick = game.state.tick;
    response = i76_execute_command(game, "level summary miss16/m06.msn");
    expect(response.code == i76_result_code::ok &&
               response.message.find("revision=2") != std::string::npos &&
               response.message.find("WRLD=1") != std::string::npos &&
               response.message.find("ZONE sidecar=miss16/m06.ter") != std::string::npos,
           "registered summary command exposes parsed structure");
    response = i76_execute_command(game, "level terrain miss16/m06.msn");
    expect(response.code == i76_result_code::ok &&
               response.message.find("height_max=1024") != std::string::npos &&
               response.message.find("surface_class=7 samples=1") != std::string::npos,
           "registered terrain command validates packed TER");
    response = i76_execute_command(game, "level dependencies miss16/m06.msn");
    expect(response.code == i76_result_code::ok &&
               response.message.find("status=ok") != std::string::npos &&
               response.message.find("resource fields not yet decoded") != std::string::npos,
           "registered dependency command reports scope honestly");
    expect(i76_resource_add_memory(game.resources, "builtin", "miss16/absent.msn",
                                   sample_mission(1U, 0U, 1U, "absent.ter")) ==
               i76_resource_result::ok, "runtime registers intentionally missing sidecar");
    response = i76_execute_command(game, "level dependencies miss16/absent.msn");
    expect(response.code == i76_result_code::ok &&
               response.message.find("status=resource not found") != std::string::npos,
           "dependencies reports missing TER without treating mission metadata as invalid");
    expect(i76_execute_command(game, "level terrain miss16/absent.msn").code !=
               i76_result_code::ok, "terrain probe rejects absent sidecar");
    expect(i76_execute_command(game, "level summary missing.msn").code !=
               i76_result_code::ok, "missing retail command input rejected");
    expect(i76_execute_command(game, "level load miss16/m06.msn").code !=
               i76_result_code::ok, "retail activation stays disabled");
    expect(game.world.last_generation == object_generation &&
               game.state.tick == tick && game.active_level.loaded &&
               i76_world_count(game.world) == 2U && !game.prepared_level.ready,
           "read-only commands do not modify simulation or active synthetic level");
    expect(i76_resource_get_stats(game.resources).references == 1U,
           "retail commands retain no extra leases while demo level active");
    expect(i76_runtime_shutdown(game) == i76_result_code::ok,
           "runtime shutdown releases synthetic active level and all leases");
}

static void test_casefold_directory()
{
    const std::filesystem::path root = std::filesystem::temp_directory_path() /
                                       "i76_retail_milestone3_fixture";
    i76_resource_store store{};
    i76_retail_mission_definition mission{};
    i76_retail_terrain_samples samples{};
    i76_retail_error error{};
    std::error_code ec{};

    std::filesystem::remove_all(root, ec);
    expect(write_fixture(root), "write uppercase synthetic mission and TER fixtures");
    expect(i76_resource_initialize(store) == i76_resource_result::ok &&
               i76_resource_mount_directory(store, root.string()) == i76_resource_result::ok,
           "mount test fixture directory");
    expect(i76_retail_mission_read(store, "miss16/m06.msn", mission, error) ==
               i76_retail_result::ok && mission.terrain.resource_name == "miss16/m06.ter",
           "casefold mission and ZONE path lookup");
    expect(i76_retail_terrain_probe(store, mission, samples, error) ==
               i76_retail_result::ok && samples.height_max == 1024U,
           "casefold sidecar acquisition and sample check");
    expect(i76_resource_get_stats(store).references == 0U,
           "casefold reader releases all lease references");
    expect(i76_resource_shutdown(store) == i76_resource_result::ok,
           "directory store closes");
    std::filesystem::remove_all(root, ec);
}

int main(int argc, char* argv[])
{
    if (argc == 3 && std::string_view(argv[1]) == "--make-fixture") {
        return write_fixture(std::filesystem::path(argv[2])) ? 0 : 1;
    }
    if (argc != 1) {
        return 2;
    }
    test_decode();
    test_resource_and_commands();
    test_casefold_directory();
    return failures == 0U ? 0 : 1;
}
