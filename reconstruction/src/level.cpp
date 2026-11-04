#include "i76/level.h"

#include <array>
#include <limits>
#include <utility>

static std::string_view trim_level(std::string_view input) noexcept
{
    std::size_t begin = 0;
    std::size_t end = input.size();

    while (begin < end && (input[begin] == ' ' || input[begin] == '\t' || input[begin] == '\r')) {
        ++begin;
    }
    while (end > begin && (input[end - 1U] == ' ' || input[end - 1U] == '\t' ||
                           input[end - 1U] == '\r')) {
        --end;
    }
    return input.substr(begin, end - begin);
}

static bool parse_line(std::string_view line, std::array<std::string_view, 4>& tokens,
                       std::size_t& count) noexcept
{
    std::size_t start = 0;
    std::size_t end = 0;

    tokens = {};
    count = 0;
    while (start < line.size()) {
        while (start < line.size() && (line[start] == ' ' || line[start] == '\t')) {
            ++start;
        }
        if (start >= line.size()) {
            break;
        }
        if (count >= tokens.size()) {
            return false;
        }
        end = start;
        while (end < line.size() && line[end] != ' ' && line[end] != '\t') {
            ++end;
        }
        tokens[count++] = line.substr(start, end - start);
        start = end;
    }
    return true;
}

static bool valid_object_name(std::string_view name) noexcept
{
    std::size_t index = 0;
    unsigned char c = 0;

    if (name.empty() || name.size() > i76_world_max_name_length) {
        return false;
    }
    for (index = 0; index < name.size(); ++index) {
        c = static_cast<unsigned char>(name[index]);
        if (c < 33U || c > 126U) {
            return false;
        }
    }
    return true;
}

static bool add_asset(i76_level_definition& definition, std::string_view name)
{
    std::string key = {};
    std::size_t index = 0;

    if (i76_resource_normalize_name(name, key) != i76_resource_result::ok) {
        return false;
    }
    for (index = 0; index < definition.assets.size(); ++index) {
        if (definition.assets[index] == key) {
            return true;
        }
    }
    if (definition.assets.size() >= i76_level_max_assets) {
        return false;
    }
    definition.assets.push_back(std::move(key));
    return true;
}

i76_level_result i76_level_decode(std::span<const std::uint8_t> bytes,
                                  i76_level_definition& definition)
{
    i76_level_definition candidate = {};
    std::string_view data = {};
    std::string_view line = {};
    std::array<std::string_view, 4> tokens = {};
    std::size_t start = 0;
    std::size_t end = 0;
    std::size_t count = 0;
    std::size_t index = 0;
    bool header = false;
    i76_level_object_def object = {};

    if (bytes.empty() || bytes.size() > i76_level_max_manifest_bytes) {
        return i76_level_result::invalid_data;
    }
    data = std::string_view(reinterpret_cast<const char*>(bytes.data()), bytes.size());
    for (index = 0; index < data.size(); ++index) {
        if ((static_cast<unsigned char>(data[index]) < 32U && data[index] != '\n' &&
             data[index] != '\r' && data[index] != '\t') ||
            static_cast<unsigned char>(data[index]) > 126U) {
            return i76_level_result::invalid_data;
        }
    }
    while (start < data.size()) {
        end = data.find('\n', start);
        if (end == std::string_view::npos) {
            end = data.size();
        }
        line = trim_level(data.substr(start, end - start));
        start = end + (end < data.size() ? 1U : 0U);
        if (line.empty() || line.starts_with('#')) {
            continue;
        }
        if (!parse_line(line, tokens, count)) {
            return i76_level_result::invalid_data;
        }
        if (!header) {
            if (count != 2U || tokens[0] != "I76LEVEL" || tokens[1] != "1") {
                return i76_level_result::invalid_data;
            }
            header = true;
            continue;
        }
        if (tokens[0] == "asset" && count == 2U) {
            if (!add_asset(candidate, tokens[1])) {
                return i76_level_result::invalid_data;
            }
            continue;
        }
        if (tokens[0] == "object" && (count == 3U || count == 4U)) {
            if (candidate.objects.size() >= i76_level_max_objects ||
                !valid_object_name(tokens[2])) {
                return i76_level_result::invalid_data;
            }
            object = {};
            if (tokens[1] == "vehicle") {
                object.kind = i76_world_kind::vehicle;
            } else if (tokens[1] == "scenery") {
                object.kind = i76_world_kind::scenery;
            } else if (tokens[1] == "marker") {
                object.kind = i76_world_kind::marker;
            } else {
                return i76_level_result::invalid_data;
            }
            object.name = tokens[2];
            if (count == 4U) {
                if (!add_asset(candidate, tokens[3])) {
                    return i76_level_result::invalid_data;
                }
                if (i76_resource_normalize_name(tokens[3], object.asset) !=
                    i76_resource_result::ok) {
                    return i76_level_result::invalid_data;
                }
            }
            candidate.objects.push_back(std::move(object));
            continue;
        }
        return i76_level_result::invalid_data;
    }
    if (!header) {
        return i76_level_result::invalid_data;
    }
    definition = std::move(candidate);
    return i76_level_result::ok;
}

i76_level_result i76_level_read(i76_resource_store& store, std::string_view name,
                                i76_level_definition& definition)
{
    i76_resource_handle blob = {};
    i76_resource_result resource_status = i76_resource_result::ok;
    i76_level_result result = i76_level_result::ok;
    i76_level_definition candidate = {};
    const i76_resource_entry* entry = nullptr;

    if (!store.initialized) {
        return i76_level_result::not_initialized;
    }
    resource_status = i76_resource_acquire(store, name, blob);
    if (resource_status != i76_resource_result::ok) {
        return resource_status == i76_resource_result::not_found ? i76_level_result::not_found :
               resource_status == i76_resource_result::invalid_argument ?
                   i76_level_result::invalid_argument : i76_level_result::invalid_data;
    }
    try {
        entry = i76_resource_lookup(store, blob);
        result = i76_level_decode(entry->bytes, candidate);
        if (result == i76_level_result::ok) {
            candidate.name = name;
        }
    } catch (...) {
        i76_resource_release(store, blob);
        throw;
    }
    i76_resource_release(store, blob);
    if (result == i76_level_result::ok) {
        definition = std::move(candidate);
    }
    return result;
}

i76_level_result i76_level_discard(i76_resource_store& store,
                                   i76_prepared_level& prepared) noexcept
{
    std::size_t index = 0;

    if (!store.initialized) {
        return i76_level_result::not_initialized;
    }
    for (index = 0; index < prepared.resources.size(); ++index) {
        i76_resource_release(store, prepared.resources[index]);
    }
    prepared = {};
    return i76_level_result::ok;
}

i76_level_result i76_level_prepare(i76_resource_store& store, std::string_view name,
                                   i76_prepared_level& prepared)
{
    i76_resource_handle asset = {};
    i76_resource_result resource_status = i76_resource_result::ok;
    i76_level_result result = i76_level_result::ok;
    i76_prepared_level candidate = {};
    std::size_t index = 0;

    if (!store.initialized) {
        return i76_level_result::not_initialized;
    }
    if (prepared.ready) {
        return i76_level_result::busy;
    }
    result = i76_level_read(store, name, candidate.definition);
    if (result != i76_level_result::ok) {
        return result;
    }
    try {
        candidate.resources.reserve(candidate.definition.assets.size());
        for (index = 0; index < candidate.definition.assets.size(); ++index) {
            resource_status = i76_resource_acquire(store, candidate.definition.assets[index],
                                                   asset);
            if (resource_status != i76_resource_result::ok) {
                i76_level_discard(store, candidate);
                return resource_status == i76_resource_result::not_found ?
                           i76_level_result::not_found : i76_level_result::invalid_data;
            }
            candidate.resources.push_back(asset);
            asset = {};
        }
        candidate.ready = true;
        prepared = std::move(candidate);
    } catch (...) {
        if (asset.slot != 0U) {
            i76_resource_release(store, asset);
        }
        i76_level_discard(store, candidate);
        throw;
    }
    return i76_level_result::ok;
}

i76_level_result i76_level_unload(i76_world_registry& world, i76_resource_store& store,
                                  i76_active_level& active) noexcept
{
    std::size_t index = 0;

    if (!world.initialized || !store.initialized) {
        return i76_level_result::not_initialized;
    }
    if (!active.loaded) {
        return i76_level_result::not_loaded;
    }
    i76_world_clear(world);
    for (index = 0; index < active.resources.size(); ++index) {
        i76_resource_release(store, active.resources[index]);
    }
    active = {};
    return i76_level_result::ok;
}

i76_level_result i76_level_activate(i76_world_registry& world, i76_resource_store& store,
                                    i76_prepared_level& prepared, i76_active_level& active)
{
    i76_world_registry replacement = {};
    i76_world_handle handle = {};
    i76_world_result world_result = i76_world_result::ok;
    i76_active_level next = {};
    std::size_t index = 0;
    std::uint64_t max_generation = std::numeric_limits<std::uint64_t>::max();

    if (!world.initialized || !store.initialized) {
        return i76_level_result::not_initialized;
    }
    if (!prepared.ready) {
        return i76_level_result::not_prepared;
    }
    if (prepared.definition.objects.size() > i76_world_max_objects ||
        prepared.definition.objects.size() > max_generation - world.last_generation) {
        return i76_level_result::capacity_exceeded;
    }
    i76_world_initialize(replacement);
    replacement.last_generation = world.last_generation;
    for (index = 0; index < prepared.definition.objects.size(); ++index) {
        world_result = i76_world_create(replacement, prepared.definition.objects[index].kind,
                                         prepared.definition.objects[index].name, handle);
        if (world_result != i76_world_result::ok) {
            i76_world_shutdown(replacement);
            return i76_level_result::activation_failed;
        }
    }
    next.loaded = true;
    next.definition = std::move(prepared.definition);
    next.resources = std::move(prepared.resources);
    prepared = {};

    // Swapping only registry storage keeps the original registry instance (and
    // increasing generation sequence) intact. Preparation failures never touch it.
    world.slots.swap(replacement.slots);
    world.creation_order.swap(replacement.creation_order);
    world.last_generation = replacement.last_generation;
    i76_world_shutdown(replacement);
    for (index = 0; index < active.resources.size(); ++index) {
        i76_resource_release(store, active.resources[index]);
    }
    active = std::move(next);
    return i76_level_result::ok;
}
