#pragma once

#include "i76/resource.h"
#include "i76/world.h"

#include <cstdint>
#include <span>
#include <string>
#include <string_view>
#include <vector>

enum class i76_level_result : std::uint8_t {
    ok = 0,
    invalid_argument,
    not_initialized,
    busy,
    not_found,
    invalid_data,
    capacity_exceeded,
    not_prepared,
    not_loaded,
    activation_failed,
};

struct i76_level_object_def {
    i76_world_kind kind{};
    std::string name{};
    std::string asset{};
};

struct i76_level_definition {
    std::string name{};
    std::vector<std::string> assets{};
    std::vector<i76_level_object_def> objects{};
};

struct i76_prepared_level {
    bool ready{};
    i76_level_definition definition{};
    std::vector<i76_resource_handle> resources{};
};

struct i76_active_level {
    bool loaded{};
    i76_level_definition definition{};
    std::vector<i76_resource_handle> resources{};
};

inline constexpr std::size_t i76_level_max_objects = i76_world_max_objects;
inline constexpr std::size_t i76_level_max_assets = 256U;
inline constexpr std::size_t i76_level_max_manifest_bytes = 65536U;

// Manifest is an original, synthetic testing format, NOT retail BWD2.
i76_level_result i76_level_decode(std::span<const std::uint8_t> bytes,
                                  i76_level_definition& definition);
// Parse a synthetic level without acquiring any of its dependencies.
i76_level_result i76_level_read(i76_resource_store& store, std::string_view name,
                                i76_level_definition& definition);
i76_level_result i76_level_prepare(i76_resource_store& store, std::string_view name,
                                   i76_prepared_level& prepared);
i76_level_result i76_level_discard(i76_resource_store& store,
                                   i76_prepared_level& prepared) noexcept;
i76_level_result i76_level_activate(i76_world_registry& world, i76_resource_store& store,
                                    i76_prepared_level& prepared, i76_active_level& active);
i76_level_result i76_level_unload(i76_world_registry& world, i76_resource_store& store,
                                  i76_active_level& active) noexcept;
