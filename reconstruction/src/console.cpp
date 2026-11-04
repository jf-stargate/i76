#include "i76/console.h"

#include <cstdint>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

// Internal compatibility boundary for existing, independently tested engine
// handlers.
i76_command_result i76_execute_legacy_command(i76_runtime& game,
    std::string_view line);

enum class i76_console_variable_kind : std::uint8_t {
    none = 0,
    boolean,
    uint32,
    uint64,
};

struct i76_console_definition {
    std::string_view name{};
    std::string_view usage{};
    std::string_view description{};
    std::uint8_t minimum{};
    std::uint8_t maximum{};
    bool tail_argument{};
    i76_console_variable_kind variable{};
    bool read_only{};
};

// One registry drives lookup, arity checks, discovery, help and completion.
// Existing engine handlers remain responsible for semantic validation and
// mutations.
static constexpr i76_console_definition definitions[] = {
    {"help", "help [command|namespace]",
        "Show registered commands and variables", 0, 64},
    {"find", "find <text>", "Search names and descriptions", 1, 1},
    {"status", "status", "Show runtime status (compatibility alias)", 0, 0},
    {"pause", "pause", "Pause real-time simulation (compatibility alias)", 0,
        0},
    {"resume", "resume", "Resume real-time simulation (compatibility alias)", 0,
        0},
    {"step", "step <count>", "Advance a fixed number of simulation ticks", 1,
        1},
    {"quit", "quit", "Request application exit", 0, 0},
    {"sim", "sim <action>", "Simulation command namespace", 0, 64},
    {"sim help", "sim help", "List simulation commands", 0, 0},
    {"sim status", "sim status", "Show runtime status", 0, 0},
    {"sim pause", "sim pause", "Pause real-time simulation", 0, 0},
    {"sim resume", "sim resume", "Resume real-time simulation", 0, 0},
    {"sim step", "sim step <count>",
        "Advance a fixed number of simulation ticks", 1, 1},
    {"object", "object <action>", "World object command namespace", 0, 64},
    {"object help", "object help", "List object commands", 0, 0},
    {"object list", "object list", "List world objects", 0, 0},
    {"object inspect", "object inspect <slot:generation>",
        "Inspect a world object", 1, 1},
    {"object spawn", "object spawn <type> <name>",
        "Create a debug world object", 2, 2},
    {"object destroy", "object destroy <slot:generation>",
        "Destroy a world object", 1, 1},
    {"object clear", "object clear", "Destroy all world objects", 0, 0},
    {"resource", "resource <action>", "Resource provider command namespace", 0,
        64},
    {"resource help", "resource help", "List resource commands", 0, 0},
    {"resource list", "resource list", "List stable resource mount IDs", 0, 0},
    {"resource mounts", "resource mounts", "Alias for resource list", 0, 0},
    {"resource cache", "resource cache", "Show leased resource cache entries",
        0, 0},
    {"resource mount", "resource mount <directory>",
        "Mount a directory provider", 1, 64, true},
    {"resource unmount", "resource unmount <id|name>",
        "Unmount an idle provider", 1, 64, true},
    {"asset", "asset <action>", "Asset command namespace", 0, 64},
    {"asset stats", "asset stats", "Show asset cache statistics", 0, 0},
    {"level", "level <action>", "Level lifecycle command namespace", 0, 64},
    {"level help", "level help", "List level commands", 0, 0},
    {"level inspect", "level inspect <name>",
        "Inspect a synthetic level or BWD2 inventory", 1, 64, true},
    {"level sections", "level sections <name>", "Inspect BWD2 chunk structure",
        1, 64, true},
    {"level summary", "level summary <mission>",
        "Decode read-only retail section metadata", 1, 64, true},
    {"level terrain", "level terrain <mission>",
        "Validate ZMAP/ZONE and packed TER sidecar", 1, 64, true},
    {"level dependencies", "level dependencies <mission>",
        "Inspect known retail resource dependencies", 1, 64, true},
    {"level prepare", "level prepare <name>", "Prepare a synthetic level", 1,
        64, true},
    {"level activate", "level activate", "Activate the prepared level", 0, 0},
    {"level load", "level load <name>",
        "Prepare and activate a synthetic level", 1, 64, true},
    {"level discard", "level discard", "Discard a prepared level", 0, 0},
    {"level unload", "level unload", "Unload the active level", 0, 0},
    {"level status", "level status", "Show prepared and active levels", 0, 0},
    {"sim.paused", "sim.paused [true|false]",
        "Real-time simulation pause state",
     0, 1, false, i76_console_variable_kind::boolean, false},
    {"sim.tick_rate", "sim.tick_rate", "Configured fixed-step tick rate",
     0, 0, false, i76_console_variable_kind::uint32, true},
    {"sim.tick", "sim.tick", "Current fixed-step tick count",
     0, 0, false, i76_console_variable_kind::uint64, true},
    {"world.objects", "world.objects", "Current world object count",
     0, 0, false, i76_console_variable_kind::uint64, true},
};

// -----------------------------------------------------------------------------
// Identify whitespace characters permitted by the console tokenizer.
// -----------------------------------------------------------------------------
static bool whitespace(char c) noexcept
{
    return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

// -----------------------------------------------------------------------------
// Emit a console diagnostic and return a typed command result.
// -----------------------------------------------------------------------------
static i76_command_result console_reply(i76_runtime& game,
                                        i76_result_code code,
                                        std::string message)
{
    i76_command_result reply = {};
    reply.code = code;
    reply.message = std::move(message);
    i76_runtime_emit_diagnostic(game, code == i76_result_code::ok ?
                                i76_diagnostic_level::info :
                                i76_diagnostic_level::error,
                                reply.message);
    return reply;
}

// -----------------------------------------------------------------------------
// Tokenize quoted and unquoted developer-console arguments.
// -----------------------------------------------------------------------------
i76_console_tokens i76_console_tokenize(std::string_view line)
{
    constexpr std::size_t maximum_line = 4096U;
    constexpr std::size_t maximum_tokens = 64U;
    i76_console_tokens result = {};
    std::string token = {};
    bool quoted = false;
    bool started = false;

    if (line.size() > maximum_line) {
        result.error = "command exceeds 4096 bytes";
        return result;
    }
    for (std::size_t index = 0; index < line.size(); ++index) {
        const char c = line[index];
        if (c == '\0' || (static_cast<unsigned char>(c) < 32U &&
            !whitespace(c))) {
            result.error = "invalid control character in command";
            result.values.clear();
            return result;
        }
        if (quoted && c == '\\' && index + 1U < line.size() &&
            (line[index + 1U] == '"' || line[index + 1U] == '\\')) {
            token += line[++index];
            continue;
        }
        if (c == '"') {
            quoted = !quoted;
            started = true;
            continue;
        }
        if (!quoted && whitespace(c)) {
            if (started) {
                if (result.values.size() == maximum_tokens) {
                    result.error = "too many command tokens";
                    result.values.clear();
                    return result;
                }
                result.values.push_back(std::move(token));
                token.clear();
                started = false;
            }
            continue;
        }
        token += c;
        started = true;
    }
    if (quoted) {
        result.values.clear();
        result.error = "unterminated quoted string";
        return result;
    }
    if (started) {
        if (result.values.size() == maximum_tokens) {
            result.values.clear();
            result.error = "too many command tokens";
            return result;
        }
        result.values.push_back(std::move(token));
    }
    return result;
}

// -----------------------------------------------------------------------------
// Check whether a token sequence matches a registered console name.
// -----------------------------------------------------------------------------
static bool matches_name(const i76_console_definition& definition,
                         const std::vector<std::string>& values,
                         std::size_t& consumed)
{
    std::size_t start = 0U;
    std::size_t part = 0U;
    std::size_t boundary = 0U;

    while (start < definition.name.size()) {
        boundary = definition.name.find(' ', start);
        if (boundary == std::string_view::npos) {
            boundary = definition.name.size();
        }
        if (part >= values.size() ||
            definition.name.substr(start, boundary - start) != values[part]) {
            return false;
        }
        ++part;
        start = boundary + 1U;
    }
    consumed = part;
    return true;
}

// -----------------------------------------------------------------------------
// Find the longest matching registered command or variable definition.
// -----------------------------------------------------------------------------
static const i76_console_definition* lookup(const std::vector<std::string>&
    values,
    std::size_t& consumed)
{
    const i76_console_definition* selected = nullptr;
    std::size_t selected_count = 0U;
    std::size_t candidate_count = 0U;

    for (const i76_console_definition& definition : definitions) {
        if (matches_name(definition, values, candidate_count) &&
            candidate_count > selected_count) {
            selected = &definition;
            selected_count = candidate_count;
        }
    }
    consumed = selected_count;
    return selected;
}

// -----------------------------------------------------------------------------
// Build command help from the shared registry metadata.
// -----------------------------------------------------------------------------
static std::string show_help(std::string_view topic)
{
    std::string message = {};
    bool found = false;

    for (const i76_console_definition& definition : definitions) {
        if (definition.name == topic && !topic.empty() &&
            topic != "sim" && topic != "resource" && topic != "level" &&
            topic != "object" && topic != "asset") {
            return std::string(definition.usage) + "\n" +
                std::string(definition.description) +
                   (definition.variable != i76_console_variable_kind::none ?
                       (definition.read_only ? "\nRead-only console variable" :
                                               "\nWritable console variable") :
                                               "");
        }
    }
    message = topic.empty() ? "commands and variables:" :
                              std::string(topic) + " commands and variables:";
    for (const i76_console_definition& definition : definitions) {
        if (definition.name == topic || topic.empty() ||
            (definition.name.size() > topic.size() &&
             definition.name.starts_with(topic) && definition.name[topic.size()]
                 == ' ')) {
            message += "\n  " + std::string(definition.usage);
            found = true;
        }
    }
    return found ? message : "unknown help topic: " + std::string(topic);
}

// -----------------------------------------------------------------------------
// Search registered console names and descriptions for matching text.
// -----------------------------------------------------------------------------
static std::string find_entries(std::string_view search)
{
    std::string result = "matches for " + std::string(search) + ":";
    std::size_t count = 0U;

    for (const i76_console_definition& definition : definitions) {
        if (definition.name.find(search) != std::string_view::npos ||
            definition.description.find(search) != std::string_view::npos) {
            result += "\n  " + std::string(definition.name) + " - " +
                      std::string(definition.description);
            ++count;
        }
    }
    return count == 0U ? "no matching console entries" : result;
}

// -----------------------------------------------------------------------------
// Read or update a supported typed console variable.
// -----------------------------------------------------------------------------
static i76_command_result variable_execute(i76_runtime& game,
                                     const i76_console_definition& definition,
                                     const std::vector<std::string>& args)
{
    std::string value = {};

    if (!args.empty() && definition.read_only) {
        return console_reply(game, i76_result_code::invalid_argument,
                             std::string(definition.name) + " is read-only");
    }
    if (!args.empty()) {
        if (definition.name == "sim.paused") {
            if (args[0] != "true" && args[0] != "false" &&
                args[0] != "1" && args[0] != "0") {
                return console_reply(game, i76_result_code::invalid_argument,
                                     "sim.paused expects true, false, 1 or 0");
            }
            i76_runtime_set_paused(game, args[0] == "true" || args[0] == "1");
        }
    }
    if (definition.name == "sim.paused") {
        value = game.state.paused ? "true" : "false";
    } else if (definition.name == "sim.tick_rate") {
        value = std::to_string(game.state.tick_rate);
    } else if (definition.name == "sim.tick") {
        value = std::to_string(game.state.tick);
    } else if (definition.name == "world.objects") {
        value = std::to_string(i76_world_count(game.world));
    }
    return console_reply(game, i76_result_code::ok,
                         std::string(definition.name) + "=" + value);
}

// -----------------------------------------------------------------------------
// List registered names matching the supplied command prefix.
// -----------------------------------------------------------------------------
std::vector<std::string> i76_console_complete(std::string_view prefix)
{
    std::vector<std::string> matches = {};
    for (const i76_console_definition& definition : definitions) {
        if (definition.name.starts_with(prefix)) {
            matches.emplace_back(definition.name);
        }
    }
    return matches;
}

// -----------------------------------------------------------------------------
// Validate a console request and dispatch its registered handler.
// -----------------------------------------------------------------------------
i76_command_result i76_console_execute(i76_runtime& game, std::string_view line)
{
    i76_console_tokens parsed = {};
    const i76_console_definition* definition = nullptr;
    std::size_t consumed = 0U;
    std::vector<std::string> args = {};
    std::string forward = {};
    std::string topic = {};
    bool after_separator = false;

    if (!game.state.initialized) {
        return {i76_result_code::not_initialized, "runtime is not initialized"};
    }
    parsed = i76_console_tokenize(line);
    if (!parsed.error.empty()) {
        return console_reply(game, i76_result_code::invalid_argument,
            parsed.error);
    }
    if (parsed.values.empty()) {
        return console_reply(game, i76_result_code::invalid_argument,
            "empty command");
    }
    definition = lookup(parsed.values, consumed);
    if (definition == nullptr) {
        return console_reply(game, i76_result_code::unknown_command,
                             "unknown command: " + parsed.values[0]);
    }
    for (std::size_t index = consumed; index < parsed.values.size(); ++index) {
        if (!after_separator && parsed.values[index] == "--") {
            after_separator = true;
            continue;
        }
        if (!after_separator && parsed.values[index].starts_with("--")) {
            return console_reply(game, i76_result_code::invalid_argument,
                                 "unknown option: " + parsed.values[index]);
        }
        args.push_back(parsed.values[index]);
    }
    if (definition->name == "help") {
        for (const std::string& item : args) {
            if (!topic.empty()) {
                topic += ' ';
            }
            topic += item;
        }
        const std::string message = show_help(topic);
        return console_reply(game, message.starts_with("unknown help topic:") ?
                             i76_result_code::invalid_argument :
                             i76_result_code::ok, message);
    }
    if (definition->name == "find") {
        if (args.size() != 1U) {
            return console_reply(game, i76_result_code::invalid_argument,
                                 "usage: find <text>");
        }
        return console_reply(game, i76_result_code::ok, find_entries(args[0]));
    }
    if (definition->variable != i76_console_variable_kind::none &&
        args.size() == 1U && args[0] == "?") {
        return console_reply(game, i76_result_code::ok,
            show_help(definition->name));
    }
    if (args.size() < definition->minimum || args.size() > definition->maximum)
        {
        return console_reply(game, i76_result_code::invalid_argument,
                             "usage: " + std::string(definition->usage));
    }
    if (definition->name == "sim" && !args.empty()) {
        return console_reply(game, i76_result_code::unknown_command,
                             "unknown simulation action (help sim)");
    }
    if (definition->name == "sim" || definition->name == "sim help" ||
        definition->name == "resource help" || definition->name == "level help"
            ||
        definition->name == "object help") {
        const std::string_view topic_name = definition->name == "sim" ||
                                             definition->name == "sim help" ?
                                             "sim" :
                                             definition->name == "resource help"
                                             ? "resource" :
                                             definition->name == "level help" ?
                                             "level" : "object";
        return console_reply(game, i76_result_code::ok, show_help(topic_name));
    }
    if (definition->variable != i76_console_variable_kind::none) {
        return variable_execute(game, *definition, args);
    }
    forward = std::string(definition->name);
    if (forward.starts_with("sim ")) {
        forward.erase(0U, 4U);
    }
    for (const std::string& arg : args) {
        forward += ' ';
        forward += arg;
    }
    return i76_execute_legacy_command(game, forward);
}
