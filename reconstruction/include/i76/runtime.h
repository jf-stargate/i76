#pragma once

#include "i76/level.h"
#include "i76/resource.h"
#include "i76/world.h"

#include <cstdint>
#include <string>
#include <vector>

enum class i76_result_code : std::uint8_t {
    ok = 0,
    already_initialized,
    not_initialized,
    invalid_argument,
    overflow,
    unknown_command,
    not_found,
};

enum class i76_diagnostic_level : std::uint8_t {
    info = 0,
    error,
};

struct i76_diagnostic_event {
    std::uint64_t tick{};
    i76_diagnostic_level level{};
    std::string message{};
};

struct i76_scene_frame {
    std::uint64_t tick{};
};

struct i76_audio_event {
    std::uint64_t tick{};
    std::uint32_t sound_id{};
};

// Each output has an independent, optional destination. Null function pointers
// mean discard; a receiver must not retain borrowed event references.
struct i76_diagnostic_sink {
    void* context{};
    void (*submit)(void*, const i76_diagnostic_event&){};
};

struct i76_scene_sink {
    void* context{};
    void (*submit)(void*, const i76_scene_frame&){};
};

struct i76_audio_sink {
    void* context{};
    void (*submit)(void*, const i76_audio_event&){};
};

struct i76_output_ports {
    i76_diagnostic_sink diagnostics{};
    i76_scene_sink scene{};
    i76_audio_sink audio{};
};

struct i76_recording_outputs {
    std::vector<i76_diagnostic_event> diagnostics{};
    std::vector<i76_scene_frame> scene{};
    std::vector<i76_audio_event> audio{};
};

i76_output_ports i76_make_null_outputs() noexcept;
i76_output_ports i76_make_recording_outputs(i76_recording_outputs& record) noexcept;

struct i76_runtime_config {
    std::uint32_t tick_rate{};
};

struct i76_runtime_state {
    bool initialized{};
    bool paused{};
    bool exit_requested{};
    std::uint32_t tick_rate{};
    std::uint64_t tick_period_ns{};
    std::uint64_t tick{};
    std::uint64_t accumulated_ns{};
};

struct i76_runtime {
    i76_runtime_state state{};
    i76_output_ports outputs{};
    // Registry lifetime follows the application; its objects are session-scoped.
    i76_world_registry world{};
    i76_resource_store resources{};
    i76_prepared_level prepared_level{};
    i76_active_level active_level{};
};

// Explicit initialize/shutdown. The registry preserves its generation history
// across repeated use of the same runtime instance, including shell sessions.
i76_result_code i76_runtime_initialize(i76_runtime& game, i76_runtime_config config,
                                        i76_output_ports outputs);
i76_result_code i76_runtime_shutdown(i76_runtime& game) noexcept;
i76_result_code i76_runtime_step(i76_runtime& game, std::uint32_t count);
i76_result_code i76_runtime_advance_time(i76_runtime& game, std::uint64_t elapsed_ns);
i76_result_code i76_runtime_set_paused(i76_runtime& game, bool paused) noexcept;
i76_result_code i76_runtime_request_exit(i76_runtime& game) noexcept;
i76_result_code i76_runtime_emit_audio(i76_runtime& game, std::uint32_t sound_id);
void i76_runtime_emit_diagnostic(i76_runtime& game, i76_diagnostic_level level,
                                 const std::string& message);

inline constexpr std::uint64_t i76_k_nanoseconds_per_second = 1'000'000'000ULL;
inline constexpr std::uint32_t i76_k_max_ticks_per_call = 10'000U;
