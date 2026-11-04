#include "i76/command.h"

#include <charconv>
#include <cstdint>
#include <system_error>
#include <utility>

static std::string_view trim(std::string_view input) noexcept
{
    std::size_t start = 0;
    std::size_t end = 0;

    start = input.find_first_not_of(" \t\r\n");
    if (start == std::string_view::npos) {
        return {};
    }
    end = input.find_last_not_of(" \t\r\n");
    return input.substr(start, end - start + 1U);
}

static std::string_view take_token(std::string_view& input) noexcept
{
    std::size_t boundary = 0;
    std::string_view token = {};

    input = trim(input);
    boundary = input.find_first_of(" \t");
    token = input.substr(0, boundary);
    if (boundary == std::string_view::npos) {
        input = {};
    } else {
        input = trim(input.substr(boundary));
    }
    return token;
}

static i76_command_result make_reply(i76_runtime& game, i76_result_code code, std::string message)
{
    i76_command_result reply = {};
    i76_diagnostic_level level = i76_diagnostic_level::error;

    reply.code = code;
    reply.message = std::move(message);
    if (code == i76_result_code::ok) {
        level = i76_diagnostic_level::info;
    }
    i76_runtime_emit_diagnostic(game, level, reply.message);
    return reply;
}

static i76_world_kind parse_kind(std::string_view text) noexcept
{
    if (text == "vehicle") {
        return i76_world_kind::vehicle;
    }
    if (text == "scenery") {
        return i76_world_kind::scenery;
    }
    if (text == "marker") {
        return i76_world_kind::marker;
    }
    return i76_world_kind::none;
}

static const char* kind_name(i76_world_kind kind) noexcept
{
    switch (kind) {
    case i76_world_kind::vehicle:
        return "vehicle";
    case i76_world_kind::scenery:
        return "scenery";
    case i76_world_kind::marker:
        return "marker";
    case i76_world_kind::none:
        break;
    }
    return "unknown";
}

static std::string handle_text(i76_world_handle handle)
{
    return std::to_string(handle.slot) + ":" + std::to_string(handle.generation);
}

static bool parse_handle(std::string_view text, i76_world_handle& handle) noexcept
{
    std::size_t separator = 0;
    const char* begin = nullptr;
    const char* end = nullptr;
    std::from_chars_result parsed = {};
    i76_world_handle candidate = {};

    handle = {};
    separator = text.find(':');
    if (separator == std::string_view::npos || separator == 0U ||
        separator == text.size() - 1U) {
        return false;
    }
    begin = text.data();
    end = begin + separator;
    parsed = std::from_chars(begin, end, candidate.slot, 10);
    if (parsed.ec != std::errc{} || parsed.ptr != end || candidate.slot == 0U) {
        return false;
    }
    begin = end + 1;
    end = text.data() + text.size();
    parsed = std::from_chars(begin, end, candidate.generation, 10);
    if (parsed.ec != std::errc{} || parsed.ptr != end || candidate.generation == 0U) {
        return false;
    }
    handle = candidate;
    return true;
}

static i76_command_result execute_object_command(i76_runtime& game, std::string_view args)
{
    constexpr std::size_t k_list_limit = 32U;
    std::string_view verb = {};
    std::string_view kind_text = {};
    std::string_view name = {};
    i76_world_handle handle = {};
    i76_world_kind kind = i76_world_kind::none;
    i76_world_result status = i76_world_result::ok;
    const i76_world_object* object = nullptr;
    std::string message = {};
    std::size_t index = 0;
    std::size_t count = 0;

    verb = take_token(args);
    if ((verb.empty() || verb == "help") && args.empty()) {
        return make_reply(game, i76_result_code::ok,
                          "object commands: object list | spawn <vehicle|scenery|marker> <name> | "
                          "inspect <slot:generation> | destroy <slot:generation> | clear");
    }
    if (verb == "list" && args.empty()) {
        count = i76_world_count(game.world);
        message = "objects=" + std::to_string(count);
        for (index = 0; index < count && index < k_list_limit; ++index) {
            handle = i76_world_handle_at(game.world, index);
            object = i76_world_lookup(game.world, handle);
            if (object != nullptr) {
                message += "\n  " + handle_text(handle) + " " + kind_name(object->kind) +
                           " " + object->name;
            }
        }
        if (count > k_list_limit) {
            message += "\n  ... " + std::to_string(count - k_list_limit) +
                       " more (use object inspect <slot:generation>)";
        }
        return make_reply(game, i76_result_code::ok, std::move(message));
    }
    if (verb == "spawn") {
        kind_text = take_token(args);
        name = take_token(args);
        kind = parse_kind(kind_text);
        if (kind == i76_world_kind::none || name.empty() || !args.empty()) {
            return make_reply(game, i76_result_code::invalid_argument,
                              "usage: object spawn <vehicle|scenery|marker> <name>");
        }
        status = i76_world_create(game.world, kind, name, handle);
        if (status == i76_world_result::invalid_argument) {
            return make_reply(game, i76_result_code::invalid_argument, "invalid object name");
        }
        if (status != i76_world_result::ok) {
            return make_reply(game, i76_result_code::overflow, "object capacity exceeded");
        }
        return make_reply(game, i76_result_code::ok,
                          "spawned " + std::string(kind_name(kind)) + " " + std::string(name) +
                              " handle=" + handle_text(handle));
    }
    if (verb == "inspect" || verb == "destroy") {
        name = take_token(args);
        if (!args.empty() || !parse_handle(name, handle)) {
            return make_reply(game, i76_result_code::invalid_argument,
                              "expected object handle <slot:generation>");
        }
        object = i76_world_lookup(game.world, handle);
        if (object == nullptr) {
            return make_reply(game, i76_result_code::not_found, "object handle not found");
        }
        if (verb == "destroy") {
            status = i76_world_destroy(game.world, handle);
            if (status != i76_world_result::ok) {
                return make_reply(game, i76_result_code::not_found, "object handle not found");
            }
            return make_reply(game, i76_result_code::ok,
                              "destroyed object handle=" + handle_text(handle));
        }
        message = "object handle=" + handle_text(handle) + " kind=" + kind_name(object->kind) +
                  " name=" + object->name + " position=(" +
                  std::to_string(object->position.x) + "," +
                  std::to_string(object->position.y) + "," +
                  std::to_string(object->position.z) + ")";
        return make_reply(game, i76_result_code::ok, std::move(message));
    }
    if (verb == "clear" && args.empty()) {
        i76_world_clear(game.world);
        return make_reply(game, i76_result_code::ok, "world objects cleared");
    }
    return make_reply(game, i76_result_code::invalid_argument, "invalid object command (object help)");
}

static const char* resource_result_name(i76_resource_result result) noexcept
{
    switch (result) {
    case i76_resource_result::ok: return "ok";
    case i76_resource_result::already_initialized: return "already initialized";
    case i76_resource_result::not_initialized: return "not initialized";
    case i76_resource_result::invalid_argument: return "invalid resource path or name";
    case i76_resource_result::not_found: return "not found";
    case i76_resource_result::busy: return "resource still retained";
    case i76_resource_result::too_large: return "resource exceeds size limit";
    case i76_resource_result::io_error: return "resource I/O failure";
    case i76_resource_result::capacity_exceeded: return "resource capacity exceeded";
    }
    return "unknown resource error";
}

static const char* level_result_name(i76_level_result result) noexcept
{
    switch (result) {
    case i76_level_result::ok: return "ok";
    case i76_level_result::invalid_argument: return "invalid level name";
    case i76_level_result::not_initialized: return "level runtime is not initialized";
    case i76_level_result::busy: return "prepared level already exists (level discard first)";
    case i76_level_result::not_found: return "level or asset not found";
    case i76_level_result::invalid_data: return "invalid level data or asset read";
    case i76_level_result::capacity_exceeded: return "level capacity exceeded";
    case i76_level_result::not_prepared: return "no prepared level";
    case i76_level_result::not_loaded: return "no loaded level";
    case i76_level_result::activation_failed: return "unable to instantiate level objects";
    }
    return "unknown level error";
}

static i76_command_result execute_resource_command(i76_runtime& game, std::string_view args)
{
    std::string_view verb = {};
    i76_resource_result code = i76_resource_result::ok;
    std::string message = {};
    std::size_t index = 0;

    verb = take_token(args);
    if (verb == "help" && args.empty()) {
        return make_reply(game, i76_result_code::ok,
                          "resource commands: resource list | mount <directory>");
    }
    if (verb == "list" && args.empty()) {
        message = "resource mounts=" + std::to_string(game.resources.mounts.size());
        for (index = 0; index < game.resources.mounts.size(); ++index) {
            message += "\n  " + game.resources.mounts[index].name;
            message += game.resources.mounts[index].kind == i76_resource_provider_kind::memory ?
                           " (memory)" : " (directory)";
        }
        return make_reply(game, i76_result_code::ok, std::move(message));
    }
    if (verb == "mount" && !args.empty()) {
        code = i76_resource_mount_directory(game.resources, args);
        if (code != i76_resource_result::ok) {
            return make_reply(game, i76_result_code::invalid_argument,
                              resource_result_name(code));
        }
        return make_reply(game, i76_result_code::ok, "mounted directory: " + std::string(args));
    }
    return make_reply(game, i76_result_code::invalid_argument, "invalid resource command");
}

static i76_command_result execute_asset_command(i76_runtime& game, std::string_view args)
{
    std::string_view verb = {};
    i76_resource_stats stats = {};

    verb = take_token(args);
    if (verb != "stats" || !args.empty()) {
        return make_reply(game, i76_result_code::invalid_argument, "usage: asset stats");
    }
    stats = i76_resource_get_stats(game.resources);
    return make_reply(game, i76_result_code::ok,
                      "asset mounts=" + std::to_string(stats.mount_count) +
                      " cached=" + std::to_string(stats.cached_count) +
                      " references=" + std::to_string(stats.references) +
                      " bytes=" + std::to_string(stats.cached_bytes));
}

static i76_command_result execute_level_command(i76_runtime& game, std::string_view args)
{
    std::string_view verb = {};
    i76_level_definition inspected = {};
    i76_level_result code = i76_level_result::ok;
    std::string message = {};

    verb = take_token(args);
    if (verb == "help" && args.empty()) {
        return make_reply(game, i76_result_code::ok,
                          "level commands: inspect <name> | prepare <name> | activate | load <name> | "
                          "discard | unload | status");
    }
    if (verb == "status" && args.empty()) {
        message = "level loaded=" + (game.active_level.loaded ? game.active_level.definition.name :
                                     std::string("none"));
        message += " objects=" + std::to_string(i76_world_count(game.world));
        message += " assets=" + std::to_string(game.active_level.resources.size());
        message += " prepared=" + (game.prepared_level.ready ? game.prepared_level.definition.name :
                                   std::string("none"));
        return make_reply(game, i76_result_code::ok, std::move(message));
    }
    if (verb == "inspect" && !args.empty()) {
        code = i76_level_read(game.resources, args, inspected);
        if (code != i76_level_result::ok) {
            return make_reply(game, i76_result_code::invalid_argument, level_result_name(code));
        }
        message = "level " + inspected.name + " objects=" +
                  std::to_string(inspected.objects.size()) + " assets=" +
                  std::to_string(inspected.assets.size());
        return make_reply(game, i76_result_code::ok, std::move(message));
    }
    if ((verb == "prepare" || verb == "load") && !args.empty()) {
        code = i76_level_prepare(game.resources, args, game.prepared_level);
        if (code != i76_level_result::ok) {
            return make_reply(game, i76_result_code::invalid_argument, level_result_name(code));
        }
        if (verb == "prepare") {
            return make_reply(game, i76_result_code::ok,
                              "level prepared: " + game.prepared_level.definition.name);
        }
        verb = "activate";
        args = {};
    }
    if (verb == "activate" && args.empty()) {
        code = i76_level_activate(game.world, game.resources, game.prepared_level,
                                  game.active_level);
        if (code != i76_level_result::ok) {
            return make_reply(game, i76_result_code::invalid_argument, level_result_name(code));
        }
        return make_reply(game, i76_result_code::ok,
                          "level loaded: " + game.active_level.definition.name +
                          " objects=" + std::to_string(i76_world_count(game.world)));
    }
    if (verb == "discard" && args.empty()) {
        if (!game.prepared_level.ready) {
            return make_reply(game, i76_result_code::invalid_argument, "no prepared level");
        }
        i76_level_discard(game.resources, game.prepared_level);
        return make_reply(game, i76_result_code::ok, "prepared level discarded");
    }
    if (verb == "unload" && args.empty()) {
        code = i76_level_unload(game.world, game.resources, game.active_level);
        if (code != i76_level_result::ok) {
            return make_reply(game, i76_result_code::invalid_argument, level_result_name(code));
        }
        return make_reply(game, i76_result_code::ok, "level unloaded");
    }
    return make_reply(game, i76_result_code::invalid_argument, "invalid level command");
}

i76_command_result i76_execute_command(i76_runtime& game, std::string_view line)
{
    std::string_view command = {};
    std::string_view args = {};
    std::uint32_t count = 0;
    const char* begin = nullptr;
    const char* end = nullptr;
    std::from_chars_result parsed = {};
    i76_result_code result = i76_result_code::ok;

    if (!game.state.initialized) {
        return {i76_result_code::not_initialized, "runtime is not initialized"};
    }
    line = trim(line);
    if (line.empty()) {
        return make_reply(game, i76_result_code::invalid_argument, "empty command");
    }
    command = take_token(line);
    args = line;
    if (command == "help" && args.empty()) {
        return make_reply(game, i76_result_code::ok,
                          "commands: help status pause resume step <count> object <action> resource <action> "
                          "level <action> asset stats quit");
    }
    if (command == "status" && args.empty()) {
        return make_reply(game, i76_result_code::ok,
                          "ticks=" + std::to_string(game.state.tick) +
                              " paused=" + (game.state.paused ? "true" : "false") +
                              " exit=" + (game.state.exit_requested ? "true" : "false") +
                              " objects=" + std::to_string(i76_world_count(game.world)));
    }
    if (command == "pause" && args.empty()) {
        i76_runtime_set_paused(game, true);
        return make_reply(game, i76_result_code::ok, "paused");
    }
    if (command == "resume" && args.empty()) {
        i76_runtime_set_paused(game, false);
        return make_reply(game, i76_result_code::ok, "resumed");
    }
    if (command == "quit" && args.empty()) {
        i76_runtime_request_exit(game);
        return make_reply(game, i76_result_code::ok, "exit requested");
    }
    if (command == "object") {
        return execute_object_command(game, args);
    }
    if (command == "resource") {
        return execute_resource_command(game, args);
    }
    if (command == "asset") {
        return execute_asset_command(game, args);
    }
    if (command == "level") {
        return execute_level_command(game, args);
    }
    if (command == "step") {
        if (args.empty()) {
            return make_reply(game, i76_result_code::invalid_argument, "step requires a count");
        }
        begin = args.data();
        end = begin + args.size();
        parsed = std::from_chars(begin, end, count, 10);
        if (parsed.ec != std::errc{} || parsed.ptr != end || count == 0U ||
            count > i76_k_max_ticks_per_call) {
            return make_reply(game, i76_result_code::invalid_argument, "invalid step count");
        }
        result = i76_runtime_step(game, count);
        if (result != i76_result_code::ok) {
            return make_reply(game, result, "unable to advance simulation");
        }
        return make_reply(game, i76_result_code::ok,
                          "stepped " + std::to_string(count) + " tick(s)");
    }
    return make_reply(game, i76_result_code::unknown_command, "unknown command");
}
