#include "i76/command.h"

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

static std::uint32_t failures = 0;

static void expect(bool condition, const char* label)
{
    if (!condition) {
        std::cerr << "FAIL: " << label << '\n';
        ++failures;
    }
}

static void test_commands_and_directory_provider()
{
    i76_runtime game = {};
    i76_runtime_config config = {};
    i76_recording_outputs record = {};
    i76_command_result result = {};
    i76_world_handle original = {};
    i76_resource_stats stats = {};
    std::filesystem::path root = std::filesystem::temp_directory_path() / "i76_level_cli_test_1";
    std::ofstream stream = {};
    std::error_code error = {};
    std::string mount_command = {};

    config.tick_rate = 60U;
    expect(i76_runtime_initialize(game, config, i76_make_recording_outputs(record)) ==
               i76_result_code::ok, "init fixture runtime");
    expect(i76_execute_command(game, "resource help").message.find("resource list") !=
               std::string::npos, "resource help");
    expect(i76_execute_command(game, "resource list").message.find("(memory)") !=
               std::string::npos, "default memory provider listed");
    expect(i76_execute_command(game, "resource invalid").code ==
               i76_result_code::invalid_argument, "invalid resource command");
    expect(i76_execute_command(game, "resource mount /i76-nonexisting-directory").code ==
               i76_result_code::invalid_argument, "nonexistent directory rejected");
    expect(i76_execute_command(game, "asset stats").message.find("cached=0") !=
               std::string::npos, "initial empty cache stats");
    expect(i76_execute_command(game, "asset list").code ==
               i76_result_code::invalid_argument, "invalid asset command");
    expect(i76_execute_command(game, "level help").message.find("level commands") !=
               std::string::npos, "level help");
    expect(i76_execute_command(game, "level activate").code ==
               i76_result_code::invalid_argument, "activate without prepare");
    expect(i76_execute_command(game, "level unload").code ==
               i76_result_code::invalid_argument, "unload without level");
    expect(i76_execute_command(game, "level discard").code ==
               i76_result_code::invalid_argument, "discard without prepare");
    expect(i76_execute_command(game, "level inspect ../escape").code ==
               i76_result_code::invalid_argument, "unsafe level inspect rejected");
    expect(i76_execute_command(game, "level inspect demo.level").message.find("objects=2") !=
               std::string::npos, "inspect without loading");
    expect(!game.prepared_level.ready && i76_world_count(game.world) == 0U &&
               i76_resource_get_stats(game.resources).references == 0U,
           "inspect is side-effect free");
    expect(i76_execute_command(game, "level prepare demo.level").code == i76_result_code::ok,
           "prepare command");
    expect(i76_execute_command(game, "level status").message.find("prepared=demo.level") !=
               std::string::npos, "status reports pending preparation");
    expect(i76_execute_command(game, "level prepare demo.level").code ==
               i76_result_code::invalid_argument, "duplicate prepare rejected");
    expect(i76_execute_command(game, "level discard").code == i76_result_code::ok,
           "discard command");
    expect(i76_resource_get_stats(game.resources).references == 0U,
           "discard drops prepared leases");
    expect(i76_execute_command(game, "level load demo.level").code == i76_result_code::ok,
           "load command");
    original = i76_world_handle_at(game.world, 0U);
    result = i76_execute_command(game, "level status");
    expect(result.message.find("loaded=demo.level") != std::string::npos &&
               result.message.find("assets=1") != std::string::npos,
           "status reports active state");
    expect(i76_execute_command(game, "level load absent.level").code ==
               i76_result_code::invalid_argument &&
               i76_world_lookup(game.world, original) != nullptr,
           "failed load retains old world and leases");
    expect(i76_execute_command(game, "level unload").code == i76_result_code::ok &&
               i76_world_lookup(game.world, original) == nullptr,
           "explicit unload invalidates world handles");
    expect(i76_execute_command(game, "level badcommand").code ==
               i76_result_code::invalid_argument, "unknown level action rejected");

    std::filesystem::remove_all(root, error);
    std::filesystem::create_directories(root, error);
    expect(!error, "create directory fixture");
    stream.open(root / "external.level", std::ios::binary);
    stream << "I76LEVEL 1\nasset external.bin\nobject scenery tower external.bin\n";
    stream.close();
    stream.open(root / "external.bin", std::ios::binary);
    stream << "GEO-fixture";
    stream.close();
    mount_command = "resource mount " + root.string();
    expect(i76_execute_command(game, mount_command).code == i76_result_code::ok,
           "CLI mount directory");
    expect(i76_execute_command(game, "resource list").message.find("(directory)") !=
               std::string::npos, "directory mount listed");
    expect(i76_execute_command(game, "level load external.level").code == i76_result_code::ok,
           "load fixture from directory provider");
    expect(i76_world_count(game.world) == 1U &&
               i76_world_lookup(game.world, i76_world_handle_at(game.world, 0U))->name == "tower",
           "external level object instantiated");
    stats = i76_resource_get_stats(game.resources);
    expect(stats.mount_count == 2U && stats.cached_bytes == 11U && stats.references == 1U,
           "external dependency leased, bytes accounted");
    expect(i76_execute_command(game, "level unload").code == i76_result_code::ok &&
               i76_resource_get_stats(game.resources).references == 0U,
           "external asset lease released");
    expect(i76_execute_command(game, "level help extra").code ==
               i76_result_code::invalid_argument, "reject extraneous level args");
    expect(!record.diagnostics.empty() &&
               record.diagnostics.back().level == i76_diagnostic_level::error,
           "recording diagnostic sink captures errors");
    expect(i76_runtime_shutdown(game) == i76_result_code::ok, "shutdown runtime fixture");
    std::filesystem::remove_all(root, error);
}

int main()
{
    test_commands_and_directory_provider();
    return failures == 0U ? 0 : 1;
}
