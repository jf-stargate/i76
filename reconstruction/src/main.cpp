#include "i76/command.h"
#include "i76/runtime.h"

#include <exception>
#include <iostream>
#include <string>
#include <vector>


static int run(int argc, char* argv[])
{
    std::vector<std::string> commands{};
    bool interactive{};

    for (int index = 1; index < argc; ++index) {
        const std::string arg{argv[index]};
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

    i76_runtime game{};
    i76_runtime_config config{};
    config.tick_rate = 60U;
    const i76_result_code initialized =
        i76_runtime_initialize(game, config, i76_make_null_outputs());
    if (initialized != i76_result_code::ok) {
        std::cerr << "unable to initialize i76_runtime\n";
        return 1;
    }

    int exit_code{};
    const auto process = [&](const std::string& command) {
        const i76_command_result result = i76_execute_command(game, command);
        if (result.code == i76_result_code::ok) {
            std::cout << result.message << '\n';
        } else {
            std::cerr << result.message << '\n';
            exit_code = 1;
        }
    };

    for (const std::string& command : commands) {
        if (game.state.exit_requested) {
            break;
        }
        process(command);
    }
    if (interactive && !game.state.exit_requested) {
        std::string line{};
        while (!game.state.exit_requested && std::getline(std::cin, line)) {
            process(line);
        }
    }

    const i76_result_code shutdown = i76_runtime_shutdown(game);
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
