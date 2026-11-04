#include "i76/command.h"
#include "i76/console.h"
#include "i76/bwd2.h"
#include "i76/retail_mission.h"

#include <charconv>
#include <cstdint>
#include <sstream>
#include <system_error>
#include <utility>

// -----------------------------------------------------------------------------
// Remove surrounding whitespace from console command text.
// -----------------------------------------------------------------------------
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

// -----------------------------------------------------------------------------
// Consume the next whitespace-delimited command token.
// -----------------------------------------------------------------------------
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

// -----------------------------------------------------------------------------
// Construct a command reply and emit its diagnostic event.
// -----------------------------------------------------------------------------
static i76_command_result make_reply(i76_runtime& game,
                                     i76_result_code code,
                                     std::string message)
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

// -----------------------------------------------------------------------------
// Convert an object-kind token into a typed world object kind.
// -----------------------------------------------------------------------------
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

// -----------------------------------------------------------------------------
// Return the human-readable name of a world object kind.
// -----------------------------------------------------------------------------
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

// -----------------------------------------------------------------------------
// Format a generation-checked world handle for console output.
// -----------------------------------------------------------------------------
static std::string handle_text(i76_world_handle handle)
{
    return std::to_string(handle.slot) + ":" +
        std::to_string(handle.generation);
}

// -----------------------------------------------------------------------------
// Validate and decode a textual slot-and-generation world handle.
// -----------------------------------------------------------------------------
static bool parse_handle(std::string_view text,
                         i76_world_handle& handle) noexcept
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
    if (parsed.ec != std::errc{} || parsed.ptr != end || candidate.generation ==
        0U) {
        return false;
    }
    handle = candidate;
    return true;
}

// -----------------------------------------------------------------------------
// Execute world-object inspection and mutation commands.
// -----------------------------------------------------------------------------
static i76_command_result execute_object_command(i76_runtime& game,
    std::string_view args)
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
                message += "\n  " + handle_text(handle) + " " +
                    kind_name(object->kind) +
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
        name = args;
        kind = parse_kind(kind_text);
        if (kind == i76_world_kind::none || name.empty()) {
            return make_reply(game, i76_result_code::invalid_argument,
                              "usage: object spawn <vehicle|scenery|marker> <name>");
        }
        status = i76_world_create(game.world, kind, name, handle);
        if (status == i76_world_result::invalid_argument) {
            return make_reply(game, i76_result_code::invalid_argument,
                "invalid object name");
        }
        if (status != i76_world_result::ok) {
            return make_reply(game, i76_result_code::overflow,
                "object capacity exceeded");
        }
        return make_reply(game, i76_result_code::ok,
                          "spawned " + std::string(kind_name(kind)) + " " +
                          std::string(name) +
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
            return make_reply(game, i76_result_code::not_found,
                "object handle not found");
        }
        if (verb == "destroy") {
            status = i76_world_destroy(game.world, handle);
            if (status != i76_world_result::ok) {
                return make_reply(game, i76_result_code::not_found,
                    "object handle not found");
            }
            return make_reply(game, i76_result_code::ok,
                              "destroyed object handle=" + handle_text(handle));
        }
        message = "object handle=" + handle_text(handle) + " kind=" +
            kind_name(object->kind) +
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
    return make_reply(game, i76_result_code::invalid_argument,
        "invalid object command (object help)");
}

// -----------------------------------------------------------------------------
// Translate resource-provider result codes into readable text.
// -----------------------------------------------------------------------------
static const char* resource_result_name(i76_resource_result result) noexcept
{
    switch (result) {
    case i76_resource_result::ok: return "ok";
    case i76_resource_result::already_initialized: return "already initialized";
    case i76_resource_result::not_initialized: return "not initialized";
    case i76_resource_result::invalid_argument: return
        "invalid resource path or name";
    case i76_resource_result::not_found: return "not found";
    case i76_resource_result::busy: return "resource still retained";
    case i76_resource_result::too_large: return "resource exceeds size limit";
    case i76_resource_result::io_error: return "resource I/O failure";
    case i76_resource_result::capacity_exceeded: return
        "resource capacity exceeded";
    }
    return "unknown resource error";
}

// -----------------------------------------------------------------------------
// Translate level-loader result codes into readable text.
// -----------------------------------------------------------------------------
static const char* level_result_name(i76_level_result result) noexcept
{
    switch (result) {
    case i76_level_result::ok: return "ok";
    case i76_level_result::invalid_argument: return "invalid level name";
    case i76_level_result::not_initialized: return
        "level runtime is not initialized";
    case i76_level_result::busy: return
        "prepared level already exists (level discard first)";
    case i76_level_result::not_found: return "level or asset not found";
    case i76_level_result::invalid_data: return
        "invalid level data or asset read";
    case i76_level_result::capacity_exceeded: return "level capacity exceeded";
    case i76_level_result::not_prepared: return "no prepared level";
    case i76_level_result::not_loaded: return "no loaded level";
    case i76_level_result::activation_failed: return
        "unable to instantiate level objects";
    }
    return "unknown level error";
}

// -----------------------------------------------------------------------------
// Execute resource mount, lookup, and cache commands.
// -----------------------------------------------------------------------------
static i76_command_result execute_resource_command(i76_runtime& game,
    std::string_view args)
{
    std::string_view verb = {};
    i76_resource_result code = i76_resource_result::ok;
    std::string message = {};
    std::size_t index = 0;
    std::size_t entry_index = 0;
    std::uint64_t id = 0;
    std::uint64_t references = 0;
    const char* begin = nullptr;
    const char* end = nullptr;
    std::from_chars_result parsed = {};
    i76_resource_result lookup = i76_resource_result::not_found;

    verb = take_token(args);
    if (verb == "help" && args.empty()) {
        return make_reply(game, i76_result_code::ok,
                          "resource commands: resource list | resource mounts | "
                          "resource cache | resource mount <directory> | "
                          "resource unmount <id|name>");
    }
    if ((verb == "list" || verb == "mounts") && args.empty()) {
        message = "resource mounts=" +
            std::to_string(game.resources.mounts.size());
        for (index = 0; index < game.resources.mounts.size(); ++index) {
            const i76_resource_mount& mount = game.resources.mounts[index];
            references = 0;
            for (entry_index = 0; entry_index < game.resources.entries.size();
                ++entry_index) {
                const i76_resource_entry& entry =
                    game.resources.entries[entry_index];
                if (entry.occupied && entry.source_mount_id == mount.id) {
                    references += entry.references;
                }
            }
            message += "\n  [" + std::to_string(mount.id) + "] " + mount.name;
            message += mount.kind == i76_resource_provider_kind::memory ?
                           " (memory)" : " (directory)";
            message += " references=" + std::to_string(references);
        }
        return make_reply(game, i76_result_code::ok, std::move(message));
    }
    if (verb == "cache" && args.empty()) {
        message = "resource cached=" +
            std::to_string(i76_resource_get_stats(game.resources).cached_count);
        for (index = 0; index < game.resources.entries.size(); ++index) {
            const i76_resource_entry& entry = game.resources.entries[index];
            if (!entry.occupied) {
                continue;
            }
            message += "\n  " + entry.name + " mount=" +
                std::to_string(entry.source_mount_id) +
                       " references=" + std::to_string(entry.references) +
                       " bytes=" + std::to_string(entry.bytes.size());
        }
        return make_reply(game, i76_result_code::ok, std::move(message));
    }
    if (verb == "mount" && !args.empty()) {
        code = i76_resource_mount_directory(game.resources, args);
        if (code != i76_resource_result::ok) {
            return make_reply(game, i76_result_code::invalid_argument,
                              resource_result_name(code));
        }
        return make_reply(game, i76_result_code::ok,
                          "mounted directory [" +
                          std::to_string(game.resources.mounts.back().id) +
                          "]: " +
                          game.resources.mounts.back().name);
    }
    if (verb == "unmount" && !args.empty()) {
        lookup = i76_resource_find_mount(game.resources, args, id);
        if (lookup == i76_resource_result::invalid_argument) {
            return make_reply(game, i76_result_code::invalid_argument,
                              "ambiguous mount name; use the numeric ID from resource list");
        }
        if (lookup == i76_resource_result::not_found) {
            begin = args.data();
            end = begin + args.size();
            parsed = std::from_chars(begin, end, id, 10);
            if (parsed.ec != std::errc{} || parsed.ptr != end || id == 0U) {
                return make_reply(game, i76_result_code::invalid_argument,
                                  "usage: resource unmount <mount id|mount path/name>");
            }
        }
        code = i76_resource_unmount(game.resources, id);
        if (code != i76_resource_result::ok) {
            message = "resource unmount failed: ";
            message += resource_result_name(code);
            if (code == i76_resource_result::busy) {
                message += " (unload/discard the level before unmounting)";
            }
            return make_reply(game, i76_result_code::invalid_argument,
                std::move(message));
        }
        return make_reply(game, i76_result_code::ok,
                          "unmounted resource [" + std::to_string(id) + "]");
    }
    return make_reply(game, i76_result_code::invalid_argument,
                      "invalid resource command (resource help)");
}

// -----------------------------------------------------------------------------
// Report asset-cache statistics through the developer console.
// -----------------------------------------------------------------------------
static i76_command_result execute_asset_command(i76_runtime& game,
    std::string_view args)
{
    std::string_view verb = {};
    i76_resource_stats stats = {};

    verb = take_token(args);
    if (verb != "stats" || !args.empty()) {
        return make_reply(game, i76_result_code::invalid_argument,
            "usage: asset stats");
    }
    stats = i76_resource_get_stats(game.resources);
    return make_reply(game, i76_result_code::ok,
                      "asset mounts=" + std::to_string(stats.mount_count) +
                      " cached=" + std::to_string(stats.cached_count) +
                      " references=" + std::to_string(stats.references) +
                      " bytes=" + std::to_string(stats.cached_bytes));
}

// -----------------------------------------------------------------------------
// Check whether a resource key names a retail BWD2 level file.
// -----------------------------------------------------------------------------
static bool bwd2_extension(std::string_view name) noexcept
{
    std::size_t dot = 0;
    std::string_view extension = {};
    char characters[5]{};
    std::size_t index = 0;

    dot = name.find_last_of('.');
    if (dot == std::string_view::npos || name.size() - dot > sizeof(characters))
        {
        return false;
    }
    extension = name.substr(dot);
    for (index = 0; index < extension.size(); ++index) {
        characters[index] = extension[index] >= 'A' && extension[index] <= 'Z' ?
                                static_cast<char>(extension[index] - 'A' + 'a')
                                : extension[index];
    }
    return std::string_view(characters) == ".msn" ||
           std::string_view(characters) == ".lvl" ||
           std::string_view(characters) == ".spc";
}

// -----------------------------------------------------------------------------
// Format a byte offset as a hexadecimal diagnostic address.
// -----------------------------------------------------------------------------
static std::string byte_offset(std::uint32_t offset)
{
    std::ostringstream stream = {};

    stream << "0x" << std::hex << offset;
    return stream.str();
}

// -----------------------------------------------------------------------------
// Inspect the chunk inventory of a retail mission without loading it.
// -----------------------------------------------------------------------------
static i76_command_result inspect_bwd2(i76_runtime& game, std::string_view name)
{
    constexpr std::size_t k_display_limit = 128U;
    i76_bwd2_document document = {};
    i76_bwd2_error error = {};
    i76_bwd2_result code = i76_bwd2_result::ok;
    std::string message = {};
    std::size_t index = 0;
    std::uint32_t indent = 0;
    const i76_bwd2_chunk* chunk = nullptr;

    code = i76_bwd2_read(game.resources, name, document, error);
    if (code != i76_bwd2_result::ok) {
        message = std::string("BWD2 inspection failed: ") +
            i76_bwd2_result_name(code) +
                  " at " + byte_offset(error.offset);
        return make_reply(game, i76_result_code::invalid_argument,
            std::move(message));
    }
    message = "BWD2 " + std::string(name) + " bytes=" +
              std::to_string(document.byte_count) + " chunks=" +
              std::to_string(document.chunks.size()) +
                  " (structural only; not loaded)";
    for (index = 0; index < document.chunks.size() && index < k_display_limit;
        ++index) {
        chunk = &document.chunks[index];
        message += "\n  ";
        for (indent = 0U; indent < chunk->depth; ++indent) {
            message += "  ";
        }
        message += chunk->tag;
        message += " offset=" + byte_offset(chunk->offset);
        message += " size=" + std::to_string(chunk->size);
        if (chunk->has_revision) {
            message += " revision=" + std::to_string(chunk->revision);
        }
    }
    if (document.chunks.size() > k_display_limit) {
        message += "\n  ... " + std::to_string(document.chunks.size() -
            k_display_limit) +
                   " more sections (inventory output limited to 128)";
    }
    return make_reply(game, i76_result_code::ok, std::move(message));
}


// -----------------------------------------------------------------------------
// Decode retail mission metadata and optional terrain statistics.
// -----------------------------------------------------------------------------
static i76_command_result inspect_retail_mission(i76_runtime& game,
    std::string_view action,
    std::string_view name)
{
    i76_retail_mission_definition mission{};
    i76_retail_terrain_samples samples{};
    i76_retail_error error{};
    i76_retail_result result{i76_retail_result::ok};
    std::string message{};

    result = i76_retail_mission_read(game.resources, name, mission, error);
    if (result != i76_retail_result::ok) {
        message = "retail mission inspection failed: ";
        message += i76_retail_result_name(result);
        message += " at " + byte_offset(error.offset);
        return make_reply(game, i76_result_code::invalid_argument,
            std::move(message));
    }

    if (action == "summary") {
        message = "retail mission " + mission.name +
                  " bytes=" + std::to_string(mission.byte_count) +
                  " chunks=" + std::to_string(mission.chunk_count) +
                  " revision=" + std::to_string(mission.revision) +
                  " (read-only; not loaded)";
        message += "\n  WRLD=" + std::to_string(mission.wrld_records) +
                   " OBJ=" + std::to_string(mission.object_records) +
                   " RSEG=" + std::to_string(mission.route_records) +
                   " FSM=" + std::to_string(mission.fsm_records);
        for (const i76_retail_section& section : mission.sections) {
            message += "\n  " + section.tag + " bytes=" +
                std::to_string(section.bytes) +
                       " records=" + std::to_string(section.direct_children);
            if (section.has_revision) {
                message += " revision=" + std::to_string(section.revision);
            }
        }
        if (mission.terrain.has_zmap) {
            message += "\n  ZMAP active_pages=" +
                       std::to_string(mission.terrain.active_pages) +
                       " mapped_cells=" +
                           std::to_string(mission.terrain.mapped_cells) +
                       " referenced_pages=" +
                           std::to_string(mission.terrain.referenced_pages);
        }
        if (mission.terrain.has_zone) {
            message += "\n  ZONE sidecar=" + mission.terrain.resource_name +
                       " prefix_byte=" +
                           std::to_string(mission.terrain.zone_prefix_byte);
        }
        return make_reply(game, i76_result_code::ok, std::move(message));
    }

    if (action == "dependencies") {
        message = "retail dependencies " + mission.name +
            " (known references only)";
        if (!mission.terrain.has_zone) {
            message += "\n  TER: no ZONE reference decoded";
        } else {
            result = i76_retail_terrain_probe(game.resources, mission, samples,
                error);
            message += "\n  TER " + mission.terrain.resource_name + " status=" +
                       i76_retail_result_name(result);
            if (result == i76_retail_result::ok) {
                message += " pages=" + std::to_string(samples.pages);
            }
        }
        message += "\n  WRLD records=" + std::to_string(mission.wrld_records) +
                   " (resource fields not yet decoded)";
        return make_reply(game, i76_result_code::ok, std::move(message));
    }

    result = i76_retail_terrain_probe(game.resources, mission, samples, error);
    if (result != i76_retail_result::ok) {
        message = "retail terrain inspection failed: ";
        message += i76_retail_result_name(result);
        message += " (" + mission.terrain.resource_name + ")";
        return make_reply(game, i76_result_code::invalid_argument,
            std::move(message));
    }
    message = "retail terrain " + mission.name +
              " active_pages=" + std::to_string(mission.terrain.active_pages) +
              " mapped_cells=" + std::to_string(mission.terrain.mapped_cells) +
              " referenced_pages=" +
                  std::to_string(mission.terrain.referenced_pages) +
              " TER=" + mission.terrain.resource_name +
              " samples=" + std::to_string(samples.samples) +
              " height_min=" + std::to_string(samples.height_min) +
              " height_max=" + std::to_string(samples.height_max) +
              " surface_flags=" + std::to_string(samples.surface_flags);
    for (std::size_t index = 0U; index < samples.surface_classes.size();
        ++index) {
        if (samples.surface_classes[index] != 0U) {
            message += "\n  surface_class=" + std::to_string(index) +
                       " samples=" +
                           std::to_string(samples.surface_classes[index]);
        }
    }
    return make_reply(game, i76_result_code::ok, std::move(message));
}

// -----------------------------------------------------------------------------
// Dispatch read-only inspection and synthetic level lifecycle commands.
// -----------------------------------------------------------------------------
static i76_command_result execute_level_command(i76_runtime& game,
    std::string_view args)
{
    std::string_view verb = {};
    i76_level_definition inspected = {};
    i76_level_result code = i76_level_result::ok;
    std::string message = {};

    verb = take_token(args);
    if (verb == "help" && args.empty()) {
        return make_reply(game, i76_result_code::ok,
                          "level commands: inspect <name> | sections <BWD2 name> | summary <mission> | terrain <mission> | dependencies <mission> | prepare <synthetic name> | activate | load <synthetic name> | "
                          "discard | unload | status");
    }
    if ((verb == "summary" || verb == "terrain" || verb == "dependencies") &&
        !args.empty()) {
        return inspect_retail_mission(game, verb, args);
    }
    if (verb == "status" && args.empty()) {
        message = "level loaded=" + (game.active_level.loaded ?
            game.active_level.definition.name :
                                     std::string("none"));
        message += " objects=" + std::to_string(i76_world_count(game.world));
        message += " assets=" +
            std::to_string(game.active_level.resources.size());
        message += " prepared=" + (game.prepared_level.ready ?
            game.prepared_level.definition.name :
                                   std::string("none"));
        return make_reply(game, i76_result_code::ok, std::move(message));
    }
    if ((verb == "sections" || (verb == "inspect" && bwd2_extension(args))) &&
        !args.empty()) {
        return inspect_bwd2(game, args);
    }
    if (verb == "inspect" && !args.empty()) {
        code = i76_level_read(game.resources, args, inspected);
        if (code != i76_level_result::ok) {
            return make_reply(game, i76_result_code::invalid_argument,
                level_result_name(code));
        }
        message = "level " + inspected.name + " objects=" +
                  std::to_string(inspected.objects.size()) + " assets=" +
                  std::to_string(inspected.assets.size());
        return make_reply(game, i76_result_code::ok, std::move(message));
    }
    if ((verb == "prepare" || verb == "load") && !args.empty()) {
        if (bwd2_extension(args)) {
            return make_reply(game, i76_result_code::invalid_argument,
                              "retail BWD2 activation is not implemented; use level inspect or level sections");
        }
        code = i76_level_prepare(game.resources, args, game.prepared_level);
        if (code != i76_level_result::ok) {
            return make_reply(game, i76_result_code::invalid_argument,
                level_result_name(code));
        }
        if (verb == "prepare") {
            return make_reply(game, i76_result_code::ok,
                              "level prepared: " +
                              game.prepared_level.definition.name);
        }
        verb = "activate";
        args = {};
    }
    if (verb == "activate" && args.empty()) {
        code = i76_level_activate(game.world, game.resources,
            game.prepared_level,
                                  game.active_level);
        if (code != i76_level_result::ok) {
            return make_reply(game, i76_result_code::invalid_argument,
                level_result_name(code));
        }
        return make_reply(game, i76_result_code::ok,
                          "level loaded: " + game.active_level.definition.name +
                          " objects=" +
                          std::to_string(i76_world_count(game.world)));
    }
    if (verb == "discard" && args.empty()) {
        if (!game.prepared_level.ready) {
            return make_reply(game, i76_result_code::invalid_argument,
                "no prepared level");
        }
        i76_level_discard(game.resources, game.prepared_level);
        return make_reply(game, i76_result_code::ok,
            "prepared level discarded");
    }
    if (verb == "unload" && args.empty()) {
        code = i76_level_unload(game.world, game.resources, game.active_level);
        if (code != i76_level_result::ok) {
            return make_reply(game, i76_result_code::invalid_argument,
                level_result_name(code));
        }
        return make_reply(game, i76_result_code::ok, "level unloaded");
    }
    return make_reply(game, i76_result_code::invalid_argument,
        "invalid level command");
}

// -----------------------------------------------------------------------------
// Execute established runtime commands behind the shared registry.
// -----------------------------------------------------------------------------
i76_command_result i76_execute_legacy_command(i76_runtime& game,
    std::string_view line)
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
        return make_reply(game, i76_result_code::invalid_argument,
            "empty command");
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
                              " paused=" + (game.state.paused ? "true" :
                              "false") +
                              " exit=" + (game.state.exit_requested ? "true" :
                              "false") +
                              " objects=" +
                              std::to_string(i76_world_count(game.world)));
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
            return make_reply(game, i76_result_code::invalid_argument,
                "step requires a count");
        }
        begin = args.data();
        end = begin + args.size();
        parsed = std::from_chars(begin, end, count, 10);
        if (parsed.ec != std::errc{} || parsed.ptr != end || count == 0U ||
            count > i76_k_max_ticks_per_call) {
            return make_reply(game, i76_result_code::invalid_argument,
                "invalid step count");
        }
        result = i76_runtime_step(game, count);
        if (result != i76_result_code::ok) {
            return make_reply(game, result, "unable to advance simulation");
        }
        return make_reply(game, i76_result_code::ok,
                          "stepped " + std::to_string(count) + " tick(s)");
    }
    return make_reply(game, i76_result_code::unknown_command,
        "unknown command");
}

// -----------------------------------------------------------------------------
// Route user commands through the registered console dispatcher.
// -----------------------------------------------------------------------------
i76_command_result i76_execute_command(i76_runtime& game, std::string_view line)
{
    return i76_console_execute(game, line);
}
