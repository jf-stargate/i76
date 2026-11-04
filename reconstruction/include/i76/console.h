#pragma once

#include "i76/command.h"

#include <string>
#include <string_view>
#include <vector>

// Syntax parsing is independent of the runtime and never performs side effects.
struct i76_console_tokens {
    std::vector<std::string> values{};
    std::string error{};
};

i76_console_tokens i76_console_tokenize(std::string_view line);

// Headless and terminal shell entry point. Commands and CVars share one registry.
i76_command_result i76_console_execute(i76_runtime& game, std::string_view line);

// Registry-backed candidates, suitable for a future terminal/SDL completion frontend.
std::vector<std::string> i76_console_complete(std::string_view prefix);
