#include "i76/line_editor.h"

#include <cstdint>
#include <iostream>
#include <string>

static std::uint32_t failures = 0;

// -----------------------------------------------------------------------------
// Record a test failure when an assertion does not hold.
// -----------------------------------------------------------------------------
static void expect(bool condition, const char* label)
{
    if (!condition) {
        std::cerr << "FAIL: " << label << '\n';
        ++failures;
    }
}

// -----------------------------------------------------------------------------
// Verify editing behavior and error cases.
// -----------------------------------------------------------------------------
static void test_editing()
{
    i76_line_editor editor = {};

    expect(editor.line.empty()
           && editor.cursor == 0U
           && editor.history.empty(),
           "all editor state is initially empty");
    expect(i76_line_editor_apply(editor, i76_line_key::left) ==
        i76_line_action::none,
           "left boundary");
    expect(i76_line_editor_apply(editor, i76_line_key::insert, "staus") ==
               i76_line_action::changed
                   && editor.cursor == 5U,
                   "insert at end");
    i76_line_editor_apply(editor, i76_line_key::left);
    i76_line_editor_apply(editor, i76_line_key::left);
    expect(editor.cursor == 3U, "cursor moves within string");
    i76_line_editor_apply(editor, i76_line_key::insert, "t");
    expect(editor.line == "status"
           && editor.cursor == 4U, "insert in middle");
    expect(i76_line_editor_apply(editor, i76_line_key::home) ==
        i76_line_action::changed
            && editor.cursor == 0U, "home jumps to beginning");
    expect(i76_line_editor_apply(editor, i76_line_key::backspace) ==
        i76_line_action::none,
           "backspace start is safe");
    expect(i76_line_editor_apply(editor, i76_line_key::end) ==
        i76_line_action::changed
            && editor.cursor == editor.line.size(), "end jumps to end");
    expect(i76_line_editor_apply(editor, i76_line_key::right) ==
        i76_line_action::none,
           "right boundary");
    i76_line_editor_apply(editor, i76_line_key::left);
    i76_line_editor_apply(editor, i76_line_key::remove);
    expect(editor.line == "statu"
           && editor.cursor == 5U, "delete at cursor");
    i76_line_editor_apply(editor, i76_line_key::backspace);
    expect(editor.line == "stat"
           && editor.cursor == 4U,
        "backspace before cursor");
    i76_line_editor_apply(editor, i76_line_key::insert, "us");
    expect(editor.line == "status", "repair end-of-line");
    expect(i76_line_editor_apply(editor, i76_line_key::enter) ==
        i76_line_action::submitted
            && editor.history.size() == 1U
            && editor.history.front() ==
                   "status",
           "enter submits and remembers command");
    i76_line_editor_reset(editor);
    expect(editor.line.empty()
           && editor.history.size() == 1U,
           "reset clears edit buffer but keeps history");
}

// -----------------------------------------------------------------------------
// Verify history behavior and error cases.
// -----------------------------------------------------------------------------
static void test_history()
{
    i76_line_editor editor = {};
    std::uint32_t index = 0;

    i76_line_editor_remember(editor, "step 1");
    i76_line_editor_remember(editor, "step 1");
    i76_line_editor_remember(editor, "status");
    i76_line_editor_remember(editor, "");
    expect(editor.history.size() == 2U,
        "ignore empty and consecutive duplicates");
    i76_line_editor_apply(editor, i76_line_key::insert, "st");
    i76_line_editor_apply(editor, i76_line_key::up);
    expect(editor.line == "status", "up gives newest command");
    i76_line_editor_apply(editor, i76_line_key::up);
    expect(editor.line == "step 1", "up gives older command");
    expect(i76_line_editor_apply(editor, i76_line_key::up) ==
        i76_line_action::none,
           "history beginning bounded");
    i76_line_editor_apply(editor, i76_line_key::down);
    expect(editor.line == "status", "down advances history");
    i76_line_editor_apply(editor, i76_line_key::down);
    expect(editor.line == "st"
           && editor.cursor == 2U,
        "down restores unfinished draft");
    expect(i76_line_editor_apply(editor, i76_line_key::down) ==
        i76_line_action::none,
           "history end bounded");
    i76_line_editor_apply(editor, i76_line_key::up);
    i76_line_editor_apply(editor, i76_line_key::backspace);
    expect(editor.history.back() == "status",
        "editing recalled command does not mutate history");
    i76_line_editor_apply(editor, i76_line_key::cancel);
    expect(editor.line.empty()
           && editor.history.size() == 2U,
           "cancel restores empty draft and retains history");

    for (index = 0; index < 140U; ++index) {
        i76_line_editor_remember(editor, std::to_string(index));
    }
    expect(editor.history.size() == i76_line_max_history
           && editor.history.front() == "12"
           && editor.history.back() == "139",
                   "history bounded with oldest entry evicted");
    i76_line_editor_reset(editor);
    i76_line_editor_apply(editor, i76_line_key::up);
    expect(editor.line == "139", "history works after eviction");
}

// -----------------------------------------------------------------------------
// Verify size and utf8 behavior and error cases.
// -----------------------------------------------------------------------------
static void test_size_and_utf8()
{
    i76_line_editor editor = {};
    std::string wide = "a\xC3\xA9\xE6\xBC\xA2"; // a, e-acute, Han

    expect(i76_line_editor_apply(editor, i76_line_key::insert, wide) ==
               i76_line_action::changed
                   && editor.cursor == 6U,
                   "UTF-8 inserted as bytes");
    i76_line_editor_apply(editor, i76_line_key::left);
    expect(editor.cursor == 3U, "left crosses entire three-byte code point");
    i76_line_editor_apply(editor, i76_line_key::left);
    expect(editor.cursor == 1U, "left crosses entire two-byte code point");
    i76_line_editor_apply(editor, i76_line_key::right);
    expect(editor.cursor == 3U, "right crosses UTF-8 code point");
    i76_line_editor_apply(editor, i76_line_key::remove);
    expect(editor.line == "a\xC3\xA9", "delete removes one UTF-8 code point");
    i76_line_editor_apply(editor, i76_line_key::backspace);
    expect(editor.line == "a"
           && editor.cursor == 1U,
           "backspace removes complete UTF-8 code point");
    i76_line_editor_apply(editor, i76_line_key::cancel);
    expect(i76_line_editor_apply(editor, i76_line_key::eof) ==
        i76_line_action::end_of_input,
           "control-D on empty buffer returns EOF");
    i76_line_editor_apply(editor, i76_line_key::insert, "abc");
    i76_line_editor_apply(editor, i76_line_key::home);
    expect(i76_line_editor_apply(editor, i76_line_key::eof) ==
        i76_line_action::changed
            && editor.line == "bc",
                   "control-D deletes at cursor if line not empty");
    i76_line_editor_apply(editor, i76_line_key::cancel);
    expect(i76_line_editor_apply(editor, i76_line_key::insert,
                                  std::string(i76_line_max_bytes, 'x')) ==
               i76_line_action::changed, "maximum permitted line accepted");
    expect(i76_line_editor_apply(editor, i76_line_key::insert, "y") ==
               i76_line_action::none
                   && editor.line.size() ==
                   i76_line_max_bytes,
           "overlong insertion safely ignored");
    expect(i76_line_editor_apply(editor, i76_line_key::enter) ==
        i76_line_action::submitted,
           "max-length line may be submitted");
    expect(editor.history.size() == 1U, "max-length command history accepted");
    i76_line_editor_reset(editor);
    expect(editor.cursor == 0U
           && editor.line.empty(), "post-submit reset");
}

// -----------------------------------------------------------------------------
// Run the test cases and return a failure status when any assertion fails.
// -----------------------------------------------------------------------------
int main()
{
    test_editing();
    test_history();
    test_size_and_utf8();
    return failures == 0U ? 0 : 1;
}
