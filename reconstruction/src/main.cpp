#include "i76/command.h"
#include "i76/line_editor.h"
#include "i76/runtime.h"
#include "i76/shell.h"
#include "i76/shell_frontends.h"

#ifdef I76_ENABLE_SDL3
#include <SDL3/SDL_main.h>
#endif

#include <charconv>
#include <cstdint>
#include <exception>
#include <iostream>
#include <string>
#include <system_error>
#include <vector>

static void print_help()
{
    std::cout << "usage: i76 [--headless] [--command <text>]... [--interactive]\n"
              << "       i76 --shell[=terminal|sdl] [--command <text>]... [--interactive]\n"
              << "       i76 --shell=sdl [--shell-frames <count>]\n"
              << "commands: help status pause resume step <count> object <action> "
                 "resource <action> level <action> asset stats quit\n";
}

static void process_runtime_command(i76_runtime& game, const std::string& command,
                                    std::int32_t& exit_code)
{
    i76_command_result result = i76_execute_command(game, command);

    if (result.code == i76_result_code::ok) {
        std::cout << result.message << '\n';
    } else {
        std::cerr << result.message << '\n';
        exit_code = 1;
    }
}

static std::int32_t run(int argc, char* argv[])
{
    std::vector<std::string> commands = {};
    std::string shell_mode = {};
    std::string line = {};
    i76_line_editor editor = {};
    bool interactive = false;
    std::uint32_t maximum_frames = 0;
    std::int32_t exit_code = 0;
    std::int32_t index = 0;
    i76_runtime game = {};
    i76_runtime_config config = {};
    i76_shell_state shell = {};
    i76_result_code result = i76_result_code::ok;
    const char* begin = nullptr;
    const char* end = nullptr;
    std::from_chars_result parsed = {};

    for (index = 1; index < argc; ++index) {
        const std::string argument = argv[index];

        if (argument == "--help") {
            print_help();
            return 0;
        }
        if (argument == "--version") {
            std::cout << "i76 reconstruction framework 0.2.0\n";
            return 0;
        }
        if (argument == "--headless") {
            continue;
        }
        if (argument == "--interactive") {
            interactive = true;
            continue;
        }
        if (argument == "--shell" || argument == "--shell=terminal") {
            shell_mode = "terminal";
            continue;
        }
        if (argument == "--shell=sdl") {
            shell_mode = "sdl";
            continue;
        }
        if (argument == "--shell-frames" && index + 1 < argc) {
            const std::string value = argv[++index];
            begin = value.data();
            end = begin + value.size();
            maximum_frames = 0;
            parsed = std::from_chars(begin, end, maximum_frames, 10);
            if (parsed.ec != std::errc{} || parsed.ptr != end || maximum_frames == 0U ||
                maximum_frames > 10000U) {
                std::cerr << "invalid shell frame count\n";
                return 2;
            }
            continue;
        }
        if (argument == "--command" && index + 1 < argc) {
            commands.emplace_back(argv[++index]);
            continue;
        }
        std::cerr << "invalid argument: " << argument << '\n';
        return 2;
    }

    if (maximum_frames != 0U && shell_mode != "sdl") {
        std::cerr << "--shell-frames requires --shell=sdl\n";
        return 2;
    }
    if (shell_mode == "sdl" && (!commands.empty() || interactive)) {
        std::cerr << "SDL shell does not accept --command or --interactive\n";
        return 2;
    }

    config.tick_rate = 60U;
    result = i76_runtime_initialize(game, config, i76_make_null_outputs());
    if (result != i76_result_code::ok) {
        std::cerr << "unable to initialize runtime\n";
        return 1;
    }

    if (!shell_mode.empty()) {
        result = i76_shell_initialize(shell, game);
        if (result == i76_result_code::ok) {
            if (shell_mode == "terminal") {
                exit_code = i76_run_terminal_shell(shell, game, commands,
                                                     interactive || commands.empty(),
                                                     std::cin, std::cout, std::cerr);
            } else {
#ifdef I76_ENABLE_SDL3
                exit_code = i76_run_sdl_shell(shell, game, maximum_frames);
#else
                std::cerr << "SDL3 shell backend unavailable. Rebuild with "
                          << "-DI76_ENABLE_SDL3=ON (requires libsdl3-dev).\n";
                exit_code = 2;
#endif
            }
        } else {
            std::cerr << "unable to initialize shell\n";
            exit_code = 1;
        }
        if (shell.initialized && i76_shell_shutdown(shell) != i76_result_code::ok) {
            exit_code = 1;
        }
    } else {
        for (const std::string& command : commands) {
            if (game.state.exit_requested) {
                break;
            }
            process_runtime_command(game, command, exit_code);
            i76_line_editor_remember(editor, command);
        }
        if (interactive && !game.state.exit_requested) {
            while (!game.state.exit_requested &&
                   i76_terminal_read_line(std::cin, std::cout, editor, "i76> ", line)) {
                process_runtime_command(game, line, exit_code);
            }
        }
    }

    if (i76_runtime_shutdown(game) != i76_result_code::ok) {
        exit_code = 1;
    }
    return exit_code;
}

int main(int argc, char* argv[])
{
    try {
        return run(argc, argv);
    } catch (const std::exception& error) {
        std::cerr << "fatal error: " << error.what() << '\n';
        return 1;
    }
}
