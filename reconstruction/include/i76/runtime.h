#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace i76 {

enum class result_code : std::uint8_t {
    ok = 0,
    already_initialized,
    not_initialized,
    invalid_argument,
    overflow,
    unknown_command,
};

enum class diagnostic_level : std::uint8_t {
    info = 0,
    error,
};

struct diagnostic_event {
    std::uint64_t tick{};
    diagnostic_level level{};
    std::string message{};
};

struct scene_frame {
    std::uint64_t tick{};
};

struct audio_event {
    std::uint64_t tick{};
    std::uint32_t sound_id{};
};

// Each output has an independent, optional destination. Null function pointers
// mean discard; a receiver must not retain borrowed event references.
struct diagnostic_sink {
    void* context{};
    void (*submit)(void*, const diagnostic_event&){};
};

struct scene_sink {
    void* context{};
    void (*submit)(void*, const scene_frame&){};
};

struct audio_sink {
    void* context{};
    void (*submit)(void*, const audio_event&){};
};

struct output_ports {
    diagnostic_sink diagnostics{};
    scene_sink scene{};
    audio_sink audio{};
};

struct recording_outputs {
    std::vector<diagnostic_event> diagnostics{};
    std::vector<scene_frame> scene{};
    std::vector<audio_event> audio{};
};

// Make distinct output channels with independently substitutable sinks.
output_ports make_null_outputs() noexcept;
output_ports make_recording_outputs(recording_outputs& record) noexcept;

struct runtime_config {
    std::uint32_t tick_rate{};
};

struct runtime_state {
    bool initialized{};
    bool paused{};
    bool exit_requested{};
    std::uint32_t tick_rate{};
    std::uint64_t tick_period_ns{};
    std::uint64_t tick{};
    std::uint64_t accumulated_ns{};
};

struct runtime {
    runtime_state state{};
    output_ports outputs{};
};

// All values are zero/null on creation. Explicit initialization supplies
// meaningful defaults and binds sinks. Nothing opens a window or device.
result_code runtime_initialize(runtime& game, runtime_config config, output_ports outputs) noexcept;
result_code runtime_shutdown(runtime& game) noexcept;
result_code runtime_step(runtime& game, std::uint32_t count);
result_code runtime_advance_time(runtime& game, std::uint64_t elapsed_ns);
result_code runtime_set_paused(runtime& game, bool paused) noexcept;
result_code runtime_request_exit(runtime& game) noexcept;
result_code runtime_emit_audio(runtime& game, std::uint32_t sound_id);
void runtime_emit_diagnostic(runtime& game, diagnostic_level level, const std::string& message);

// No hidden clock reads: the host owns wall-clock input.
inline constexpr std::uint64_t k_nanoseconds_per_second = 1'000'000'000ULL;
inline constexpr std::uint32_t k_max_ticks_per_call = 10'000U;

} // namespace i76
