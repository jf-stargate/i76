#include "i76/shell.h"

#include <utility>

// -----------------------------------------------------------------------------
// Trim surrounding whitespace from shell input.
// -----------------------------------------------------------------------------
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

// -----------------------------------------------------------------------------
// Determine whether input addresses a known shell command namespace.
// -----------------------------------------------------------------------------
static bool shell_namespace(std::string_view command,
                            std::string_view name) noexcept
{
    return command == name
           || (command.size() > name.size()
           && command.starts_with(name)
           && (command[name.size()] == ' '
           || command[name.size()] == '\t'));
}

// -----------------------------------------------------------------------------
// Update the shell notice and return a runtime command reply.
// -----------------------------------------------------------------------------
static i76_command_result shell_reply(i76_shell_state& shell,
                                      i76_runtime& game,
                                      i76_result_code code,
                                      std::string message)
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

// -----------------------------------------------------------------------------
// Initialize the presentation-independent shell state.
// -----------------------------------------------------------------------------
i76_result_code i76_shell_initialize(i76_shell_state& shell,
                                     const i76_runtime& game) noexcept
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

// -----------------------------------------------------------------------------
// Release shell state after a session completes.
// -----------------------------------------------------------------------------
i76_result_code i76_shell_shutdown(i76_shell_state& shell)
{
    if (!shell.initialized) {
        return i76_result_code::not_initialized;
    }
    shell = {};
    return i76_result_code::ok;
}

// -----------------------------------------------------------------------------
// Build the menu view for the shell's current page.
// -----------------------------------------------------------------------------
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
        view.subtitle =
            "Configuration will be connected to the application services";
        view.items[0] = {"Back to main menu", "back"};
        view.item_count = 1U;
        break;
    case i76_shell_page::about:
        view.title = "ABOUT";
        view.subtitle =
            "Independent I76 engine framework - no retail resources included";
        view.items[0] = {"Back to main menu", "back"};
        view.item_count = 1U;
        break;
    case i76_shell_page::session:
        view.title = "TEST SESSION";
        view.subtitle =
            "Synthetic level and world registry - retail missions not loaded";
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

// -----------------------------------------------------------------------------
// Execute a shell command without duplicating engine behavior.
// -----------------------------------------------------------------------------
i76_command_result i76_shell_execute(i76_shell_state& shell,
                                     i76_runtime& game,
                                     std::string_view command)
{
    i76_command_result result = {};
    i76_result_code code = i76_result_code::ok;
    std::uint32_t index = 0;

    if (!shell.initialized
        || !game.state.initialized) {
        return {i76_result_code::not_initialized,
            "shell or runtime is not initialized"};
    }

    command = trim_shell_input(command);
    if (command.size() == 1U
        && command[0] >= '1'
        && command[0] <= '8') {
        index = static_cast<std::uint32_t>(command[0] - '1');
        return i76_shell_select(shell, game, index);
    }
    if (command == "help") {
        return shell_reply(shell, game, i76_result_code::ok,
                           "select 1-8 or use: play options about back menu "
                           "status pause resume "
                           "step <n> object <action> level <action> "
                           "resource <action> asset stats exit");
    }
    if (command == "exit"
        || command == "quit") {
        code = i76_runtime_request_exit(game);
        return shell_reply(shell, game, code, "exit requested");
    }
    if (command == "back"
        || command == "menu") {
        if (shell.page == i76_shell_page::main_menu) {
            return shell_reply(shell, game, i76_result_code::invalid_argument,
                               "already at main menu");
        }
        if (shell.page == i76_shell_page::session) {
            if (game.active_level.loaded) {
                result = i76_execute_command(game, "level unload");
                if (result.code != i76_result_code::ok) {
                    return result;
                }
            } else {
                i76_world_clear(game.world);
            }
        }
        shell.page = i76_shell_page::main_menu;
        shell.selected_index = 0U;
        return shell_reply(shell, game, i76_result_code::ok, "main menu");
    }
    if (shell_namespace(command, "resource")
        || shell_namespace(command,
        "asset")
        || shell_namespace(command, "level")
        || shell_namespace(command, "find")
        || (shell_namespace(command, "help")
        && command != "help")
        || command.starts_with("sim.")
        || command.starts_with("world.")) {
        result = i76_execute_command(game, command);
        shell.notice = result.message;
        if (result.code == i76_result_code::ok
            && game.active_level.loaded
            && (command.starts_with("level load ")
            || command == "level activate"))
                {
            shell.page = i76_shell_page::session;
            shell.selected_index = 0U;
        }
        if (result.code == i76_result_code::ok
            && command == "level unload") {
            shell.page = i76_shell_page::main_menu;
            shell.selected_index = 0U;
        }
        return result;
    }
    if (shell.page == i76_shell_page::main_menu) {
        if (command == "play") {
            result = i76_execute_command(game, "level load demo.level");
            if (result.code != i76_result_code::ok) {
                return result;
            }
            shell.page = i76_shell_page::session;
            shell.selected_index = 0U;
            return shell_reply(shell, game, i76_result_code::ok,
                               "test session started (2 synthetic objects; "
                               "no retail mission)");
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
        if (shell_namespace(command, "sim")
            || command == "status"
            || command == "pause"
            || command == "resume"
            || command == "step"
            || command.starts_with("step ")
            || command.starts_with("step\t")
            || command == "object"
            || command.starts_with("object ")
            || command.starts_with("object\t")) {
            result = i76_execute_command(game, command);
            shell.notice = result.message;
            return result;
        }
    }
    return shell_reply(shell, game, i76_result_code::unknown_command,
                       "command unavailable on this page (type help)");
}

// -----------------------------------------------------------------------------
// Run the command associated with a selected menu item.
// -----------------------------------------------------------------------------
i76_command_result i76_shell_select(i76_shell_state& shell,
                                    i76_runtime& game,
                                    std::uint32_t item_index)
{
    i76_shell_view view = {};

    if (!shell.initialized
        || !game.state.initialized) {
        return {i76_result_code::not_initialized,
            "shell or runtime is not initialized"};
    }
    view = i76_shell_make_view(shell);
    if (item_index >= view.item_count) {
        return shell_reply(shell, game, i76_result_code::invalid_argument,
                           "invalid menu selection");
    }
    return i76_shell_execute(shell, game, view.items[item_index].command);
}
