#include "i76/command.h"
#include "i76/runtime.h"

#include <cstdint>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

static void process_command(i76_runtime& game, const std::string& command,
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
    bool interactive = false;
    std::int32_t index = 0;
    std::int32_t exit_code = 0;
    i76_runtime game = {};
    i76_runtime_config config = {};
    i76_result_code initialized = i76_result_code::ok;
    i76_result_code shutdown = i76_result_code::ok;
    std::string line = {};

    for (index = 1; index < argc; ++index) {
        const std::string arg = argv[index];

        if (arg == "--help") {
            std::cout << "usage: i76 [--headless] [--command <text>]... [--interactive]"
                      << "\ncommands: help status pause resume step <count> quit\n";
            return 0;
        }
        if (arg == "--version") {
            std::cout << "i76 reconstruction framework 0.1.0\n";
            return 0;
        }
        if (arg == "--headless") {
            continue;
        }
        if (arg == "--interactive") {
            interactive = true;
            continue;
        }
        if (arg == "--command" && index + 1 < argc) {
            commands.emplace_back(argv[++index]);
            continue;
        }

        std::cerr << "invalid argument: " << arg << '\n';
        return 2;
    }

    config.tick_rate = 60U;
    initialized = i76_runtime_initialize(game, config, i76_make_null_outputs());

    if (initialized != i76_result_code::ok) {
        std::cerr << "unable to initialize runtime\n";
        return 1;
    }

    for (const std::string& command : commands) {
        if (game.state.exit_requested) {
            break;
        }
        process_command(game, command, exit_code);
    }

    if (interactive && !game.state.exit_requested) {
        while (!game.state.exit_requested && std::getline(std::cin, line)) {
            process_command(game, line, exit_code);
        }
    }

    shutdown = i76_runtime_shutdown(game);
    return shutdown == i76_result_code::ok ? exit_code : 1;
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
