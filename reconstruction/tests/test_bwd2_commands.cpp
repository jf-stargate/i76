#include "i76/command.h"
#include "i76/bwd2.h"

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

static std::uint32_t failures = 0;

static void expect(bool condition, const char* label)
{
    if (!condition) {
        std::cerr << "FAIL: " << label << '\n';
        ++failures;
    }
}

static void add_u32(std::vector<std::uint8_t>& bytes, std::uint32_t value)
{
    bytes.push_back(static_cast<std::uint8_t>(value & 255U));
    bytes.push_back(static_cast<std::uint8_t>((value >> 8U) & 255U));
    bytes.push_back(static_cast<std::uint8_t>((value >> 16U) & 255U));
    bytes.push_back(static_cast<std::uint8_t>((value >> 24U) & 255U));
}

static std::vector<std::uint8_t> make_chunk(std::string_view name,
                                             const std::vector<std::uint8_t>& payload)
{
    std::vector<std::uint8_t> bytes = {};
    std::uint32_t index = 0;

    for (index = 0; index < 4U; ++index) {
        bytes.push_back(index < name.size() ? static_cast<std::uint8_t>(name[index]) : 0U);
    }
    add_u32(bytes, static_cast<std::uint32_t>(8U + payload.size()));
    bytes.insert(bytes.end(), payload.begin(), payload.end());
    return bytes;
}

static void append(std::vector<std::uint8_t>& target,
                   const std::vector<std::uint8_t>& suffix)
{
    target.insert(target.end(), suffix.begin(), suffix.end());
}

static std::vector<std::uint8_t> sample_mission()
{
    std::vector<std::uint8_t> root = {};
    std::vector<std::uint8_t> object = {};
    std::vector<std::uint8_t> rev = {};
    std::vector<std::uint8_t> stream = {};
    const std::vector<std::uint8_t> empty = {};

    add_u32(rev, 2U);
    append(root, make_chunk("REV", rev));
    rev = {};
    add_u32(rev, 3U);
    append(object, make_chunk("OREV", rev));
    append(object, make_chunk("OBJ", {1, 2, 3, 4}));
    append(object, make_chunk("EXIT", empty));
    append(root, make_chunk("ODEF", object));
    append(root, make_chunk("EXIT", empty));
    stream = make_chunk("BWD2", {});
    append(stream, root);
    return stream;
}

static bool write_fixture(const std::filesystem::path& root)
{
    std::error_code error = {};
    std::ofstream file = {};
    std::vector<std::uint8_t> bytes = sample_mission();
    std::filesystem::path destination = root / "MISS16" / "M06.MSN";

    std::filesystem::create_directories(destination.parent_path(), error);
    if (error) {
        return false;
    }
    file.open(destination, std::ios::binary | std::ios::trunc);
    if (!file) {
        return false;
    }
    file.write(reinterpret_cast<const char*>(bytes.data()),
               static_cast<std::streamsize>(bytes.size()));
    file.close();
    return file.good();
}

static void test_console_and_directory()
{
    i76_runtime game = {};
    i76_runtime_config config = {};
    i76_recording_outputs record = {};
    i76_command_result reply = {};
    i76_resource_stats stats = {};
    i76_world_handle earlier = {};
    std::vector<std::uint8_t> bytes = sample_mission();
    std::vector<std::uint8_t> malformed = make_chunk("BAD!", {});
    std::filesystem::path root = std::filesystem::temp_directory_path() / "i76_bwd2_cli_fixture";
    std::filesystem::path outside = std::filesystem::temp_directory_path() / "i76_bwd2_outside.msn";
    std::filesystem::path link = root / "MISS16" / "ESCAPE.MSN";
    std::filesystem::path duplicate_a = root / "MISS16" / "AMBIG.MSN";
    std::filesystem::path duplicate_b = root / "MISS16" / "Ambig.Msn";
    std::error_code error = {};
    std::ofstream file = {};
    std::string command = {};

    config.tick_rate = 60U;
    expect(i76_runtime_initialize(game, config, i76_make_recording_outputs(record)) ==
               i76_result_code::ok, "initialize console runtime");
    expect(i76_resource_add_memory(game.resources, "builtin", "sample.msn", bytes) ==
               i76_resource_result::ok, "register synthetic mission");
    expect(i76_resource_add_memory(game.resources, "builtin", "broken.msn", malformed) ==
               i76_resource_result::ok, "register broken mission");
    expect(i76_resource_add_memory(game.resources, "builtin", "sample.spc", bytes) ==
               i76_resource_result::ok, "register synthetic scenario");
    expect(i76_resource_add_memory(game.resources, "builtin", "sample.lvl", bytes) ==
               i76_resource_result::ok, "register synthetic editor level");
    reply = i76_execute_command(game, "level inspect sample.msn");
    expect(reply.code == i76_result_code::ok &&
               reply.message.find("BWD2 sample.msn") != std::string::npos &&
               reply.message.find("revision=2") != std::string::npos &&
               reply.message.find("  ODEF offset=") != std::string::npos &&
               reply.message.find("not loaded") != std::string::npos,
           "automatic BWD2 inspection by .msn suffix");
    expect(i76_execute_command(game, "level inspect sample.spc").code ==
               i76_result_code::ok &&
               i76_execute_command(game, "level inspect sample.lvl").code ==
                   i76_result_code::ok,
           "SPC and LVL suffixes also select BWD2 inspection");
    reply = i76_execute_command(game, "level sections sample.msn");
    expect(reply.code == i76_result_code::ok &&
               reply.message.find("chunks=7") != std::string::npos,
           "explicit BWD2 section command");
    expect(i76_execute_command(game, "level load sample.msn").code != i76_result_code::ok &&
               i76_execute_command(game, "level prepare sample.msn").code != i76_result_code::ok,
           "BWD2 not accepted for gameplay construction");
    expect(i76_execute_command(game, "level sections ../sample.msn").code !=
               i76_result_code::ok, "reject path traversal");
    reply = i76_execute_command(game, "level sections broken.msn");
    expect(reply.code != i76_result_code::ok &&
               reply.message.find("expected BWD2 root") != std::string::npos &&
               reply.message.find("at 0x0") != std::string::npos,
           "report parser error and offset");
    expect(i76_execute_command(game, "level sections no.msn").code !=
               i76_result_code::ok, "missing resource reported");
    expect(i76_execute_command(game, "level inspect demo.level").message.find("objects=2") !=
               std::string::npos, "previous synthetic inspection remains available");
    expect(i76_execute_command(game, "level load demo.level").code == i76_result_code::ok,
           "activate existing synthetic level");
    earlier = i76_world_handle_at(game.world, 0U);
    expect(i76_execute_command(game, "level inspect sample.msn").code == i76_result_code::ok &&
               i76_world_lookup(game.world, earlier) != nullptr,
           "BWD2 inspection cannot invalidate active world");
    stats = i76_resource_get_stats(game.resources);
    expect(stats.references == 1U, "inspector cannot retain extra resource leases");

    std::filesystem::remove_all(root, error);
    expect(write_fixture(root), "write on-disk mixed-case fixture");
    command = "resource mount " + root.string();
    expect(i76_execute_command(game, command).code == i76_result_code::ok,
           "mount on-disk fixture directory");
    reply = i76_execute_command(game, "level inspect miss16/m06.msn");
    expect(reply.code == i76_result_code::ok &&
               reply.message.find("BWD2 miss16/m06.msn") != std::string::npos,
           "case-insensitive legacy filesystem fallback on directory provider");
    reply = i76_execute_command(game, "level sections MISS16/M06.MSN");
    expect(reply.code == i76_result_code::ok &&
               reply.message.find("chunks=7") != std::string::npos,
           "explicit BWD2 command handles mixed-case filename");
    stats = i76_resource_get_stats(game.resources);
    expect(stats.references == 1U, "directory inspection does not leak leases");
    // If the filesystem distinguishes these spellings, a casefold-only lookup
    // must reject ambiguity instead of picking a platform-dependent entry.
    file.open(duplicate_a, std::ios::binary | std::ios::trunc);
    file.write(reinterpret_cast<const char*>(bytes.data()),
               static_cast<std::streamsize>(bytes.size()));
    file.close();
    file.open(duplicate_b, std::ios::binary | std::ios::trunc);
    file.write(reinterpret_cast<const char*>(bytes.data()),
               static_cast<std::streamsize>(bytes.size()));
    file.close();
    error.clear();
    if (!std::filesystem::equivalent(duplicate_a, duplicate_b, error) && !error) {
        expect(i76_execute_command(game, "level sections miss16/ambig.msn").code !=
                   i76_result_code::ok, "ambiguous casefold match rejected");
    }
    expect(i76_execute_command(game, "level unload").code == i76_result_code::ok,
           "existing level unload still works");
    stats = i76_resource_get_stats(game.resources);
    expect(stats.references == 0U && stats.cached_bytes == 0U,
           "resource bytes fully released after unload");

    // A casefolded name must not be able to read outside an explicitly mounted
    // directory via symlink. Windows may lack symlink creation privileges.
    file.open(outside, std::ios::binary | std::ios::trunc);
    file.write(reinterpret_cast<const char*>(bytes.data()),
               static_cast<std::streamsize>(bytes.size()));
    file.close();
    error.clear();
    std::filesystem::create_symlink(outside, link, error);
    if (!error) {
        expect(i76_execute_command(game, "level sections miss16/escape.msn").code !=
                   i76_result_code::ok, "out-of-root symlink cannot be inspected");
    }
    expect(i76_runtime_shutdown(game) == i76_result_code::ok, "cleanup runtime");
    std::filesystem::remove_all(root, error);
    std::filesystem::remove(outside, error);
    expect(!record.diagnostics.empty(), "recording sink retains inspect diagnostics");
}

int main(int argc, char* argv[])
{
    if (argc == 3 && std::string_view(argv[1]) == "--make-fixture") {
        return write_fixture(std::filesystem::path(argv[2])) ? 0 : 1;
    }
    if (argc != 1) {
        return 2;
    }
    test_console_and_directory();
    return failures == 0U ? 0 : 1;
}
