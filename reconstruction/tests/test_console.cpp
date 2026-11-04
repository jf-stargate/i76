#include "i76/console.h"

#include <cstdint>
#include <filesystem>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

static std::uint32_t failures = 0U;

// -----------------------------------------------------------------------------
// Record a test failure when an assertion does not hold.
// -----------------------------------------------------------------------------
static void expect(bool condition, const char* description)
{
    if (!condition) {
        std::cerr << "FAIL: " << description << '\n';
        ++failures;
    }
}

// -----------------------------------------------------------------------------
// Verify console lexing, quoting, and malformed input handling.
// -----------------------------------------------------------------------------
static void test_lexer()
{
    i76_console_tokens tokens = {};
    std::string long_line(4097U, 'a');
    std::string long_tokens = {};

    tokens = i76_console_tokenize(" \t resource mount "
    "\"C:\\Games\\Interstate 76\" \t");
    expect(tokens.error.empty()
           && tokens.values.size() == 3U
           && tokens.values[0] == "resource"
           && tokens.values[1] == "mount"
           && tokens.values[2] == "C:\\Games\\Interstate 76",
               "quoted Windows path");
    tokens = i76_console_tokenize("object spawn vehicle \"dune buggy\"");
    expect(tokens.error.empty()
           && tokens.values.size() == 4U
           && tokens.values[3] == "dune buggy", "quoted object name");
    tokens = i76_console_tokenize("object spawn vehicle "
                                  "pre\"middle part\"post");
    expect(tokens.error.empty()
           && tokens.values.size() == 4U
           && tokens.values[3] == "premiddle partpost",
               "adjacent bare and quoted segments");
    tokens = i76_console_tokenize("resource mount \"\"");
    expect(tokens.error.empty()
           && tokens.values.size() == 3U
           && tokens.values[2].empty(),
           "explicit empty token retained");
    tokens = i76_console_tokenize("resource mount \"oops");
    expect(!tokens.error.empty()
           && tokens.values.empty(),
        "reject unterminated quotes");
    tokens = i76_console_tokenize(long_line);
    expect(!tokens.error.empty()
           && tokens.values.empty(),
        "reject overlong command");
    for (std::size_t index = 0U; index < 65U; ++index) {
        long_tokens += "x ";
    }
    tokens = i76_console_tokenize(long_tokens);
    expect(!tokens.error.empty(), "reject excessive tokens");
    tokens = i76_console_tokenize(std::string_view("foo\0bar", 7U));
    expect(!tokens.error.empty(), "reject embedded null");
    tokens = i76_console_tokenize(" \t ");
    expect(tokens.error.empty()
           && tokens.values.empty(),
        "blank line produces no tokens");
}

// -----------------------------------------------------------------------------
// Check command lookup, variable mutation, and completion behavior.
// -----------------------------------------------------------------------------
static void test_console()
{
    i76_runtime game = {};
    i76_runtime_config config = {};
    i76_recording_outputs record = {};
    i76_command_result result = {};
    std::vector<std::string> candidates = {};
    std::filesystem::path directory =
        std::filesystem::temp_directory_path() /
            "i76 console grammar test directory";
    std::error_code error = {};

    expect(i76_console_execute(game, "sim.paused").code ==
        i76_result_code::not_initialized,
           "console requires initialized runtime");
    config.tick_rate = 60U;
    expect(i76_runtime_initialize(game, config,
        i76_make_recording_outputs(record)) ==
               i76_result_code::ok, "initialize runtime");

    candidates = i76_console_complete("sim.");
    expect(candidates.size() == 3U
           && candidates[0] == "sim.paused"
           && candidates[1] == "sim.tick_rate", "completion based on registry");
    expect(i76_execute_command(game, "help").message.find("step <count>") !=
               std::string::npos, "registry help preserves step discovery");
    expect(i76_execute_command(game,
        "resource help").message.find("resource list") !=
               std::string::npos, "resource help from registry");
    expect(i76_execute_command(game,
        "level help").message.find("level commands") !=
               std::string::npos, "level help from registry");
    expect(i76_execute_command(game,
        "help level load").message.find("Prepare and activate") !=
               std::string::npos, "per-command generated help");
    expect(i76_execute_command(game, "help bogus").code ==
               i76_result_code::invalid_argument,
                   "unknown help topic rejected");
    expect(i76_execute_command(game, "find paused").message.find("sim.paused")
        !=
               std::string::npos, "search registry");

    expect(i76_execute_command(game, "sim.paused").message ==
        "sim.paused=false",
           "query live boolean CVar");
    expect(i76_execute_command(game, "sim.paused true").code ==
        i76_result_code::ok
            && game.state.paused, "write pause CVar calls runtime");
    expect(i76_execute_command(game, "sim.paused 0").code == i76_result_code::ok
            && !game.state.paused, "numeric bool spelling");
    expect(i76_execute_command(game, "sim paused").code != i76_result_code::ok,
           "dotted variable is not command");
    expect(i76_execute_command(game, "sim.paused yes").code ==
               i76_result_code::invalid_argument
                   && !game.state.paused,
           "invalid CVar has no side effects");
    expect(i76_execute_command(game, "sim.paused false extra").code ==
               i76_result_code::invalid_argument
                   && !game.state.paused,
           "reject extra variable arguments");
    expect(i76_execute_command(game, "sim.paused ?").message.find("Writable") !=
               std::string::npos, "CVar help shorthand");
    expect(i76_execute_command(game, "sim.tick_rate").message ==
        "sim.tick_rate=60",
           "read-only tick-rate CVar");
    expect(i76_execute_command(game, "sim.tick_rate 120").code ==
               i76_result_code::invalid_argument
                   && game.state.tick_rate == 60U,
           "reject read-only writes");
    expect(i76_execute_command(game,
        "sim.tick_rate ?").message.find("Read-only") !=
               std::string::npos, "read-only CVar help");
    expect(i76_execute_command(game, "world.objects").message ==
        "world.objects=0",
           "world count CVar");
    expect(i76_execute_command(game, "sim pause").code == i76_result_code::ok
           && game.state.paused, "hierarchical pause");
    expect(i76_execute_command(game, "sim resume").code == i76_result_code::ok
            && !game.state.paused, "hierarchical resume");
    expect(i76_execute_command(game, "sim step 3").code == i76_result_code::ok
            && game.state.tick == 3U, "hierarchical step");
    expect(i76_execute_command(game, "sim.tick").message == "sim.tick=3",
           "tick CVar tracks runtime");
    expect(i76_execute_command(game, "sim status").message.find("ticks=3") !=
               std::string::npos, "hierarchical status");

    expect(i76_execute_command(game, "step \"3\"").code == i76_result_code::ok
            && game.state.tick == 6U, "quoted numeric argument");
    expect(i76_execute_command(game, "step \"unterminated").code ==
               i76_result_code::invalid_argument
                   && game.state.tick == 6U,
           "malformed quote prevents execution");
    expect(i76_execute_command(game, "sim step 2 --bad").code ==
               i76_result_code::invalid_argument
                   && game.state.tick == 6U,
           "unrecognized option rejected before execution");
    expect(i76_execute_command(game, "sim step -- 2").code ==
        i76_result_code::ok
            && game.state.tick == 8U, "option terminator");
    expect(i76_execute_command(game, "step -1").code ==
        i76_result_code::invalid_argument
            && game.state.tick == 8U, "legacy step validation retained");

    expect(i76_execute_command(game,
        "object spawn vehicle \"Test Vehicle\"").code ==
               i76_result_code::ok
                   && i76_execute_command(game,
                   "object list").message.find("Test Vehicle") !=
                   std::string::npos, "quoted world object name");
    expect(i76_execute_command(game, "object spawn vehicle Test Vehicle").code
        ==
               i76_result_code::invalid_argument,
                   "unquoted two-word name rejected");

    std::filesystem::remove_all(directory, error);
    error.clear();
    std::filesystem::create_directories(directory, error);
    expect(!error, "create directory with spaces");
    result = i76_execute_command(game, "resource mount \"" + directory.string()
        + "\"");
    expect(result.code == i76_result_code::ok, "quoted mount path with spaces");
    expect(i76_execute_command(game, "resource list").message.find("directory")
        !=
               std::string::npos, "directory listed");
    expect(i76_execute_command(game, "resource unmount 2").code ==
        i76_result_code::ok,
           "unmount with stable ID");
    expect(i76_runtime_shutdown(game) == i76_result_code::ok,
        "shutdown runtime");
    std::filesystem::remove_all(directory, error);
}

// -----------------------------------------------------------------------------
// Run the test cases and return a failure status when any assertion fails.
// -----------------------------------------------------------------------------
int main()
{
    test_lexer();
    test_console();
    return failures == 0U ? 0 : 1;
}
