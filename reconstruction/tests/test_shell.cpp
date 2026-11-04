#include "i76/shell.h"

#include <cstdint>
#include <iostream>
#include <string_view>

static std::uint32_t failures = 0;

static void expect(bool condition, const char* label)
{
    if (!condition) {
        std::cerr << "FAIL: " << label << '\n';
        ++failures;
    }
}

static void test_lifecycle()
{
    i76_shell_state shell = {};
    i76_runtime game = {};
    i76_runtime_config config = {};
    i76_shell_view view = {};

    expect(!shell.initialized && shell.selected_index == 0U && shell.notice.empty(),
           "shell zero initialization");
    expect(i76_shell_make_view(shell).item_count == 0U, "uninitialized view empty");
    expect(i76_shell_shutdown(shell) == i76_result_code::not_initialized,
           "shutdown before init rejected");
    expect(i76_shell_initialize(shell, game) == i76_result_code::not_initialized,
           "shell requires initialized runtime");
    expect(i76_shell_execute(shell, game, "play").code == i76_result_code::not_initialized,
           "execute before init rejected");
    expect(i76_shell_select(shell, game, 0U).code == i76_result_code::not_initialized,
           "select before init rejected");

    config.tick_rate = 60U;
    expect(i76_runtime_initialize(game, config, i76_make_null_outputs()) ==
               i76_result_code::ok, "runtime init");
    expect(i76_shell_initialize(shell, game) == i76_result_code::ok, "shell init");
    expect(i76_shell_initialize(shell, game) == i76_result_code::already_initialized,
           "duplicate init rejected");
    view = i76_shell_make_view(shell);
    expect(view.item_count == 4U && view.items[0].command == "play",
           "main menu available after init");
    expect(i76_shell_shutdown(shell) == i76_result_code::ok, "shell shutdown");
    expect(!shell.initialized && shell.notice.empty() && shell.selected_index == 0U,
           "shell shutdown resets state");
    expect(i76_shell_initialize(shell, game) == i76_result_code::ok, "repeat shell init");
    expect(i76_shell_shutdown(shell) == i76_result_code::ok, "repeat shell shutdown");
    expect(i76_runtime_shutdown(game) == i76_result_code::ok, "runtime shutdown");
}

static void test_navigation()
{
    i76_shell_state shell = {};
    i76_runtime game = {};
    i76_runtime_config config = {};
    i76_recording_outputs record = {};
    i76_shell_view view = {};
    i76_command_result reply = {};

    config.tick_rate = 60U;
    expect(i76_runtime_initialize(game, config, i76_make_recording_outputs(record)) ==
               i76_result_code::ok, "runtime init");
    expect(i76_shell_initialize(shell, game) == i76_result_code::ok, "shell init");
    expect(i76_shell_execute(shell, game, " 2 \t").code == i76_result_code::ok &&
               shell.page == i76_shell_page::options, "numbered options selection");
    view = i76_shell_make_view(shell);
    expect(view.item_count == 1U && view.items[0].command == "back", "options menu");
    expect(i76_shell_select(shell, game, 0U).code == i76_result_code::ok &&
               shell.page == i76_shell_page::main_menu, "select back");
    expect(i76_shell_execute(shell, game, "3").code == i76_result_code::ok &&
               shell.page == i76_shell_page::about, "about selection");
    expect(i76_shell_execute(shell, game, "back").code == i76_result_code::ok,
           "return from about");
    expect(i76_shell_execute(shell, game, "menu").code == i76_result_code::invalid_argument,
           "menu at root rejected");
    expect(i76_shell_select(shell, game, 100U).code == i76_result_code::invalid_argument,
           "out-of-range selection rejected");
    expect(i76_shell_execute(shell, game, "9").code == i76_result_code::unknown_command,
           "bad numeric selection rejected");
    expect(i76_shell_execute(shell, game, "options trailing").code ==
               i76_result_code::unknown_command, "trailing data rejected");
    expect(shell.page == i76_shell_page::main_menu && game.state.tick == 0U,
           "invalid actions do not mutate game or page");

    expect(i76_shell_execute(shell, game, "1").code == i76_result_code::ok &&
               shell.page == i76_shell_page::session, "start synthetic session");
    view = i76_shell_make_view(shell);
    expect(view.item_count == 8U && view.items[1].command == "step 1",
           "session actions exposed as data");
    expect(i76_shell_execute(shell, game, "step 3").code == i76_result_code::ok &&
               game.state.tick == 3U, "session dispatches runtime step");
    expect(i76_shell_execute(shell, game, "pause").code == i76_result_code::ok &&
               game.state.paused, "pause forwarded");
    expect(i76_shell_execute(shell, game, "status").message.find("ticks=3") !=
               std::string::npos, "session status forwarded");
    expect(i76_shell_execute(shell, game, "step 0").code == i76_result_code::invalid_argument &&
               game.state.tick == 3U, "invalid step leaves state unchanged");
    expect(i76_shell_execute(shell, game, "resume").code == i76_result_code::ok &&
               !game.state.paused, "resume forwarded");
    expect(i76_shell_execute(shell, game, "about").code == i76_result_code::unknown_command &&
               shell.page == i76_shell_page::session, "invalid session command rejected");
    expect(i76_shell_execute(shell, game, "menu").code == i76_result_code::ok &&
               shell.page == i76_shell_page::main_menu, "return to menu");
    expect(i76_shell_execute(shell, game, "status").code == i76_result_code::unknown_command,
           "runtime status unavailable from main menu");
    expect(record.scene.size() == 3U, "scene events from real runtime");
    expect(!record.diagnostics.empty(), "diagnostic events captured");
    expect(i76_shell_execute(shell, game, "help").code == i76_result_code::ok,
           "shell help available");
    reply = i76_shell_execute(shell, game, "4");
    expect(reply.code == i76_result_code::ok && game.state.exit_requested,
           "exit requests application shutdown");
    expect(i76_shell_shutdown(shell) == i76_result_code::ok, "shell shutdown");
    expect(i76_runtime_shutdown(game) == i76_result_code::ok, "runtime shutdown");
}

static void test_null_equivalence()
{
    i76_shell_state null_shell = {};
    i76_shell_state record_shell = {};
    i76_runtime null_game = {};
    i76_runtime record_game = {};
    i76_recording_outputs record = {};
    i76_runtime_config config = {};

    config.tick_rate = 60U;
    expect(i76_runtime_initialize(null_game, config, i76_make_null_outputs()) ==
               i76_result_code::ok, "null runtime init");
    expect(i76_runtime_initialize(record_game, config, i76_make_recording_outputs(record)) ==
               i76_result_code::ok, "recording runtime init");
    expect(i76_shell_initialize(null_shell, null_game) == i76_result_code::ok,
           "null shell init");
    expect(i76_shell_initialize(record_shell, record_game) == i76_result_code::ok,
           "recording shell init");
    i76_shell_execute(null_shell, null_game, "play");
    i76_shell_execute(record_shell, record_game, "play");
    i76_shell_execute(null_shell, null_game, "step 6");
    i76_shell_execute(record_shell, record_game, "step 6");
    expect(null_game.state.tick == record_game.state.tick && record.scene.size() == 6U,
           "null sink and recording sink have identical game state");
    expect(null_shell.page == record_shell.page, "null sink preserves shell state");
    expect(i76_shell_shutdown(null_shell) == i76_result_code::ok, "null shell cleanup");
    expect(i76_shell_shutdown(record_shell) == i76_result_code::ok, "record shell cleanup");
    expect(i76_runtime_shutdown(null_game) == i76_result_code::ok, "null runtime cleanup");
    expect(i76_runtime_shutdown(record_game) == i76_result_code::ok,
           "record runtime cleanup");
}

int main()
{
    test_lifecycle();
    test_navigation();
    test_null_equivalence();
    return failures == 0U ? 0 : 1;
}
