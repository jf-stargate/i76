#include "i76/runtime.h"

#include <cstdint>
#include <iostream>
#include <limits>

namespace {

std::uint32_t failures{};

void expect(bool condition, const char* label)
{
    if (!condition) {
        std::cerr << "FAIL: " << label << '\n';
        ++failures;
    }
}

void check_lifecycle()
{
    i76::runtime game{};
    i76::runtime_config config{};
    i76::recording_outputs record{};

    expect(!game.state.initialized && game.state.tick == 0U &&
               game.outputs.scene.submit == nullptr,
           "runtime zero initialized");
    expect(i76::runtime_shutdown(game) == i76::result_code::not_initialized,
           "reject shutdown before init");
    expect(i76::runtime_step(game, 1U) == i76::result_code::not_initialized,
           "reject manual step before init");
    expect(i76::runtime_advance_time(game, 1U) == i76::result_code::not_initialized,
           "reject clock advance before init");
    expect(i76::runtime_set_paused(game, true) == i76::result_code::not_initialized,
           "reject pause before init");
    expect(i76::runtime_request_exit(game) == i76::result_code::not_initialized,
           "reject quit before init");
    expect(i76::runtime_emit_audio(game, 1U) == i76::result_code::not_initialized,
           "reject audio before init");
    i76::runtime_emit_diagnostic(game, i76::diagnostic_level::error, "ignored");

    expect(i76::runtime_initialize(game, config, i76::make_null_outputs()) ==
               i76::result_code::invalid_argument,
           "reject zero tick rate");
    expect(!game.state.initialized, "invalid init is atomic");
    config.tick_rate = 1001U;
    expect(i76::runtime_initialize(game, config, i76::make_null_outputs()) ==
               i76::result_code::invalid_argument,
           "reject excessive tick rate");
    config.tick_rate = 60U;
    expect(i76::runtime_initialize(game, config, i76::make_recording_outputs(record)) ==
               i76::result_code::ok,
           "init");
    expect(i76::runtime_initialize(game, config, i76::make_null_outputs()) ==
               i76::result_code::already_initialized,
           "reject duplicate init");
    expect(game.outputs.scene.submit != nullptr, "duplicate init keeps outputs");
    expect(i76::runtime_shutdown(game) == i76::result_code::ok, "shutdown");
    expect(game.state.tick == 0U && game.outputs.scene.submit == nullptr,
           "shutdown zeroes state and sinks");
    expect(i76::runtime_initialize(game, config, i76::make_null_outputs()) ==
               i76::result_code::ok,
           "repeat init");
    expect(i76::runtime_shutdown(game) == i76::result_code::ok, "repeat shutdown");
}

void check_fixed_clock()
{
    i76::runtime game{};
    i76::runtime_config config{};
    config.tick_rate = 100U;
    i76::recording_outputs record{};
    expect(i76::runtime_initialize(game, config, i76::make_recording_outputs(record)) ==
               i76::result_code::ok,
           "init clock fixture");
    expect(i76::runtime_advance_time(game, 9'000'000U) == i76::result_code::ok &&
               game.state.tick == 0U,
           "subtick accumulation");
    expect(i76::runtime_advance_time(game, 12'000'000U) == i76::result_code::ok &&
               game.state.tick == 2U && game.state.accumulated_ns == 1'000'000U,
           "complete ticks and remainder");
    expect(record.scene.size() == 2U && record.scene[0].tick == 1U &&
               record.scene[1].tick == 2U,
           "ordered scene output");
    expect(i76::runtime_set_paused(game, true) == i76::result_code::ok,
           "pause");
    expect(i76::runtime_advance_time(game, 99'000'000U) == i76::result_code::ok &&
               game.state.tick == 2U,
           "pause discards wall time");
    expect(i76::runtime_step(game, 1U) == i76::result_code::ok &&
               game.state.tick == 3U,
           "manual step while paused");
    expect(i76::runtime_set_paused(game, false) == i76::result_code::ok,
           "resume");
    expect(i76::runtime_advance_time(game, 10'000'000U) == i76::result_code::ok &&
               game.state.tick == 4U,
           "resumed clock");
    expect(i76::runtime_step(game, 0U) == i76::result_code::invalid_argument &&
               game.state.tick == 4U,
           "zero step rejected");
    expect(i76::runtime_step(game, i76::k_max_ticks_per_call + 1U) ==
               i76::result_code::invalid_argument && game.state.tick == 4U,
           "large manual step rejected without mutation");
    expect(i76::runtime_advance_time(game, std::numeric_limits<std::uint64_t>::max()) ==
               i76::result_code::overflow && game.state.tick == 4U,
           "excessive clock input rejected without mutation");
    expect(i76::runtime_shutdown(game) == i76::result_code::ok, "clock cleanup");
}

void check_outputs()
{
    i76::runtime null_game{};
    i76::runtime record_game{};
    i76::runtime_config config{};
    config.tick_rate = 60U;
    i76::recording_outputs record{};
    expect(i76::runtime_initialize(null_game, config, i76::make_null_outputs()) ==
               i76::result_code::ok,
           "null init");
    expect(i76::runtime_initialize(record_game, config, i76::make_recording_outputs(record)) ==
               i76::result_code::ok,
           "record init");
    for (std::uint32_t index{}; index < 5U; ++index) {
        expect(i76::runtime_step(null_game, 1U) == i76::result_code::ok &&
                   i76::runtime_step(record_game, 1U) == i76::result_code::ok,
               "advance with interchangeable sinks");
    }
    expect(record.scene.size() == 5U, "recorded frame count");
    i76::runtime_emit_diagnostic(null_game, i76::diagnostic_level::error, "ignored");
    expect(i76::runtime_advance_time(null_game, 0U) == i76::result_code::ok,
           "zero elapsed host time is valid");

    expect(null_game.state.tick == record_game.state.tick, "sinks preserve simulation");
    expect(i76::runtime_emit_audio(record_game, 17U) == i76::result_code::ok &&
               i76::runtime_emit_audio(null_game, 17U) == i76::result_code::ok,
           "audio outputs can be null or recorded");
    expect(record.audio.size() == 1U && record.audio[0].sound_id == 17U &&
               record.audio[0].tick == 5U,
           "audio event content");
    i76::runtime_emit_diagnostic(record_game, i76::diagnostic_level::info, "synthetic");
    expect(record.diagnostics.size() == 1U &&
               record.diagnostics[0].message == "synthetic",
           "diagnostic recording");
    expect(i76::runtime_shutdown(record_game) == i76::result_code::ok &&
               i76::runtime_shutdown(null_game) == i76::result_code::ok,
           "sinks cleanup");
    expect(record.scene.size() == 5U, "records outlive runtime");
}

} // namespace

int main()
{
    check_lifecycle();
    check_fixed_clock();
    check_outputs();
    return failures == 0U ? 0 : 1;
}
