#include "i76/world.h"

#include <limits>
#include <utility>

// -----------------------------------------------------------------------------
// Check that a world-object kind is supported.
// -----------------------------------------------------------------------------
static bool valid_kind(i76_world_kind kind) noexcept
{
    return kind == i76_world_kind::vehicle
           || kind == i76_world_kind::scenery
           || kind == i76_world_kind::marker;
}

// -----------------------------------------------------------------------------
// Check object names for the permitted length and ASCII characters.
// -----------------------------------------------------------------------------
static bool valid_name(std::string_view name) noexcept
{
    std::size_t index = 0;
    unsigned char character = 0;

    if (name.empty()
        || name.size() > i76_world_max_name_length) {
        return false;
    }
    for (index = 0; index < name.size(); ++index) {
        character = static_cast<unsigned char>(name[index]);
        if (character < 32U
            || character > 126U) {
            return false;
        }
    }
    return true;
}

// -----------------------------------------------------------------------------
// Initialize the world registry while retaining handle generations.
// -----------------------------------------------------------------------------
i76_world_result i76_world_initialize(i76_world_registry& world) noexcept
{
    if (world.initialized) {
        return i76_world_result::already_initialized;
    }
    world.initialized = true;
    return i76_world_result::ok;
}

// -----------------------------------------------------------------------------
// Remove world objects without invalidating the registry itself.
// -----------------------------------------------------------------------------
i76_world_result i76_world_clear(i76_world_registry& world) noexcept
{
    std::size_t index = 0;

    if (!world.initialized) {
        return i76_world_result::not_initialized;
    }
    for (index = 0; index < world.slots.size(); ++index) {
        world.slots[index].object = {};
        world.slots[index].occupied = false;
    }
    world.creation_order.clear();
    return i76_world_result::ok;
}

// -----------------------------------------------------------------------------
// Release world storage while keeping generation history.
// -----------------------------------------------------------------------------
i76_world_result i76_world_shutdown(i76_world_registry& world) noexcept
{
    std::vector<i76_world_slot> empty_slots = {};
    std::vector<i76_world_handle> empty_order = {};

    if (!world.initialized) {
        return i76_world_result::not_initialized;
    }
    world.slots.swap(empty_slots);
    world.creation_order.swap(empty_order);
    world.initialized = false;
    // Keep last_generation: a later initialization of the same world instance
    // must never bring a previously issued handle back to life.
    return i76_world_result::ok;
}

// -----------------------------------------------------------------------------
// Allocate a generation-checked world object with stable ordering.
// -----------------------------------------------------------------------------
i76_world_result i76_world_create(i76_world_registry& world,
                                  i76_world_kind kind,
                                  std::string_view name,
                                  i76_world_handle& handle)
{
    std::size_t index = 0;
    std::size_t selected = 0;
    i76_world_object object = {};
    i76_world_handle new_handle = {};

    handle = {};
    if (!world.initialized) {
        return i76_world_result::not_initialized;
    }
    if (!valid_kind(kind)
        || !valid_name(name)) {
        return i76_world_result::invalid_argument;
    }
    if (world.creation_order.size() >= i76_world_max_objects
        || world.last_generation == std::numeric_limits<std::uint64_t>::max()) {
        return i76_world_result::capacity_exceeded;
    }

    // Slot storage is inspectable in GDB; no raw pointer is a durable identity.
    selected = world.slots.size();
    if (world.creation_order.size() != world.slots.size()) {
        for (index = 0; index < world.slots.size(); ++index) {
            if (!world.slots[index].occupied) {
                selected = index;
                break;
            }
        }
    }
    if (selected == world.slots.size()
        && world.slots.size() >=
        i76_world_max_objects) {
        return i76_world_result::capacity_exceeded;
    }

    new_handle.slot = static_cast<std::uint32_t>(selected + 1U);
    new_handle.generation = world.last_generation + 1U;
    object.handle = new_handle;
    object.kind = kind;
    object.name.assign(name);

    // Reserve the ordered handle list first so that once the slot is installed,
    // appending the handle cannot fail and leave a half-created live object.
    world.creation_order.reserve(world.creation_order.size() + 1U);
    if (selected == world.slots.size()) {
        world.slots.emplace_back();
    }
    world.slots[selected].object = std::move(object);
    world.slots[selected].occupied = true;
    world.creation_order.push_back(new_handle);
    world.last_generation = new_handle.generation;
    handle = new_handle;
    return i76_world_result::ok;
}

// -----------------------------------------------------------------------------
// Validate a world handle and return its live object if present.
// -----------------------------------------------------------------------------
const i76_world_object* i76_world_lookup(const i76_world_registry& world,
                                         i76_world_handle handle) noexcept
{
    std::size_t index = 0;
    const i76_world_slot* slot = nullptr;

    if (!world.initialized
        || handle.slot == 0U
        || handle.generation == 0U) {
        return nullptr;
    }
    index = static_cast<std::size_t>(handle.slot - 1U);
    if (index >= world.slots.size()) {
        return nullptr;
    }
    slot = &world.slots[index];
    if (!slot->occupied
        || slot->object.handle.generation != handle.generation)
        {
        return nullptr;
    }
    return &slot->object;
}

// -----------------------------------------------------------------------------
// Remove the object named by a valid generation-checked handle.
// -----------------------------------------------------------------------------
i76_world_result i76_world_destroy(i76_world_registry& world,
                                   i76_world_handle handle) noexcept
{
    std::size_t index = 0;
    std::size_t slot_index = 0;

    if (!world.initialized) {
        return i76_world_result::not_initialized;
    }
    if (i76_world_lookup(world, handle) == nullptr) {
        return i76_world_result::invalid_handle;
    }
    slot_index = static_cast<std::size_t>(handle.slot - 1U);
    for (index = 0; index < world.creation_order.size(); ++index) {
        if (world.creation_order[index].slot == handle.slot
            && world.creation_order[index].generation == handle.generation) {
            world.creation_order.erase(world.creation_order.begin() +
                                       static_cast<std::ptrdiff_t>(index));
            break;
        }
    }
    world.slots[slot_index].object = {};
    world.slots[slot_index].occupied = false;
    return i76_world_result::ok;
}

// -----------------------------------------------------------------------------
// Count live world objects in creation order.
// -----------------------------------------------------------------------------
std::size_t i76_world_count(const i76_world_registry& world) noexcept
{
    return world.initialized ? world.creation_order.size() : 0U;
}

// -----------------------------------------------------------------------------
// Return the live handle at a given creation-order position.
// -----------------------------------------------------------------------------
i76_world_handle i76_world_handle_at(const i76_world_registry& world,
                                     std::size_t creation_index) noexcept
{
    if (!world.initialized
        || creation_index >= world.creation_order.size()) {
        return {};
    }
    return world.creation_order[creation_index];
}
