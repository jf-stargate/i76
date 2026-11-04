#include "i76/shell_frontends.h"
#include "i76/line_editor.h"

#include <iostream>

static void print_shell_menu(const i76_shell_state& shell, std::ostream& output)
{
    i76_shell_view view = i76_shell_make_view(shell);
    std::uint32_t index = 0;

    output << "\n== " << view.title << " ==\n";
    output << view.subtitle << "\n";
    for (index = 0; index < view.item_count; ++index) {
        output << "  " << (index + 1U) << ") " << view.items[index].label << "\n";
    }
    output << "Type a number or 'help'.\n";
}

static void process_shell_command(i76_shell_state& shell, i76_runtime& game,
                                  std::string_view line, std::int32_t& exit_code,
                                  std::ostream& output, std::ostream& errors)
{
    i76_shell_page previous = shell.page;
    i76_command_result reply = i76_shell_execute(shell, game, line);

    if (reply.code == i76_result_code::ok) {
        output << reply.message << '\n';
    } else {
        errors << reply.message << '\n';
        exit_code = 1;
    }
    if (!game.state.exit_requested && shell.page != previous) {
        print_shell_menu(shell, output);
    }
}

std::int32_t i76_run_terminal_shell(i76_shell_state& shell, i76_runtime& game,
                                    const std::vector<std::string>& commands, bool interactive,
                                    std::istream& input, std::ostream& output, std::ostream& errors)
{
    std::int32_t exit_code = 0;
    std::string line = {};
    i76_line_editor editor = {};

    if (!shell.initialized || !game.state.initialized) {
        errors << "shell or runtime not initialized\n";
        return 1;
    }

    print_shell_menu(shell, output);
    for (const std::string& command : commands) {
        if (game.state.exit_requested) {
            break;
        }
        process_shell_command(shell, game, command, exit_code, output, errors);
        i76_line_editor_remember(editor, command);
    }

    if (interactive && !game.state.exit_requested) {
        while (!game.state.exit_requested) {
            if (!i76_terminal_read_line(input, output, editor, "i76> ", line)) {
                break;
            }
            process_shell_command(shell, game, line, exit_code, output, errors);
        }
    }
    return exit_code;
}
