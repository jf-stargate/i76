#include "i76/command.h"

#include <cstdint>
#include <iostream>
#include <limits>
#include <string_view>

namespace {

std::uint32_t failures{};

void expect(bool condition, const char* label)
{
    if (!condition) {
        std::cerr << "FAIL: " << label << '\n';
        ++failures;
    }
}

void check_commands()
{
    i76::runtime game{};
    i76::recording_outputs record{};
    i76::runtime_config config{};
    config.tick_rate = 60U;
    expect(i76::execute_command(game, "status").code == i76::result_code::not_initialized,
           "no commands before init");
    expect(i76::runtime_initialize(game, config, i76::make_recording_outputs(record)) ==
               i76::result_code::ok,
           "commands init");
    expect(i76::execute_command(game, "help").message.find("step <count>") !=
               std::string::npos,
           "help");
    expect(i76::execute_command(game, " status \t").message.find("ticks=0") !=
               std::string::npos,
           "whitespace trim");
    expect(i76::execute_command(game, "pause").code == i76::result_code::ok &&
               game.state.paused,
           "pause command");
    expect(i76::execute_command(game, "step  3").code == i76::result_code::ok &&
               game.state.tick == 3U,
           "step while paused");
    const std::string_view invalid[] = {
        "", "step", "step 0", "step -1", "step +3", "step 3x", "step 10001",
        "step 4294967296", "step 999999999999999999999999", "help extra", "unknown", "quit extra",
    };
    for (const std::string_view command : invalid) {
        expect(i76::execute_command(game, command).code != i76::result_code::ok,
               "invalid command rejected");
        expect(game.state.tick == 3U && game.state.paused && !game.state.exit_requested,
               "invalid command leaves state unchanged");
    }
    const std::uint64_t saved_tick = game.state.tick;
    game.state.tick = std::numeric_limits<std::uint64_t>::max();
    expect(i76::execute_command(game, "step 1").code != i76::result_code::ok &&
               game.state.tick == std::numeric_limits<std::uint64_t>::max(),
           "failed runtime step propagates error");
    game.state.tick = saved_tick;
    expect(i76::execute_command(game, "resume").code == i76::result_code::ok &&
               !game.state.paused,
           "resume command");
    expect(i76::execute_command(game, "quit").code == i76::result_code::ok &&
               game.state.exit_requested,
           "quit command");
    expect(record.scene.size() == 3U && record.diagnostics.size() >= 17U,
           "events recorded for valid and invalid commands");
    expect(record.diagnostics.back().level == i76::diagnostic_level::info,
           "quit diagnostic recorded");
    expect(i76::runtime_shutdown(game) == i76::result_code::ok,
           "commands shutdown");
}

} // namespace

int main()
{
    check_commands();
    return failures == 0U ? 0 : 1;
}
