#pragma once

#include "i76/runtime.h"

#include <string>
#include <string_view>


struct i76_command_result {
    i76_result_code code{};
    std::string message{};
};

// Parse and execute one command at a well-defined host/simulation boundary.
// In particular, a failed parse must not mutate the i76_runtime.
i76_command_result i76_execute_command(i76_runtime& game,
                                       std::string_view line);

