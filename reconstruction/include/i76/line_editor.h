#pragma once

#include <cstddef>
#include <cstdint>
#include <iosfwd>
#include <string>
#include <string_view>
#include <vector>

// The editable buffer and command history have no terminal/OS dependency.
enum class i76_line_key : std::uint8_t {
    insert = 0,
    left,
    right,
    up,
    down,
    home,
    end,
    backspace,
    remove,
    enter,
    cancel,
    eof,
};

enum class i76_line_action : std::uint8_t {
    none = 0,
    changed,
    submitted,
    cancelled,
    end_of_input,
};

struct i76_line_editor {
    std::string line{};
    std::size_t cursor{}; // byte offset at a UTF-8 boundary
    std::vector<std::string> history{};
    std::size_t history_index{}; // history.size() denotes the draft
    std::string draft{};
};

inline constexpr std::size_t i76_line_max_bytes = 4096U;
inline constexpr std::size_t i76_line_max_history = 128U;

void i76_line_editor_reset(i76_line_editor& editor) noexcept;
void i76_line_editor_remember(i76_line_editor& editor,
                              std::string_view command);
i76_line_action i76_line_editor_apply(i76_line_editor& editor,
                                      i76_line_key key,
                                      std::string_view text = {});

// This adapter uses native character-at-a-time input only for the real console.
// Piped input and injected test streams retain ordinary std::getline semantics.
bool i76_terminal_read_line(std::istream& input,
                            std::ostream& output,
                            i76_line_editor& editor,
                            std::string_view prompt,
                            std::string& result);
