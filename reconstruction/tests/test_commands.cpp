#include "i76/command.h"

#include <cstdint>
#include <iostream>
#include <limits>
#include <string_view>


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
// Exercise the runtime command parser and its error responses.
// -----------------------------------------------------------------------------
static void check_commands()
{
    i76_runtime game = {};
    i76_recording_outputs record = {};
    i76_runtime_config config = {};
    std::uint64_t saved_tick = 0;
    const std::string_view invalid[] = {
        "", "step", "step 0", "step -1", "step +3", "step 3x", "step 10001",
        "step 4294967296", "step 999999999999999999999999", "help extra",
            "unknown", "quit extra",
    };
    config.tick_rate = 60U;
    expect(i76_execute_command(game, "status").code ==
        i76_result_code::not_initialized,
           "no commands before init");
    expect(i76_runtime_initialize(game, config,
        i76_make_recording_outputs(record)) ==
               i76_result_code::ok,
           "commands init");
    expect(i76_execute_command(game, "help").message.find("step <count>") !=
               std::string::npos,
           "help");
    expect(i76_execute_command(game, " status \t").message.find("ticks=0") !=
               std::string::npos,
           "whitespace trim");
    expect(i76_execute_command(game, "pause").code == i76_result_code::ok &&
               game.state.paused,
           "pause command");
    expect(i76_execute_command(game, "step  3").code == i76_result_code::ok &&
               game.state.tick == 3U,
           "step while paused");

    for (const std::string_view command : invalid) {
        expect(i76_execute_command(game, command).code != i76_result_code::ok,
               "invalid command rejected");
        expect(game.state.tick == 3U && game.state.paused &&
            !game.state.exit_requested,
               "invalid command leaves state unchanged");
    }
    saved_tick = game.state.tick;
    game.state.tick = std::numeric_limits<std::uint64_t>::max();
    expect(i76_execute_command(game, "step 1").code != i76_result_code::ok &&
               game.state.tick == std::numeric_limits<std::uint64_t>::max(),
           "failed i76_runtime step propagates error");
    game.state.tick = saved_tick;
    expect(i76_execute_command(game, "resume").code == i76_result_code::ok &&
               !game.state.paused,
           "resume command");
    expect(i76_execute_command(game, "quit").code == i76_result_code::ok &&
               game.state.exit_requested,
           "quit command");
    expect(record.scene.size() == 3U && record.diagnostics.size() >= 17U,
           "events recorded for valid and invalid commands");
    expect(record.diagnostics.back().level == i76_diagnostic_level::info,
           "quit diagnostic recorded");
    expect(i76_runtime_shutdown(game) == i76_result_code::ok,
           "commands shutdown");
}


// -----------------------------------------------------------------------------
// Run the test cases and return a failure status when any assertion fails.
// -----------------------------------------------------------------------------
int main()
{
    check_commands();
    return failures == 0U ? 0 : 1;
}
