#include "i76/shell_frontends.h"

#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

static std::uint32_t failures = 0;

// -----------------------------------------------------------------------------
// Record a test failure when the expected condition is false.
// -----------------------------------------------------------------------------
static void expect(bool condition, const char* label)
{
    if (!condition) {
        std::cerr << "FAIL: " << label << '\n';
        ++failures;
    }
}

// -----------------------------------------------------------------------------
// Verify execution of scripted terminal commands.
// -----------------------------------------------------------------------------
static void test_scripted_terminal()
{
    i76_runtime game = {};
    i76_shell_state shell = {};
    i76_runtime_config config = {};
    std::vector<std::string> commands = {"play", "step 3", "status", "menu",
        "exit"};
    std::istringstream input = {};
    std::ostringstream output = {};
    std::ostringstream errors = {};
    std::int32_t code = 0;

    config.tick_rate = 60U;
    expect(i76_runtime_initialize(game, config, i76_make_null_outputs()) ==
               i76_result_code::ok, "runtime initialization");
    expect(i76_shell_initialize(shell, game) == i76_result_code::ok,
           "shell initialization");
    code = i76_run_terminal_shell(shell, game, commands, false, input, output,
        errors);
    expect(code == 0 && errors.str().empty(), "scripted execution succeeds");
    expect(output.str().find("INTERSTATE '76") != std::string::npos,
           "initial main menu visible");
    expect(output.str().find("TEST SESSION") != std::string::npos,
           "session menu visible");
    expect(output.str().find("ticks=3 paused=false") != std::string::npos,
           "runtime status visible");
    expect(game.state.exit_requested, "exit command reaches runtime");
    expect(i76_shell_shutdown(shell) == i76_result_code::ok, "shell teardown");
    expect(i76_runtime_shutdown(game) == i76_result_code::ok,
        "runtime teardown");
}

// -----------------------------------------------------------------------------
// Verify interactive terminal input and line editing.
// -----------------------------------------------------------------------------
static void test_interactive_terminal()
{
    i76_runtime game = {};
    i76_shell_state shell = {};
    i76_runtime_config config = {};
    std::vector<std::string> commands = {};
    std::istringstream input{"2\n1\n1\n2\n7\n4\n"};
    std::ostringstream output = {};
    std::ostringstream errors = {};
    std::int32_t code = 0;

    config.tick_rate = 100U;
    expect(i76_runtime_initialize(game, config, i76_make_null_outputs()) ==
               i76_result_code::ok, "runtime initialization");
    expect(i76_shell_initialize(shell, game) == i76_result_code::ok,
           "shell initialization");
    code = i76_run_terminal_shell(shell, game, commands, true, input, output,
        errors);
    expect(code == 0, "interactive terminal returns success");
    expect(game.state.tick == 1U, "numbered menu actions stepped runtime");
    expect(game.state.exit_requested, "interactive exit submitted");
    expect(output.str().find("i76> ") != std::string::npos, "prompt visible");
    expect(i76_shell_shutdown(shell) == i76_result_code::ok, "shell cleanup");
    expect(i76_runtime_shutdown(game) == i76_result_code::ok,
        "runtime cleanup");
}

// -----------------------------------------------------------------------------
// Verify terminal handling of malformed input and exit conditions.
// -----------------------------------------------------------------------------
static void test_terminal_errors()
{
    i76_runtime game = {};
    i76_shell_state shell = {};
    i76_runtime_config config = {};
    std::vector<std::string> commands = {"step 3"};
    std::istringstream input = {};
    std::ostringstream output = {};
    std::ostringstream errors = {};
    std::int32_t code = 0;

    code = i76_run_terminal_shell(shell, game, commands, false, input, output,
        errors);
    expect(code == 1 && errors.str().find("not initialized") !=
        std::string::npos,
           "uninitialized use fails clearly");
    config.tick_rate = 60U;
    i76_runtime_initialize(game, config, i76_make_null_outputs());
    i76_shell_initialize(shell, game);
    errors.str({});
    errors.clear();
    code = i76_run_terminal_shell(shell, game, commands, false, input, output,
        errors);
    expect(code == 1 && errors.str().find("unavailable") != std::string::npos,
           "invalid command reported");
    expect(game.state.tick == 0U,
        "invalid terminal command leaves state intact");
    i76_shell_shutdown(shell);
    i76_runtime_shutdown(game);
}

// -----------------------------------------------------------------------------
// Run the test suite or produce a fixture for functional tests.
// -----------------------------------------------------------------------------
int main()
{
    test_scripted_terminal();
    test_interactive_terminal();
    test_terminal_errors();
    return failures == 0U ? 0 : 1;
}
