#pragma once

#include "i76/command.h"

#include <array>
#include <cstdint>
#include <string>
#include <string_view>

// This shell is an application front end, not an emulation of i76shell.dll.
// It has no direct graphics, audio, terminal, filesystem, or OS dependencies.
enum class i76_shell_page : std::uint8_t {
    main_menu = 0,
    options,
    about,
    session,
};

struct i76_shell_item {
    std::string_view label{};
    std::string_view command{};
};

struct i76_shell_view {
    std::string_view title{};
    std::string_view subtitle{};
    std::array<i76_shell_item, 8> items{};
    std::uint32_t item_count{};
};

struct i76_shell_state {
    bool initialized{};
    i76_shell_page page{};
    std::uint32_t selected_index{};
    std::string notice{};
};

i76_result_code i76_shell_initialize(i76_shell_state& shell, const i76_runtime& game) noexcept;
i76_result_code i76_shell_shutdown(i76_shell_state& shell);
i76_shell_view i76_shell_make_view(const i76_shell_state& shell) noexcept;
i76_command_result i76_shell_execute(i76_shell_state& shell, i76_runtime& game,
                                     std::string_view command);
i76_command_result i76_shell_select(i76_shell_state& shell, i76_runtime& game,
                                    std::uint32_t item_index);
