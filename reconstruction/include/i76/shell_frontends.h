#pragma once

#include "i76/shell.h"

#include <cstdint>
#include <iosfwd>
#include <string>
#include <vector>

// Frontend helpers; portable core does not depend on terminal or SDL headers.
std::int32_t i76_run_terminal_shell(i76_shell_state& shell,
                                    i76_runtime& game,
                                    const std::vector<std::string>& commands,
                                    bool interactive,
                                    std::istream& input,
                                    std::ostream& output,
                                    std::ostream& errors);

#ifdef I76_ENABLE_SDL3
std::int32_t i76_run_sdl_shell(i76_shell_state& shell,
                               i76_runtime& game,
                               std::uint32_t maximum_frames);
#endif
