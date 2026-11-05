#include "i76/runtime.h"

#include <limits>

static constexpr std::uint8_t demo_level[] =
    "I76LEVEL 1\nasset demo_shared.dat\nobject vehicle demo_car "
    "demo_shared.dat\n"
    "object marker demo_checkpoint\n";
static constexpr std::uint8_t demo_shared[] = "synthetic asset payload";

// -----------------------------------------------------------------------------
// Append a diagnostic event to the injected recording sink.
// -----------------------------------------------------------------------------
static void record_diagnostic(void* context, const i76_diagnostic_event& event)
{
    i76_recording_outputs* record =
        static_cast<i76_recording_outputs*>(context);
    record->diagnostics.push_back(event);
}

// -----------------------------------------------------------------------------
// Append a scene-frame event to the injected recording sink.
// -----------------------------------------------------------------------------
static void record_scene(void* context, const i76_scene_frame& frame)
{
    i76_recording_outputs* record =
        static_cast<i76_recording_outputs*>(context);
    record->scene.push_back(frame);
}

// -----------------------------------------------------------------------------
// Append an audio event to the injected recording sink.
// -----------------------------------------------------------------------------
static void record_audio(void* context, const i76_audio_event& event)
{
    i76_recording_outputs* record =
        static_cast<i76_recording_outputs*>(context);
    record->audio.push_back(event);
}

// -----------------------------------------------------------------------------
// Forward the current fixed-tick scene frame to an optional sink.
// -----------------------------------------------------------------------------
static void emit_frame(i76_runtime& game)
{
    i76_scene_frame frame = {};

    if (game.outputs.scene.submit != nullptr) {
        frame.tick = game.state.tick;
        game.outputs.scene.submit(game.outputs.scene.context, frame);
    }
}

// -----------------------------------------------------------------------------
// Construct output ports that discard scene, audio, and diagnostics.
// -----------------------------------------------------------------------------
i76_output_ports i76_make_null_outputs() noexcept
{
    return {};
}

// -----------------------------------------------------------------------------
// Connect runtime outputs to the supplied recording buffers.
// -----------------------------------------------------------------------------
i76_output_ports i76_make_recording_outputs(i76_recording_outputs& record
                                         ) noexcept
{
    i76_output_ports ports = {};

    ports.diagnostics.context = &record;
    ports.diagnostics.submit = record_diagnostic;
    ports.scene.context = &record;
    ports.scene.submit = record_scene;
    ports.audio.context = &record;
    ports.audio.submit = record_audio;
    return ports;
}

// -----------------------------------------------------------------------------
// Initialize simulation timing, resources, world objects, and outputs.
// -----------------------------------------------------------------------------
i76_result_code i76_runtime_initialize(i76_runtime& game,
                                       i76_runtime_config config,
                                       i76_output_ports outputs)
{
    i76_world_result world_result = i76_world_result::ok;
    i76_resource_result resource_result = i76_resource_result::ok;

    if (game.state.initialized) {
        return i76_result_code::already_initialized;
    }
    if (config.tick_rate == 0U
        || config.tick_rate > 1000U) {
        return i76_result_code::invalid_argument;
    }
    world_result = i76_world_initialize(game.world);
    if (world_result != i76_world_result::ok) {
        return i76_result_code::invalid_argument;
    }

    resource_result = i76_resource_initialize(game.resources);
    if (resource_result == i76_resource_result::ok) {
        resource_result = i76_resource_mount_memory(game.resources, "builtin");
    }
    if (resource_result == i76_resource_result::ok) {
        resource_result = i76_resource_add_memory(game.resources, "builtin",
            "demo.level",
                                                  {demo_level,
                                                  sizeof(demo_level) - 1U});
    }
    if (resource_result == i76_resource_result::ok) {
        resource_result = i76_resource_add_memory(game.resources, "builtin",
            "demo_shared.dat",
                                                  {demo_shared,
                                                  sizeof(demo_shared) - 1U});
    }
    if (resource_result != i76_resource_result::ok) {
        i76_resource_shutdown(game.resources);
        i76_world_shutdown(game.world);
        return i76_result_code::invalid_argument;
    }
    game.state = {};
    game.outputs = outputs;
    game.state.initialized = true;
    game.state.tick_rate = config.tick_rate;
    game.state.tick_period_ns = i76_k_nanoseconds_per_second / config.tick_rate;
    return i76_result_code::ok;
}

// -----------------------------------------------------------------------------
// Release runtime-owned resources while preserving generation history.
// -----------------------------------------------------------------------------
i76_result_code i76_runtime_shutdown(i76_runtime& game) noexcept
{
    if (!game.state.initialized) {
        return i76_result_code::not_initialized;
    }
    if (game.prepared_terrain.ready) {
        i76_terrain_discard(game.prepared_terrain);
    }
    if (game.active_terrain.loaded) {
        i76_terrain_unload(game.active_terrain);
    }
    i76_level_discard(game.resources, game.prepared_level);
    if (game.active_level.loaded) {
        i76_level_unload(game.world, game.resources, game.active_level);
    }
    if (i76_resource_shutdown(game.resources) != i76_resource_result::ok) {
        // Caller still owns a resource lease.
        return i76_result_code::invalid_argument;
    }
    i76_world_shutdown(game.world);
    game.state = {};
    game.outputs = {};
    return i76_result_code::ok;
}

// -----------------------------------------------------------------------------
// Advance the fixed-step simulation by a validated tick count.
// -----------------------------------------------------------------------------
i76_result_code i76_runtime_step(i76_runtime& game, std::uint32_t count)
{
    std::uint32_t index = 0;

    if (!game.state.initialized) {
        return i76_result_code::not_initialized;
    }
    if (count == 0U
        || count > i76_k_max_ticks_per_call
        || game.state.tick >
               std::numeric_limits<std::uint64_t>::max() - count) {
        return i76_result_code::invalid_argument;
    }
    for (index = 0; index < count; ++index) {
        ++game.state.tick;
        emit_frame(game);
    }
    return i76_result_code::ok;
}

// -----------------------------------------------------------------------------
// Translate host elapsed time into bounded simulation ticks.
// -----------------------------------------------------------------------------
i76_result_code i76_runtime_advance_time(i76_runtime& game,
                                         std::uint64_t elapsed_ns)
{
    std::uint64_t total_ns = 0;
    std::uint64_t count = 0;

    if (!game.state.initialized) {
        return i76_result_code::not_initialized;
    }
    if (game.state.paused) {
        return i76_result_code::ok;
    }
    if (elapsed_ns > std::numeric_limits<std::uint64_t>::max() -
        game.state.accumulated_ns) {
        return i76_result_code::overflow;
    }
    total_ns = game.state.accumulated_ns + elapsed_ns;
    count = total_ns / game.state.tick_period_ns;
    if (count > i76_k_max_ticks_per_call
        || count >
               std::numeric_limits<std::uint64_t>::max() - game.state.tick) {
        return i76_result_code::overflow;
    }
    game.state.accumulated_ns = total_ns % game.state.tick_period_ns;
    if (count != 0U) {
        return i76_runtime_step(game, static_cast<std::uint32_t>(count));
    }
    return i76_result_code::ok;
}

// -----------------------------------------------------------------------------
// Update the real-time simulation pause state.
// -----------------------------------------------------------------------------
i76_result_code i76_runtime_set_paused(i76_runtime& game, bool paused) noexcept
{
    if (!game.state.initialized) {
        return i76_result_code::not_initialized;
    }
    game.state.paused = paused;
    game.state.accumulated_ns = 0U;
    return i76_result_code::ok;
}

// -----------------------------------------------------------------------------
// Mark the runtime for orderly application exit.
// -----------------------------------------------------------------------------
i76_result_code i76_runtime_request_exit(i76_runtime& game) noexcept
{
    if (!game.state.initialized) {
        return i76_result_code::not_initialized;
    }
    game.state.exit_requested = true;
    return i76_result_code::ok;
}

// -----------------------------------------------------------------------------
// Publish an audio event through the configured output sink.
// -----------------------------------------------------------------------------
i76_result_code i76_runtime_emit_audio(i76_runtime& game,
                                       std::uint32_t sound_id)
{
    i76_audio_event event = {};

    if (!game.state.initialized) {
        return i76_result_code::not_initialized;
    }
    if (game.outputs.audio.submit != nullptr) {
        event.tick = game.state.tick;
        event.sound_id = sound_id;
        game.outputs.audio.submit(game.outputs.audio.context, event);
    }
    return i76_result_code::ok;
}

// -----------------------------------------------------------------------------
// Publish a diagnostic event without direct host I/O.
// -----------------------------------------------------------------------------
void i76_runtime_emit_diagnostic(i76_runtime& game,
                                 i76_diagnostic_level level,
                                 const std::string& message)
{
    i76_diagnostic_event event = {};

    if (game.state.initialized
        && game.outputs.diagnostics.submit != nullptr) {
        event.tick = game.state.tick;
        event.level = level;
        event.message = message;
        game.outputs.diagnostics.submit(game.outputs.diagnostics.context,
            event);
    }
}
