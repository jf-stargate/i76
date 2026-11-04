#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

// Runtime identities are NOT retail object addresses or serialized IDs.
// Slot 0 / generation 0 denotes an invalid, zero-initialized handle.
struct i76_world_handle {
    std::uint32_t slot{};
    std::uint64_t generation{};
};

// These are reconstructed logical classes, not recovered retail class IDs.
enum class i76_world_kind : std::uint8_t {
    none = 0,
    vehicle,
    scenery,
    marker,
};

enum class i76_world_result : std::uint8_t {
    ok = 0,
    already_initialized,
    not_initialized,
    invalid_argument,
    invalid_handle,
    capacity_exceeded,
};

struct i76_world_position {
    float x{};
    float y{};
    float z{};
};

struct i76_world_object {
    i76_world_handle handle{};
    i76_world_kind kind{};
    std::string name{};
    i76_world_position position{};
};

struct i76_world_slot {
    bool occupied{};
    i76_world_object object{};
};

struct i76_world_registry {
    bool initialized{};
    // Never reset during normal clear/shutdown/reinitialize of this instance.
    // Handles minted by an older session therefore cannot alias reused slots.
    std::uint64_t last_generation{};
    std::vector<i76_world_slot> slots{};
    std::vector<i76_world_handle> creation_order{};
};

inline constexpr std::uint32_t i76_world_max_objects = 4096U;
inline constexpr std::size_t i76_world_max_name_length = 64U;

i76_world_result i76_world_initialize(i76_world_registry& world) noexcept;
i76_world_result i76_world_shutdown(i76_world_registry& world) noexcept;
i76_world_result i76_world_clear(i76_world_registry& world) noexcept;
i76_world_result i76_world_create(i76_world_registry& world,
                                  i76_world_kind kind,
                                  std::string_view name,
                                  i76_world_handle& handle);
i76_world_result i76_world_destroy(i76_world_registry& world,
                                   i76_world_handle handle) noexcept;

// Borrowed object pointers are invalidated by any mutating registry operation.
// Never retain one across a frame boundary; persist the generation-checked
// handle.
const i76_world_object* i76_world_lookup(const i76_world_registry& world,
                                         i76_world_handle handle) noexcept;
std::size_t i76_world_count(const i76_world_registry& world) noexcept;
i76_world_handle i76_world_handle_at(const i76_world_registry& world,
                                     std::size_t creation_index) noexcept;
