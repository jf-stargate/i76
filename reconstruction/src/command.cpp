#include "i76/command.h"

#include <charconv>
#include <cstdint>
#include <system_error>
#include <utility>

namespace i76 {
namespace {

std::string_view trim(std::string_view input)
{
    const std::size_t start = input.find_first_not_of(" \t\r\n");
    if (start == std::string_view::npos) {
        return {};
    }
    const std::size_t end = input.find_last_not_of(" \t\r\n");
    return input.substr(start, end - start + 1U);
}

command_result make_reply(runtime& game, result_code code, std::string message)
{
    command_result reply{};
    reply.code = code;
    reply.message = std::move(message);
    runtime_emit_diagnostic(game, code == result_code::ok ? diagnostic_level::info
                                                            : diagnostic_level::error,
                            reply.message);
    return reply;
}

} // namespace

command_result execute_command(runtime& game, std::string_view line)
{
    if (!game.state.initialized) {
        return {result_code::not_initialized, "runtime is not initialized"};
    }
    line = trim(line);
    if (line.empty()) {
        return make_reply(game, result_code::invalid_argument, "empty command");
    }

    const std::size_t split = line.find_first_of(" \t");
    const std::string_view command = line.substr(0, split);
    const std::string_view args = split == std::string_view::npos ? std::string_view{}
                                                                     : trim(line.substr(split));
    if (command == "help" && args.empty()) {
        return make_reply(game, result_code::ok,
                          "commands: help status pause resume step <count> quit");
    }
    if (command == "status" && args.empty()) {
        return make_reply(game, result_code::ok,
                          "ticks=" + std::to_string(game.state.tick) +
                              " paused=" + (game.state.paused ? "true" : "false") +
                              " exit=" + (game.state.exit_requested ? "true" : "false"));
    }
    if (command == "pause" && args.empty()) {
        runtime_set_paused(game, true);
        return make_reply(game, result_code::ok, "paused");
    }
    if (command == "resume" && args.empty()) {
        runtime_set_paused(game, false);
        return make_reply(game, result_code::ok, "resumed");
    }
    if (command == "quit" && args.empty()) {
        runtime_request_exit(game);
        return make_reply(game, result_code::ok, "exit requested");
    }
    if (command == "step") {
        std::uint32_t count{};
        if (args.empty()) {
            return make_reply(game, result_code::invalid_argument, "step requires a count");
        }
        const char* const begin = args.data();
        const char* const end = begin + args.size();
        const std::from_chars_result parsed = std::from_chars(begin, end, count, 10);
        if (parsed.ec != std::errc{} || parsed.ptr != end || count == 0U ||
            count > k_max_ticks_per_call) {
            return make_reply(game, result_code::invalid_argument, "invalid step count");
        }
        const result_code result = runtime_step(game, count);
        if (result != result_code::ok) {
            return make_reply(game, result, "unable to advance simulation");
        }
        return make_reply(game, result_code::ok,
                          "stepped " + std::to_string(count) + " tick(s)");
    }
    return make_reply(game, result_code::unknown_command, "unknown command");
}

} // namespace i76
