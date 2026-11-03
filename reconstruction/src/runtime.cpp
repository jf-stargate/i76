#include "i76/runtime.h"

#include <limits>

namespace i76 {
namespace {

void record_diagnostic(void* context, const diagnostic_event& event)
{
    auto* record = static_cast<recording_outputs*>(context);
    record->diagnostics.push_back(event);
}

void record_scene(void* context, const scene_frame& frame)
{
    auto* record = static_cast<recording_outputs*>(context);
    record->scene.push_back(frame);
}

void record_audio(void* context, const audio_event& event)
{
    auto* record = static_cast<recording_outputs*>(context);
    record->audio.push_back(event);
}

void emit_frame(runtime& game)
{
    if (game.outputs.scene.submit != nullptr) {
        scene_frame frame{};
        frame.tick = game.state.tick;
        game.outputs.scene.submit(game.outputs.scene.context, frame);
    }
}

} // namespace

output_ports make_null_outputs() noexcept
{
    return {};
}

output_ports make_recording_outputs(recording_outputs& record) noexcept
{
    output_ports ports{};
    ports.diagnostics.context = &record;
    ports.diagnostics.submit = record_diagnostic;
    ports.scene.context = &record;
    ports.scene.submit = record_scene;
    ports.audio.context = &record;
    ports.audio.submit = record_audio;
    return ports;
}

result_code runtime_initialize(runtime& game, runtime_config config, output_ports outputs) noexcept
{
    if (game.state.initialized) {
        return result_code::already_initialized;
    }
    if (config.tick_rate == 0U || config.tick_rate > 1000U) {
        return result_code::invalid_argument;
    }

    game = {};
    game.state.initialized = true;
    game.state.tick_rate = config.tick_rate;
    game.state.tick_period_ns = k_nanoseconds_per_second / config.tick_rate;
    game.outputs = outputs;
    return result_code::ok;
}

result_code runtime_shutdown(runtime& game) noexcept
{
    if (!game.state.initialized) {
        return result_code::not_initialized;
    }
    game = {};
    return result_code::ok;
}

result_code runtime_step(runtime& game, std::uint32_t count)
{
    if (!game.state.initialized) {
        return result_code::not_initialized;
    }
    if (count == 0U || count > k_max_ticks_per_call ||
        game.state.tick > std::numeric_limits<std::uint64_t>::max() - count) {
        return result_code::invalid_argument;
    }

    // A manually requested step is permitted while paused, like a debugger.
    for (std::uint32_t index{}; index < count; ++index) {
        ++game.state.tick;
        emit_frame(game);
    }
    return result_code::ok;
}

result_code runtime_advance_time(runtime& game, std::uint64_t elapsed_ns)
{
    if (!game.state.initialized) {
        return result_code::not_initialized;
    }
    if (game.state.paused) {
        return result_code::ok;
    }
    if (elapsed_ns > std::numeric_limits<std::uint64_t>::max() - game.state.accumulated_ns) {
        return result_code::overflow;
    }

    const std::uint64_t total_ns = game.state.accumulated_ns + elapsed_ns;
    const std::uint64_t count = total_ns / game.state.tick_period_ns;
    if (count > k_max_ticks_per_call ||
        count > std::numeric_limits<std::uint64_t>::max() - game.state.tick) {
        return result_code::overflow;
    }

    game.state.accumulated_ns = total_ns % game.state.tick_period_ns;
    if (count != 0U) {
        return runtime_step(game, static_cast<std::uint32_t>(count));
    }
    return result_code::ok;
}

result_code runtime_set_paused(runtime& game, bool paused) noexcept
{
    if (!game.state.initialized) {
        return result_code::not_initialized;
    }
    game.state.paused = paused;
    // Pausing does not bank elapsed host time for replay on resume.
    game.state.accumulated_ns = 0U;
    return result_code::ok;
}

result_code runtime_request_exit(runtime& game) noexcept
{
    if (!game.state.initialized) {
        return result_code::not_initialized;
    }
    game.state.exit_requested = true;
    return result_code::ok;
}

result_code runtime_emit_audio(runtime& game, std::uint32_t sound_id)
{
    if (!game.state.initialized) {
        return result_code::not_initialized;
    }
    if (game.outputs.audio.submit != nullptr) {
        audio_event event{};
        event.tick = game.state.tick;
        event.sound_id = sound_id;
        game.outputs.audio.submit(game.outputs.audio.context, event);
    }
    return result_code::ok;
}

void runtime_emit_diagnostic(runtime& game, diagnostic_level level, const std::string& message)
{
    if (game.state.initialized && game.outputs.diagnostics.submit != nullptr) {
        diagnostic_event event{};
        event.tick = game.state.tick;
        event.level = level;
        event.message = message;
        game.outputs.diagnostics.submit(game.outputs.diagnostics.context, event);
    }
}

} // namespace i76
