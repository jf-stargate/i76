#include "i76/line_editor.h"

#include <utility>

static std::size_t previous_character(std::string_view text, std::size_t cursor) noexcept
{
    if (cursor == 0U) {
        return 0U;
    }
    --cursor;
    while (cursor != 0U && (static_cast<std::uint8_t>(text[cursor]) & 0xC0U) == 0x80U) {
        --cursor;
    }
    return cursor;
}

static std::size_t next_character(std::string_view text, std::size_t cursor) noexcept
{
    if (cursor >= text.size()) {
        return text.size();
    }
    ++cursor;
    while (cursor < text.size() &&
           (static_cast<std::uint8_t>(text[cursor]) & 0xC0U) == 0x80U) {
        ++cursor;
    }
    return cursor;
}

void i76_line_editor_reset(i76_line_editor& editor) noexcept
{
    editor.line.clear();
    editor.cursor = 0U;
    editor.draft.clear();
    editor.history_index = editor.history.size();
}

void i76_line_editor_remember(i76_line_editor& editor, std::string_view command)
{
    if (command.empty() || command.size() > i76_line_max_bytes) {
        return;
    }
    if (!editor.history.empty() && editor.history.back() == command) {
        return;
    }
    if (editor.history.size() >= i76_line_max_history) {
        editor.history.erase(editor.history.begin());
    }
    editor.history.emplace_back(command);
    editor.history_index = editor.history.size();
}

i76_line_action i76_line_editor_apply(i76_line_editor& editor, i76_line_key key,
                                       std::string_view text)
{
    std::size_t next = 0;

    switch (key) {
    case i76_line_key::insert:
        if (text.empty() || text.size() > i76_line_max_bytes - editor.line.size()) {
            return i76_line_action::none;
        }
        editor.line.insert(editor.cursor, text);
        editor.cursor += text.size();
        return i76_line_action::changed;
    case i76_line_key::left:
        next = previous_character(editor.line, editor.cursor);
        if (next == editor.cursor) {
            return i76_line_action::none;
        }
        editor.cursor = next;
        return i76_line_action::changed;
    case i76_line_key::right:
        next = next_character(editor.line, editor.cursor);
        if (next == editor.cursor) {
            return i76_line_action::none;
        }
        editor.cursor = next;
        return i76_line_action::changed;
    case i76_line_key::home:
        if (editor.cursor == 0U) {
            return i76_line_action::none;
        }
        editor.cursor = 0U;
        return i76_line_action::changed;
    case i76_line_key::end:
        if (editor.cursor == editor.line.size()) {
            return i76_line_action::none;
        }
        editor.cursor = editor.line.size();
        return i76_line_action::changed;
    case i76_line_key::backspace:
        next = previous_character(editor.line, editor.cursor);
        if (next == editor.cursor) {
            return i76_line_action::none;
        }
        editor.line.erase(next, editor.cursor - next);
        editor.cursor = next;
        return i76_line_action::changed;
    case i76_line_key::remove:
        next = next_character(editor.line, editor.cursor);
        if (next == editor.cursor) {
            return i76_line_action::none;
        }
        editor.line.erase(editor.cursor, next - editor.cursor);
        return i76_line_action::changed;
    case i76_line_key::up:
        if (editor.history.empty() || editor.history_index == 0U) {
            return i76_line_action::none;
        }
        if (editor.history_index == editor.history.size()) {
            editor.draft = editor.line;
        }
        --editor.history_index;
        editor.line = editor.history[editor.history_index];
        editor.cursor = editor.line.size();
        return i76_line_action::changed;
    case i76_line_key::down:
        if (editor.history_index >= editor.history.size()) {
            return i76_line_action::none;
        }
        ++editor.history_index;
        editor.line = editor.history_index == editor.history.size() ?
                          editor.draft : editor.history[editor.history_index];
        editor.cursor = editor.line.size();
        return i76_line_action::changed;
    case i76_line_key::enter:
        i76_line_editor_remember(editor, editor.line);
        // The caller captures editor.line before calling enter.
        return i76_line_action::submitted;
    case i76_line_key::cancel:
        i76_line_editor_reset(editor);
        return i76_line_action::cancelled;
    case i76_line_key::eof:
        if (editor.line.empty()) {
            return i76_line_action::end_of_input;
        }
        return i76_line_editor_apply(editor, i76_line_key::remove);
    }
    return i76_line_action::none;
}
