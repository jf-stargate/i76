#include "i76/world.h"

#include <cstdint>
#include <iostream>
#include <limits>
#include <string>

static std::uint32_t failures = 0;

static void expect(bool condition, const char* label)
{
    if (!condition) {
        std::cerr << "FAIL: " << label << '\n';
        ++failures;
    }
}

static void test_lifecycle_and_validation()
{
    i76_world_registry world = {};
    i76_world_handle handle = {};
    i76_world_handle old_handle = {};
    const i76_world_object* object = nullptr;
    std::string long_name(65U, 'a');

    expect(!world.initialized && world.last_generation == 0U && world.slots.empty() &&
               i76_world_count(world) == 0U, "value-initialized registry");
    expect(i76_world_create(world, i76_world_kind::vehicle, "car", handle) ==
               i76_world_result::not_initialized && handle.slot == 0U,
           "spawn rejected before initialize");
    expect(i76_world_clear(world) == i76_world_result::not_initialized,
           "clear rejected before initialize");
    expect(i76_world_destroy(world, handle) == i76_world_result::not_initialized,
           "destroy rejected before initialize");
    expect(i76_world_shutdown(world) == i76_world_result::not_initialized,
           "shutdown rejected before initialize");
    expect(i76_world_lookup(world, {}) == nullptr &&
               i76_world_handle_at(world, 0U).slot == 0U,
           "lookup and enumeration reject inactive world");

    expect(i76_world_initialize(world) == i76_world_result::ok, "initialize");
    expect(i76_world_initialize(world) == i76_world_result::already_initialized,
           "duplicate initialize rejected");
    expect(i76_world_create(world, i76_world_kind::none, "car", handle) ==
               i76_world_result::invalid_argument, "invalid class rejected");
    expect(i76_world_create(world, static_cast<i76_world_kind>(255U), "car", handle) ==
               i76_world_result::invalid_argument, "unknown class rejected");
    expect(i76_world_create(world, i76_world_kind::vehicle, "", handle) ==
               i76_world_result::invalid_argument, "empty name rejected");
    expect(i76_world_create(world, i76_world_kind::vehicle, long_name, handle) ==
               i76_world_result::invalid_argument, "oversize name rejected");
    expect(i76_world_create(world, i76_world_kind::vehicle, "bad\nname", handle) ==
               i76_world_result::invalid_argument, "control character rejected");
    expect(i76_world_create(world, i76_world_kind::vehicle, "bad\0name", handle) ==
               i76_world_result::ok, "C string literal truncates at NUL by design");
    expect(i76_world_count(world) == 1U, "valid C string fixture constructed");
    expect(i76_world_clear(world) == i76_world_result::ok, "clear fixtures");
    expect(i76_world_create(world, i76_world_kind::marker,
                            std::string_view("bad\0name", 8U), handle) ==
               i76_world_result::invalid_argument, "embedded NUL rejected");
    expect(handle.slot == 0U && handle.generation == 0U && i76_world_count(world) == 0U,
           "invalid create returns no handle and no objects");

    expect(i76_world_create(world, i76_world_kind::vehicle, "scout", handle) ==
               i76_world_result::ok, "create scout");
    expect(handle.slot == 1U && handle.generation == 2U,
           "first live slot and monotonic generation");
    object = i76_world_lookup(world, handle);
    expect(object != nullptr && object->name == "scout" &&
               object->kind == i76_world_kind::vehicle && object->position.x == 0.0f &&
               object->position.y == 0.0f && object->position.z == 0.0f,
           "object data and position zero initialized");
    expect(i76_world_lookup(world, {0U, 2U}) == nullptr &&
               i76_world_lookup(world, {1U, 0U}) == nullptr &&
               i76_world_lookup(world, {2U, 2U}) == nullptr &&
               i76_world_lookup(world, {1U, 999U}) == nullptr,
           "invalid, out-of-range and wrong-generation handles rejected");
    old_handle = handle;
    expect(i76_world_shutdown(world) == i76_world_result::ok, "shutdown");
    expect(world.slots.empty() && world.creation_order.empty() && !world.initialized &&
               i76_world_lookup(world, handle) == nullptr,
           "shutdown releases resources and invalidates objects");
    expect(i76_world_initialize(world) == i76_world_result::ok, "reinitialize");
    expect(i76_world_create(world, i76_world_kind::vehicle, "replacement", handle) ==
               i76_world_result::ok, "create after reinitialize");
    expect(handle.slot == old_handle.slot && handle.generation != old_handle.generation &&
               i76_world_lookup(world, old_handle) == nullptr,
           "old handle stays invalid across reinitialization");
    expect(i76_world_shutdown(world) == i76_world_result::ok, "final shutdown");
}

static void test_order_and_generation()
{
    i76_world_registry world = {};
    i76_world_handle first = {};
    i76_world_handle second = {};
    i76_world_handle third = {};
    i76_world_handle fourth = {};

    expect(i76_world_initialize(world) == i76_world_result::ok, "order initialize");
    expect(i76_world_create(world, i76_world_kind::vehicle, "one", first) ==
               i76_world_result::ok, "create one");
    expect(i76_world_create(world, i76_world_kind::scenery, "two", second) ==
               i76_world_result::ok, "create two");
    expect(i76_world_create(world, i76_world_kind::marker, "three", third) ==
               i76_world_result::ok, "create three");
    expect(i76_world_count(world) == 3U && i76_world_handle_at(world, 0U).slot == first.slot &&
               i76_world_handle_at(world, 1U).slot == second.slot &&
               i76_world_handle_at(world, 2U).slot == third.slot,
           "initial creation order");
    expect(i76_world_handle_at(world, 3U).slot == 0U, "out-of-range enumeration");
    expect(i76_world_destroy(world, second) == i76_world_result::ok,
           "destroy middle object");
    expect(i76_world_destroy(world, second) == i76_world_result::invalid_handle &&
               i76_world_lookup(world, second) == nullptr,
           "double destroy and stale handle rejected");
    expect(i76_world_create(world, i76_world_kind::vehicle, "four", fourth) ==
               i76_world_result::ok, "reuse freed slot");
    expect(fourth.slot == second.slot && fourth.generation > second.generation &&
               i76_world_lookup(world, second) == nullptr,
           "generation changes on slot reuse");
    expect(i76_world_handle_at(world, 0U).generation == first.generation &&
               i76_world_handle_at(world, 1U).generation == third.generation &&
               i76_world_handle_at(world, 2U).generation == fourth.generation,
           "order by creation rather than slot index");
    expect(i76_world_clear(world) == i76_world_result::ok && i76_world_count(world) == 0U,
           "session clear");
    expect(i76_world_lookup(world, first) == nullptr &&
               i76_world_lookup(world, third) == nullptr &&
               i76_world_lookup(world, fourth) == nullptr,
           "all old handles invalid after session clear");
    expect(i76_world_create(world, i76_world_kind::vehicle, "new", first) ==
               i76_world_result::ok && first.generation > fourth.generation,
           "new session uses fresh generation");
    expect(i76_world_destroy(world, {0U, 0U}) == i76_world_result::invalid_handle,
           "zero handle invalid");
    expect(i76_world_shutdown(world) == i76_world_result::ok, "order shutdown");
}

static void test_capacity_and_exhaustion()
{
    i76_world_registry world = {};
    i76_world_handle handle = {};
    std::uint32_t index = 0;

    expect(i76_world_initialize(world) == i76_world_result::ok, "capacity initialize");
    for (index = 0; index < i76_world_max_objects; ++index) {
        if (i76_world_create(world, i76_world_kind::vehicle, "test", handle) !=
            i76_world_result::ok) {
            expect(false, "create through limit");
            break;
        }
    }
    expect(i76_world_count(world) == i76_world_max_objects, "capacity reached");
    expect(i76_world_create(world, i76_world_kind::vehicle, "excess", handle) ==
               i76_world_result::capacity_exceeded && handle.slot == 0U,
           "overflow rejected with null output handle");
    expect(i76_world_destroy(world, i76_world_handle_at(world, 0U)) ==
               i76_world_result::ok, "make room");
    expect(i76_world_create(world, i76_world_kind::marker, "new", handle) ==
               i76_world_result::ok && i76_world_count(world) == i76_world_max_objects,
           "capacity recovered after destruction");
    expect(i76_world_clear(world) == i76_world_result::ok, "capacity clear");
    world.last_generation = std::numeric_limits<std::uint64_t>::max();
    expect(i76_world_create(world, i76_world_kind::scenery, "no-reuse", handle) ==
               i76_world_result::capacity_exceeded,
           "exhausted generation never wraps and aliases stale handle");
    expect(i76_world_count(world) == 0U, "generation overflow does not mutate registry");
    expect(i76_world_shutdown(world) == i76_world_result::ok, "capacity shutdown");
}

int main()
{
    test_lifecycle_and_validation();
    test_order_and_generation();
    test_capacity_and_exhaustion();
    return failures == 0U ? 0 : 1;
}
