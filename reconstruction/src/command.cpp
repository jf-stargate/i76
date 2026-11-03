#include "i76/command.h"

#include <charconv>
#include <cstdint>
#include <system_error>
#include <utility>


static std::string_view trim(std::string_view input)
{
    std::size_t start = 0;
    std::size_t end = 0;

    start = input.find_first_not_of(" \t\r\n");
    if (start == std::string_view::npos) {
        return {};
    }
    end = input.find_last_not_of(" \t\r\n");
    return input.substr(start, end - start + 1U);
}

static i76_command_result make_reply(i76_runtime& game, i76_result_code code, std::string message)
{
    i76_command_result reply{};
    reply.code = code;
    reply.message = std::move(message);
    i76_runtime_emit_diagnostic(game, code == i76_result_code::ok ? i76_diagnostic_level::info
                                                            : i76_diagnostic_level::error,
                            reply.message);
    return reply;
}


i76_command_result i76_execute_command(i76_runtime& game, std::string_view line)
{
    std::size_t split = 0;
    std::string_view command = {};
    std::string_view args = {};

    if (!game.state.initialized) {
        return {i76_result_code::not_initialized, "runtime is not initialized"};
    }
    line = trim(line);
    if (line.empty()) {
        return make_reply(game, i76_result_code::invalid_argument, "empty command");
    }

    split = line.find_first_of(" \t");
    command = line.substr(0, split);
    args = split == std::string_view::npos ? std::string_view{}
                                                                     : trim(line.substr(split));
    if (command == "help" && args.empty()) {
        return make_reply(game, i76_result_code::ok,
                          "commands: help status pause resume step <count> quit");
    }
    if (command == "status" && args.empty()) {
        return make_reply(game, i76_result_code::ok,
                          "ticks=" + std::to_string(game.state.tick) +
                              " paused=" + (game.state.paused ? "true" : "false") +
                              " exit=" + (game.state.exit_requested ? "true" : "false"));
    }
    if (command == "pause" && args.empty()) {
        i76_runtime_set_paused(game, true);
        return make_reply(game, i76_result_code::ok, "paused");
    }
    if (command == "resume" && args.empty()) {
        i76_runtime_set_paused(game, false);
        return make_reply(game, i76_result_code::ok, "resumed");
    }
    if (command == "quit" && args.empty()) {
        i76_runtime_request_exit(game);
        return make_reply(game, i76_result_code::ok, "exit requested");
    }
    if (command == "step") {
        std::uint32_t count = 0;
        const char* begin = nullptr;
        const char* end = nullptr;
        std::from_chars_result parsed = {};
        i76_result_code result = i76_result_code::ok;

        if (args.empty()) {
            return make_reply(game, i76_result_code::invalid_argument, "step requires a count");
        }
        begin = args.data();
        end = begin + args.size();
        parsed = std::from_chars(begin, end, count, 10);
        if (parsed.ec != std::errc{} || parsed.ptr != end || count == 0U ||
            count > i76_k_max_ticks_per_call) {
            return make_reply(game, i76_result_code::invalid_argument, "invalid step count");
        }
        result = i76_runtime_step(game, count);
        if (result != i76_result_code::ok) {
            return make_reply(game, result, "unable to advance simulation");
        }
        return make_reply(game, i76_result_code::ok,
                          "stepped " + std::to_string(count) + " tick(s)");
    }
    return make_reply(game, i76_result_code::unknown_command, "unknown command");
}

