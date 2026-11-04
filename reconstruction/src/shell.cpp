#include "i76/shell.h"

#include <utility>

static std::string_view trim_shell_input(std::string_view input)
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

static i76_command_result shell_reply(i76_shell_state& shell, i76_runtime& game,
                                      i76_result_code code, std::string message)
{
    i76_command_result result = {};
    i76_diagnostic_level level = i76_diagnostic_level::error;

    result.code = code;
    result.message = std::move(message);
    if (code == i76_result_code::ok) {
        level = i76_diagnostic_level::info;
    }
    shell.notice = result.message;
    i76_runtime_emit_diagnostic(game, level, result.message);
    return result;
}

i76_result_code i76_shell_initialize(i76_shell_state& shell, const i76_runtime& game) noexcept
{
    if (shell.initialized) {
        return i76_result_code::already_initialized;
    }
    if (!game.state.initialized) {
        return i76_result_code::not_initialized;
    }

    shell = {};
    shell.initialized = true;
    shell.page = i76_shell_page::main_menu;
    return i76_result_code::ok;
}

i76_result_code i76_shell_shutdown(i76_shell_state& shell)
{
    if (!shell.initialized) {
        return i76_result_code::not_initialized;
    }
    shell = {};
    return i76_result_code::ok;
}

i76_shell_view i76_shell_make_view(const i76_shell_state& shell) noexcept
{
    i76_shell_view view = {};

    if (!shell.initialized) {
        return view;
    }

    switch (shell.page) {
    case i76_shell_page::main_menu:
        view.title = "INTERSTATE '76";
        view.subtitle = "Reconstruction shell / original assets not loaded";
        view.items[0] = {"Start test session", "play"};
        view.items[1] = {"Options", "options"};
        view.items[2] = {"About", "about"};
        view.items[3] = {"Exit", "exit"};
        view.item_count = 4U;
        break;
    case i76_shell_page::options:
        view.title = "OPTIONS";
        view.subtitle = "Configuration will be connected to the application services";
        view.items[0] = {"Back to main menu", "back"};
        view.item_count = 1U;
        break;
    case i76_shell_page::about:
        view.title = "ABOUT";
        view.subtitle = "Independent I76 engine framework - no retail resources included";
        view.items[0] = {"Back to main menu", "back"};
        view.item_count = 1U;
        break;
    case i76_shell_page::session:
        view.title = "TEST SESSION";
        view.subtitle = "Synthetic world registry - missions and gameplay are not implemented";
        view.items[0] = {"Status", "status"};
        view.items[1] = {"Step 1 tick", "step 1"};
        view.items[2] = {"Step 60 ticks", "step 60"};
        view.items[3] = {"List world objects", "object list"};
        view.items[4] = {"Pause", "pause"};
        view.items[5] = {"Resume", "resume"};
        view.items[6] = {"Return to menu", "menu"};
        view.items[7] = {"Exit", "exit"};
        view.item_count = 8U;
        break;
    }
    return view;
}

i76_command_result i76_shell_execute(i76_shell_state& shell, i76_runtime& game,
                                     std::string_view command)
{
    i76_command_result result = {};
    i76_result_code code = i76_result_code::ok;
    i76_world_result world_code = i76_world_result::ok;
    i76_world_handle demo_handle = {};
    std::uint32_t index = 0;

    if (!shell.initialized || !game.state.initialized) {
        return {i76_result_code::not_initialized, "shell or runtime is not initialized"};
    }

    command = trim_shell_input(command);
    if (command.size() == 1U && command[0] >= '1' && command[0] <= '8') {
        index = static_cast<std::uint32_t>(command[0] - '1');
        return i76_shell_select(shell, game, index);
    }
    if (command == "help") {
        return shell_reply(shell, game, i76_result_code::ok,
                           "select 1-8 or use: play options about back menu status pause resume "
                           "step <n> object <action> exit");
    }
    if (command == "exit" || command == "quit") {
        code = i76_runtime_request_exit(game);
        return shell_reply(shell, game, code, "exit requested");
    }
    if (command == "back" || command == "menu") {
        if (shell.page == i76_shell_page::main_menu) {
            return shell_reply(shell, game, i76_result_code::invalid_argument,
                               "already at main menu");
        }
        if (shell.page == i76_shell_page::session) {
            world_code = i76_world_clear(game.world);
            if (world_code != i76_world_result::ok) {
                return shell_reply(shell, game, i76_result_code::not_initialized,
                                   "unable to unload test world");
            }
        }
        shell.page = i76_shell_page::main_menu;
        shell.selected_index = 0U;
        return shell_reply(shell, game, i76_result_code::ok, "main menu");
    }
    if (shell.page == i76_shell_page::main_menu) {
        if (command == "play") {
            world_code = i76_world_clear(game.world);
            if (world_code == i76_world_result::ok) {
                world_code = i76_world_create(game.world, i76_world_kind::vehicle,
                                               "demo_car", demo_handle);
            }
            if (world_code == i76_world_result::ok) {
                world_code = i76_world_create(game.world, i76_world_kind::marker,
                                               "demo_checkpoint", demo_handle);
            }
            if (world_code != i76_world_result::ok) {
                i76_world_clear(game.world);
                return shell_reply(shell, game, i76_result_code::overflow,
                                   "unable to initialize synthetic world");
            }
            shell.page = i76_shell_page::session;
            shell.selected_index = 0U;
            return shell_reply(shell, game, i76_result_code::ok,
                               "test session started (2 synthetic objects; no mission loaded)");
        }
        if (command == "options") {
            shell.page = i76_shell_page::options;
            shell.selected_index = 0U;
            return shell_reply(shell, game, i76_result_code::ok, "options");
        }
        if (command == "about") {
            shell.page = i76_shell_page::about;
            shell.selected_index = 0U;
            return shell_reply(shell, game, i76_result_code::ok, "about");
        }
    }
    if (shell.page == i76_shell_page::session) {
        if (command == "status" || command == "pause" || command == "resume" ||
            command == "step" || command.starts_with("step ") ||
            command.starts_with("step\t") || command == "object" ||
            command.starts_with("object ") || command.starts_with("object\t")) {
            result = i76_execute_command(game, command);
            shell.notice = result.message;
            return result;
        }
    }
    return shell_reply(shell, game, i76_result_code::unknown_command,
                       "command unavailable on this page (type help)");
}

i76_command_result i76_shell_select(i76_shell_state& shell, i76_runtime& game,
                                    std::uint32_t item_index)
{
    i76_shell_view view = {};

    if (!shell.initialized || !game.state.initialized) {
        return {i76_result_code::not_initialized, "shell or runtime is not initialized"};
    }
    view = i76_shell_make_view(shell);
    if (item_index >= view.item_count) {
        return shell_reply(shell, game, i76_result_code::invalid_argument,
                           "invalid menu selection");
    }
    return i76_shell_execute(shell, game, view.items[item_index].command);
}
