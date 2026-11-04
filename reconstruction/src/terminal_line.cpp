#include "i76/line_editor.h"

#include <iostream>
#include <string>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <poll.h>
#include <termios.h>
#include <unistd.h>
#endif

// Only host-side terminal code touches OS console interfaces.
struct i76_native_terminal {
    bool enabled{};
#ifdef _WIN32
    HANDLE output_handle{};
    DWORD output_mode{};
#else
    termios original{};
#endif

    // -------------------------------------------------------------------------
    // Restore saved terminal mode when native input handling ends.
    // -------------------------------------------------------------------------
    ~i76_native_terminal() noexcept
    {
        if (!enabled) {
            return;
        }
#ifdef _WIN32
        SetConsoleMode(output_handle, output_mode);
#else
        tcsetattr(STDIN_FILENO, TCSANOW, &original);
#endif
    }
};

// -----------------------------------------------------------------------------
// Enable host terminal input and preserve its previous settings.
// -----------------------------------------------------------------------------
static bool enable_native_terminal(i76_native_terminal& terminal,
                                   std::istream& input,
                                   std::ostream& output) noexcept
{
    if (&input != &std::cin
        || &output != &std::cout) {
        return false;
    }
#ifdef _WIN32
    DWORD input_mode = 0;

    terminal.output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &input_mode)
        || !GetConsoleMode(terminal.output_handle, &terminal.output_mode)) {
        return false;
    }
    if (!SetConsoleMode(terminal.output_handle,
                        terminal.output_mode |
                        ENABLE_VIRTUAL_TERMINAL_PROCESSING)) {
        return false;
    }
#else
    termios raw = {};

    if (!isatty(STDIN_FILENO)
        || !isatty(STDOUT_FILENO)
        || tcgetattr(STDIN_FILENO, &terminal.original) != 0) {
        return false;
    }
    raw = terminal.original;
    raw.c_iflag &= static_cast<tcflag_t>(~(BRKINT | ICRNL | INPCK | ISTRIP |
        IXON));
    raw.c_lflag &= static_cast<tcflag_t>(~(ECHO | ICANON | IEXTEN | ISIG));
    raw.c_cflag |= CS8;
    raw.c_cc[VMIN] = 1;
    raw.c_cc[VTIME] = 0;
    if (tcsetattr(STDIN_FILENO, TCSANOW, &raw) != 0) {
        return false;
    }
#endif
    terminal.enabled = true;
    return true;
}

// -----------------------------------------------------------------------------
// Count visible UTF-8 code points in an editable terminal line.
// -----------------------------------------------------------------------------
static std::size_t visible_characters(std::string_view text) noexcept
{
    std::size_t index = 0;
    std::size_t count = 0;

    for (index = 0; index < text.size(); ++index) {
        if ((static_cast<std::uint8_t>(text[index]) & 0xC0U) != 0x80U) {
            ++count;
        }
    }
    return count;
}

// -----------------------------------------------------------------------------
// Redraw the current command and restore its visual cursor position.
// -----------------------------------------------------------------------------
static void redraw(std::ostream& output,
                   std::string_view prompt,
                   const i76_line_editor& editor)
{
    std::size_t back = 0;

    output << "\r\x1b[2K" << prompt << editor.line;
    back = visible_characters(
        std::string_view(editor.line).substr(editor.cursor));
    if (back != 0U) {
        output << "\x1b[" << back << 'D';
    }
    output << std::flush;
}

#ifndef _WIN32

// -----------------------------------------------------------------------------
// Read one input byte from the configured native terminal.
// -----------------------------------------------------------------------------
static int read_native_byte() noexcept
{
    unsigned char byte = 0;

    return read(STDIN_FILENO, &byte, 1) == 1 ? static_cast<int>(byte) : -1;
}

// -----------------------------------------------------------------------------
// Poll briefly for an optional continuation input byte.
// -----------------------------------------------------------------------------
static int read_optional_byte() noexcept
{
    pollfd descriptor = {};
    int ready = 0;

    descriptor.fd = STDIN_FILENO;
    descriptor.events = POLLIN;
    ready = poll(&descriptor, 1, 75);
    if (ready <= 0
        || (descriptor.revents & POLLIN) == 0) {
        return -1;
    }
    return read_native_byte();
}

// -----------------------------------------------------------------------------
// Translate terminal escape sequences into editor key actions.
// -----------------------------------------------------------------------------
static i76_line_key decode_escape(int& ordinary_byte) noexcept
{
    char sequence[12] = {};
    std::size_t length = 0;
    int next = -1;
    bool csi = false;

    ordinary_byte = -1;
    next = read_optional_byte();
    if (next != '['
        && next != 'O') {
        // ESC alone must not swallow the next normal keystroke
        ordinary_byte = next;
        return i76_line_key::insert;
    }
    csi = next == '[';
    while (length < sizeof(sequence)) {
        next = read_optional_byte();
        if (next < 0) {
            return i76_line_key::insert;
        }
        if (next >= '0'
            && next <= '9') {
            sequence[length++] = static_cast<char>(next);
            continue;
        }
        if (next == ';'
            && csi) {
            sequence[length++] = ';';
            continue;
        }
        if (next == 'A') return i76_line_key::up;
        if (next == 'B') return i76_line_key::down;
        if (next == 'C') return i76_line_key::right;
        if (next == 'D') return i76_line_key::left;
        if (next == 'H') return i76_line_key::home;
        if (next == 'F') return i76_line_key::end;
        if (next == '~'
            && csi) {
            if (length == 1U
                && sequence[0] == '3') return i76_line_key::remove;
            if (length == 1U
                && (sequence[0] == '1'
                || sequence[0] == '7')) {
                return i76_line_key::home;
            }
            if (length == 1U
                && (sequence[0] == '4'
                || sequence[0] == '8')) {
                return i76_line_key::end;
            }
        }
        break;
    }
    return i76_line_key::insert;
}
#endif

#ifdef _WIN32

// -----------------------------------------------------------------------------
// Read and validate a UTF-8 code point from terminal input.
// -----------------------------------------------------------------------------
static std::string utf8_codepoint(std::uint32_t code)
{
    std::string encoded = {};

    if (code <= 0x7FU) {
        encoded.push_back(static_cast<char>(code));
    } else if (code <= 0x7FFU) {
        encoded.push_back(static_cast<char>(0xC0U | (code >> 6)));
        encoded.push_back(static_cast<char>(0x80U | (code & 0x3FU)));
    } else if (code <= 0xFFFFU) {
        encoded.push_back(static_cast<char>(0xE0U | (code >> 12)));
        encoded.push_back(static_cast<char>(0x80U | ((code >> 6) & 0x3FU)));
        encoded.push_back(static_cast<char>(0x80U | (code & 0x3FU)));
    } else if (code <= 0x10FFFFU) {
        encoded.push_back(static_cast<char>(0xF0U | (code >> 18)));
        encoded.push_back(static_cast<char>(0x80U | ((code >> 12) & 0x3FU)));
        encoded.push_back(static_cast<char>(0x80U | ((code >> 6) & 0x3FU)));
        encoded.push_back(static_cast<char>(0x80U | (code & 0x3FU)));
    }
    return encoded;
}
#endif

// -----------------------------------------------------------------------------
// Read one editable terminal command using the shared line editor.
// -----------------------------------------------------------------------------
bool i76_terminal_read_line(std::istream& input,
                            std::ostream& output,
                            i76_line_editor& editor,
                            std::string_view prompt,
                            std::string& result)
{
    i76_native_terminal terminal = {};
    i76_line_key key = i76_line_key::insert;
    i76_line_action action = i76_line_action::none;
    std::string text = {};
    std::string pending = {};
    std::uint32_t pending_bytes = 0;
    std::uint32_t character = 0;
#ifndef _WIN32
    int ordinary_byte = -1;
#endif
#ifdef _WIN32
    std::uint32_t high_surrogate = 0;
#endif

    result.clear();
    i76_line_editor_reset(editor);
    if (!enable_native_terminal(terminal, input, output)) {
        output << prompt << std::flush;
        if (!std::getline(input, result)) {
            return false;
        }
        i76_line_editor_remember(editor, result);
        return true;
    }

    redraw(output, prompt, editor);
    while (true) {
        key = i76_line_key::insert;
        text.clear();
#ifdef _WIN32
        character = static_cast<std::uint32_t>(_getwch());
        if (character == 0U
            || character == 0xE0U) {
            character = static_cast<std::uint32_t>(_getwch());
            switch (character) {
            case 72U: key = i76_line_key::up; break;
            case 80U: key = i76_line_key::down; break;
            case 75U: key = i76_line_key::left; break;
            case 77U: key = i76_line_key::right; break;
            case 71U: key = i76_line_key::home; break;
            case 79U: key = i76_line_key::end; break;
            case 83U: key = i76_line_key::remove; break;
            default: break;
            }
            character = 0U;
        } else if (character >= 0xD800U
                   && character <= 0xDBFFU) {
            high_surrogate = character;
            continue;
        } else if (character >= 0xDC00U
                   && character <= 0xDFFFU) {
            if (high_surrogate == 0U) {
                continue; // skip an unmatched UTF-16 low surrogate
            }
            character = 0x10000U + ((high_surrogate - 0xD800U) << 10U) +
                        (character - 0xDC00U);
            high_surrogate = 0U;
        } else {
            high_surrogate = 0U;
        }
        if (character >= 0x80U
            && character <= 0x10FFFFU) {
            text = utf8_codepoint(character);
        }
#else
        character = static_cast<std::uint32_t>(read_native_byte());
        if (character == static_cast<std::uint32_t>(-1)) {
            output << "\n" << std::flush;
            return false;
        }
        if (pending_bytes != 0U) {
            if ((character & 0xC0U) == 0x80U) {
                pending.push_back(static_cast<char>(character));
                --pending_bytes;
                if (pending_bytes == 0U) {
                    text = pending;
                    pending.clear();
                } else {
                    continue;
                }
            } else {
                pending_bytes = 0U;
                pending.clear();
            }
        }
        if (text.empty()
            && character >= 0xC2U
            && character <= 0xF4U) {
            pending.clear();
            pending.push_back(static_cast<char>(character));
            pending_bytes = character <= 0xDFU ? 1U : character <= 0xEFU ? 2U :
                3U;
            continue;
        }
        if (character == 27U) {
            key = decode_escape(ordinary_byte);
            if (ordinary_byte >= 0) {
                character = static_cast<std::uint32_t>(ordinary_byte);
            }
        }
#endif
        if (character == 1U) key = i76_line_key::home;
        else if (character == 5U) key = i76_line_key::end;
        else if (character == 3U) key = i76_line_key::cancel;
        else if (character == 4U) key = i76_line_key::eof;
        else if (character == 127U
            || character == 8U) key =
            i76_line_key::backspace;
        else if (character == '\n'
            || character == '\r') key =
            i76_line_key::enter;
        else if (character >= 32U
                        && character <= 126U)
            text.push_back(static_cast<char>(character));

        if (key == i76_line_key::insert
            && text.empty()) {
            continue;
        }
        if (key == i76_line_key::enter) {
            result = editor.line;
        }
        action = i76_line_editor_apply(editor, key, text);
        if (action == i76_line_action::submitted) {
            output << "\n" << std::flush;
            return true;
        }
        if (action == i76_line_action::end_of_input) {
            output << "\n" << std::flush;
            return false;
        }
        if (action == i76_line_action::cancelled) {
            output << "\r\x1b[2K^C\n" << std::flush;
            redraw(output, prompt, editor);
        } else if (action == i76_line_action::changed) {
            redraw(output, prompt, editor);
        }
    }
}
