#include "i76/command.h"
#include "i76/shell.h"

#include <cstdint>
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

static void test_world_commands()
{
    i76_runtime game = {};
    i76_runtime_config config = {};
    i76_recording_outputs record = {};
    i76_command_result reply = {};
    std::uint64_t tick = 0;
    const std::string invalid[] = {
        "object spawn", "object spawn vehicle", "object spawn unknown spy",
        "object spawn marker name with spaces", "object inspect", "object inspect 0:0",
        "object inspect 1", "object inspect 1:", "object inspect :1", "object inspect 1:2:3",
        "object inspect 4294967296:1", "object inspect 1:18446744073709551616",
        "object inspect -1:1", "object inspect 1:+1", "object inspect 1:1 trailing",
        "object destroy garbage", "object clear trailing", "object list trailing",
        "object help extra", "object wibble", "object spawn scenery bad/name with spaces",
    };

    expect(i76_execute_command(game, "object list").code == i76_result_code::not_initialized,
           "object commands require initialized runtime");
    config.tick_rate = 60U;
    expect(i76_runtime_initialize(game, config, i76_make_recording_outputs(record)) ==
               i76_result_code::ok, "commands init");
    expect(i76_execute_command(game, "object").message.find("object commands") !=
               std::string::npos, "object help");
    expect(i76_execute_command(game, "object list").message == "objects=0", "empty list");
    tick = game.state.tick;
    for (const std::string& input : invalid) {
        reply = i76_execute_command(game, input);
        expect(reply.code != i76_result_code::ok, "invalid syntax rejected");
        expect(i76_world_count(game.world) == 0U && game.state.tick == tick,
               "bad input has no effect");
    }
    expect(i76_execute_command(game, "object spawn vehicle scout").message.find("1:1") !=
               std::string::npos, "spawn exact first handle");
    expect(i76_execute_command(game, "object spawn marker checkpoint").message.find("2:2") !=
               std::string::npos, "spawn second handle");
    reply = i76_execute_command(game, "object list");
    expect(reply.code == i76_result_code::ok &&
               reply.message.find("1:1 vehicle scout") != std::string::npos &&
               reply.message.find("2:2 marker checkpoint") != std::string::npos,
           "ordered list includes handles and kinds");
    reply = i76_execute_command(game, "object inspect 1:1");
    expect(reply.code == i76_result_code::ok &&
               reply.message.find("position=(0.000000,0.000000,0.000000)") != std::string::npos,
           "inspector exposes zeroed transform");
    expect(i76_execute_command(game, "object inspect 1:9").code ==
               i76_result_code::not_found, "wrong generation distinguished from parse error");
    expect(i76_execute_command(game, "object destroy 1:1").code == i76_result_code::ok,
           "destroy object");
    expect(i76_execute_command(game, "object destroy 1:1").code ==
               i76_result_code::not_found, "stale handle destroy rejected");
    expect(i76_execute_command(game, "object spawn scenery road").message.find("1:3") !=
               std::string::npos, "reused slot gets new generation");
    expect(i76_execute_command(game, "object list").message.find("2:2 marker checkpoint") <
               i76_execute_command(game, "object list").message.find("1:3 scenery road"),
           "listing uses creation order");
    expect(i76_execute_command(game, "object clear").code == i76_result_code::ok &&
               i76_world_count(game.world) == 0U,
           "clear via commands");
    expect(i76_execute_command(game, "object inspect 1:3").code ==
               i76_result_code::not_found, "clear invalidates old handles");
    expect(i76_execute_command(game, "object spawn vehicle after").message.find("1:4") !=
               std::string::npos, "fresh generation after clear");
    expect(!record.diagnostics.empty() &&
               record.diagnostics.back().message.find("1:4") != std::string::npos,
           "recording output receives final result");
    expect(i76_runtime_shutdown(game) == i76_result_code::ok, "commands shutdown");
    expect(i76_runtime_initialize(game, config, i76_make_null_outputs()) ==
               i76_result_code::ok, "runtime reinitialize with world");
    expect(i76_execute_command(game, "object spawn vehicle again").message.find("1:5") !=
               std::string::npos, "runtime reinitialize preserves handle generations");
    expect(i76_execute_command(game, "object inspect 1:4").code ==
               i76_result_code::not_found, "previous runtime's handle remains invalid");
    expect(i76_runtime_shutdown(game) == i76_result_code::ok, "reinitialized shutdown");
}

static void test_recording_equivalence()
{
    i76_runtime null_game = {};
    i76_runtime record_game = {};
    i76_runtime_config config = {};
    i76_recording_outputs record = {};
    const std::string commands[] = {
        "object spawn vehicle a", "object spawn marker b", "object destroy 1:1",
        "object spawn scenery c", "object list", "object clear",
    };

    config.tick_rate = 60U;
    expect(i76_runtime_initialize(null_game, config, i76_make_null_outputs()) ==
               i76_result_code::ok, "null output initialize");
    expect(i76_runtime_initialize(record_game, config, i76_make_recording_outputs(record)) ==
               i76_result_code::ok, "record output initialize");
    for (const std::string& command : commands) {
        expect(i76_execute_command(null_game, command).message ==
                   i76_execute_command(record_game, command).message,
               "sink choice does not change command result");
        expect(i76_world_count(null_game.world) == i76_world_count(record_game.world) &&
                   null_game.world.last_generation == record_game.world.last_generation,
               "sink choice does not change world state");
    }
    expect(record.diagnostics.size() == 6U && i76_world_count(record_game.world) == 0U,
           "recording output captured all world events");
    expect(i76_runtime_shutdown(null_game) == i76_result_code::ok &&
               i76_runtime_shutdown(record_game) == i76_result_code::ok,
           "both worlds shut down");
}

static void test_shell_session_lifetime()
{
    i76_runtime game = {};
    i76_runtime_config config = {};
    i76_shell_state shell = {};
    i76_world_handle old_handle = {};
    i76_command_result reply = {};

    config.tick_rate = 60U;
    expect(i76_runtime_initialize(game, config, i76_make_null_outputs()) ==
               i76_result_code::ok, "shell runtime initialize");
    expect(i76_shell_initialize(shell, game) == i76_result_code::ok, "shell initialize");
    expect(i76_shell_execute(shell, game, "object list").code ==
               i76_result_code::unknown_command, "world commands unavailable outside session");
    expect(i76_shell_execute(shell, game, "play").code == i76_result_code::ok &&
               i76_world_count(game.world) == 2U, "synthetic session has two objects");
    old_handle = i76_world_handle_at(game.world, 0U);
    reply = i76_shell_execute(shell, game, "object inspect 1:1");
    expect(reply.code == i76_result_code::ok &&
               reply.message.find("demo_car") != std::string::npos,
           "session inspector reads synthetic object");
    expect(i76_shell_execute(shell, game, "object spawn scenery overpass").code ==
               i76_result_code::ok && i76_world_count(game.world) == 3U,
           "shell forwards mutating commands to real core");
    expect(i76_shell_execute(shell, game, "object list").message.find("overpass") !=
               std::string::npos, "shell object listing");
    expect(i76_shell_execute(shell, game, "menu").code == i76_result_code::ok &&
               i76_world_count(game.world) == 0U &&
               i76_world_lookup(game.world, old_handle) == nullptr,
           "return to menu unloads world");
    expect(i76_shell_execute(shell, game, "play").code == i76_result_code::ok &&
               i76_world_count(game.world) == 2U, "second session reseeded");
    expect(i76_world_lookup(game.world, old_handle) == nullptr &&
               i76_world_handle_at(game.world, 0U).generation > old_handle.generation,
           "old session handle never aliases later session");
    expect(i76_shell_shutdown(shell) == i76_result_code::ok, "shell shutdown");
    expect(i76_runtime_shutdown(game) == i76_result_code::ok, "runtime shutdown");
}

int main()
{
    test_world_commands();
    test_recording_equivalence();
    test_shell_session_lifetime();
    return failures == 0U ? 0 : 1;
}
