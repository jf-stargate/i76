#pragma once

#include "i76/runtime.h"

#include <string>
#include <string_view>

namespace i76 {

struct command_result {
    result_code code{};
    std::string message{};
};

// Parse and execute one command at a well-defined host/simulation boundary.
// In particular, a failed parse must not mutate the runtime.
command_result execute_command(runtime& game, std::string_view line);

} // namespace i76
