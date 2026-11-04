#include "i76/level.h"
#include "i76/runtime.h"

#include <cstdint>
#include <iostream>
#include <limits>
#include <span>
#include <string>
#include <string_view>

static std::uint32_t failures = 0;

// -----------------------------------------------------------------------------
// Record a test failure when an assertion does not hold.
// -----------------------------------------------------------------------------
static void expect(bool condition, const char* label)
{
    if (!condition) {
        std::cerr << "FAIL: " << label << '\n';
        ++failures;
    }
}

// -----------------------------------------------------------------------------
// Convert a text fixture into a byte vector for level decoding.
// -----------------------------------------------------------------------------
static std::span<const std::uint8_t> raw(std::string_view text) noexcept
{
    return {reinterpret_cast<const std::uint8_t*>(text.data()), text.size()};
}

// -----------------------------------------------------------------------------
// Verify parser behavior and error cases.
// -----------------------------------------------------------------------------
static void test_parser()
{
    i76_level_definition definition = {};
    const char* invalid[] = {"", "not a manifest", "I76LEVEL 2\n",
        "I76LEVEL 1\nunknown x\n",
                             "I76LEVEL 1\nobject\n",
                             "I76LEVEL 1\nobject car x\n",
                             "I76LEVEL 1\nobject vehicle \n",
                             "I76LEVEL 1\nobject vehicle ok extra too\n",
                             "I76LEVEL 1\nasset ../../bad\n",
                             "I76LEVEL 1\nobject vehicle ok ../bad\n",
                             "I76LEVEL 1\nasset no space\n",
                             "I76LEVEL 1\nobject marker a\v\n",
                             "I76LEVEL 1\nasset a\nI76LEVEL 1\n"};

    expect(definition.objects.empty()
           && definition.name.empty()
           && definition.assets.empty(),
           "level definition zero initialization");
    expect(i76_level_decode(raw("I76LEVEL 1\r\n# comment\nasset SHARED.DAT\n"
                                "object vehicle scout shared.dat\nobject "
                                "marker flag\n"), definition) ==
               i76_level_result::ok, "decode valid synthetic manifest");
    expect(definition.objects.size() == 2U
           && definition.objects[0].kind ==
               i76_world_kind::vehicle
           && definition.assets.size() == 1U
           && definition.assets[0] == "shared.dat"
           && definition.objects[0].asset == "shared.dat",
           "parsed objects and unique asset dependencies");
    for (const char* bad : invalid) {
        expect(i76_level_decode(raw(bad), definition) ==
            i76_level_result::invalid_data,
               "reject malformed or unsupported record");
        expect(definition.objects.size() == 2U
               && definition.assets.size() ==
            1U,
               "parse errors preserve prior definition");
    }
    expect(i76_level_decode(raw("I76LEVEL 1\nobject scenery valid\n"),
        definition) ==
               i76_level_result::ok
                   && definition.objects.size() == 1U
                   && definition.assets.empty(), "decode asset-free level");
    expect(i76_level_decode(raw(std::string(65537U, 'a')), definition) ==
               i76_level_result::invalid_data, "oversized manifest rejected");
}

// -----------------------------------------------------------------------------
// Verify transactional lifecycle behavior and error cases.
// -----------------------------------------------------------------------------
static void test_transactional_lifecycle()
{
    i76_runtime game = {};
    i76_runtime_config config = {};
    i76_prepared_level candidate = {};
    i76_world_handle old = {};
    i76_world_handle fresh = {};
    std::uint64_t current_generation = 0;
    i76_resource_stats stats = {};

    config.tick_rate = 60U;
    expect(i76_runtime_initialize(game, config, i76_make_null_outputs()) ==
        i76_result_code::ok,
           "initialize runtime with built-in resource fixture");
    expect(game.resources.initialized
           && game.resources.mounts.size() == 1U
           && !game.active_level.loaded
           && !game.prepared_level.ready,
           "application owns resource store; levels start empty");
    expect(i76_level_unload(game.world, game.resources, game.active_level) ==
               i76_level_result::not_loaded, "reject unload of empty session");
    expect(i76_level_activate(game.world, game.resources, game.prepared_level,
                              game.active_level) ==
                              i76_level_result::not_prepared,
           "reject activate without prepare");
    expect(i76_level_prepare(game.resources, "missing.level",
        game.prepared_level) ==
               i76_level_result::not_found, "missing level rejected");
    expect(i76_level_prepare(game.resources, "../escape", game.prepared_level)
        ==
               i76_level_result::invalid_argument,
                   "unsafe level name rejected");
    expect(i76_level_prepare(game.resources, "demo.level", game.prepared_level)
        ==
               i76_level_result::ok, "prepare level without mutating world");
    expect(game.prepared_level.ready
           && !game.active_level.loaded
           && i76_world_count(game.world) == 0U
           && game.prepared_level.definition.objects.size() == 2U,
           "prepare is independent of world state");
    expect(i76_level_prepare(game.resources, "demo.level", game.prepared_level)
        ==
               i76_level_result::busy, "do not overwrite pending preparation");
    stats = i76_resource_get_stats(game.resources);
    expect(stats.cached_count == 1U
           && stats.references == 1U,
           "prepared level holds exactly one asset lease");
    expect(i76_level_activate(game.world, game.resources, game.prepared_level,
                              game.active_level) == i76_level_result::ok,
           "activate prepared level");
    expect(game.active_level.loaded
           && !game.prepared_level.ready
           && i76_world_count(game.world) == 2U,
           "activated level consumes prepared state");
    old = i76_world_handle_at(game.world, 0U);
    expect(i76_world_lookup(game.world, old) != nullptr
           && i76_world_lookup(game.world, old)->name == "demo_car",
                   "runtime actor instantiated");
    expect(i76_level_prepare(game.resources, "demo.level", candidate) ==
        i76_level_result::ok,
           "prepare next level while current remains active");
    stats = i76_resource_get_stats(game.resources);
    expect(stats.references == 2U
           && stats.cached_count == 1U,
           "two levels reference one shared asset cache entry");
    expect(i76_level_discard(game.resources, candidate) == i76_level_result::ok
            && !candidate.ready, "discard releases temporary asset references");
    expect(i76_resource_get_stats(game.resources).references == 1U,
           "active level retains its asset");
    expect(i76_level_prepare(game.resources, "missing.level", candidate) ==
               i76_level_result::not_found
                   && i76_world_lookup(game.world,
                   old) != nullptr,
           "preparation failure leaves active world untouched");
    expect(i76_level_prepare(game.resources, "demo.level", candidate) ==
        i76_level_result::ok,
           "prepare replacement");
    current_generation = game.world.last_generation;
    game.world.last_generation = std::numeric_limits<std::uint64_t>::max();
    expect(i76_level_activate(game.world, game.resources, candidate,
        game.active_level) ==
               i76_level_result::capacity_exceeded
                   && candidate.ready
                   && i76_world_lookup(game.world, old) != nullptr,
           "failed activation retains current world and prepared assets");
    game.world.last_generation = current_generation;
    expect(i76_level_activate(game.world, game.resources, candidate,
        game.active_level) ==
               i76_level_result::ok, "replacement activation succeeds");
    fresh = i76_world_handle_at(game.world, 0U);
    expect(fresh.slot == old.slot
           && fresh.generation > old.generation
           && i76_world_lookup(game.world, old) == nullptr,
           "replacement invalidates stale handles without resetting "
           "generation");
    expect(i76_resource_get_stats(game.resources).references == 1U,
           "old asset lease released on successful swap");
    expect(i76_level_unload(game.world, game.resources, game.active_level) ==
               i76_level_result::ok
                   && !game.active_level.loaded
                   && i76_world_lookup(game.world, fresh) == nullptr,
           "unload invalidates active objects");
    stats = i76_resource_get_stats(game.resources);
    expect(stats.cached_count == 0U
           && stats.references == 0U
           && stats.mount_count == 1U,
                   "unload frees cached payload, retains mounts");
    expect(i76_runtime_shutdown(game) == i76_result_code::ok
           && !game.resources.initialized
           && game.resources.mounts.empty(),
           "runtime shutdown releases resource store");
    expect(i76_runtime_initialize(game, config, i76_make_null_outputs()) ==
        i76_result_code::ok,
           "repeated application initialization");
    expect(i76_level_prepare(game.resources, "demo.level", candidate) ==
        i76_level_result::ok
            && i76_level_activate(game.world, game.resources, candidate,
                   game.active_level) ==
                   i76_level_result::ok, "load level after reinitialize");
    expect(i76_world_handle_at(game.world, 0U).generation > fresh.generation,
           "new application session does not resurrect old handles");
    expect(i76_runtime_shutdown(game) == i76_result_code::ok,
           "shutdown cleans active level automatically");
}

// -----------------------------------------------------------------------------
// Verify missing dependencies behavior and error cases.
// -----------------------------------------------------------------------------
static void test_missing_dependencies()
{
    i76_resource_store store = {};
    i76_prepared_level prepared = {};
    const std::string missing =
        "I76LEVEL 1\nobject scenery statue missing.geo\n";
    const std::string malformed = "I76LEVEL 1\nobject wrong invalid\n";
    const std::uint8_t byte = 0;
    i76_level_definition parsed_only = {};

    expect(i76_resource_initialize(store) == i76_resource_result::ok,
           "fixture store initialized");
    expect(i76_resource_mount_memory(store, "fixture") ==
        i76_resource_result::ok,
           "memory fixture mounted");
    expect(i76_resource_add_memory(store, "fixture", "broken.level",
        raw(malformed)) ==
               i76_resource_result::ok, "add malformed fixture");
    expect(i76_resource_add_memory(store, "fixture", "missing.level",
        raw(missing)) ==
               i76_resource_result::ok, "add missing-asset fixture");
    expect(i76_resource_add_memory(store, "fixture", "empty.level", {&byte,
        0U}) ==
               i76_resource_result::ok, "add empty level fixture");
    expect(i76_level_prepare(store, "broken.level", prepared) ==
        i76_level_result::invalid_data
            && !prepared.ready, "reject malformed level atomically");
    expect(i76_level_read(store, "missing.level", parsed_only) ==
        i76_level_result::ok
            && parsed_only.objects.size() == 1U
            && parsed_only.assets.size() ==
                   1U,
           "inspection can parse level without its dependencies");
    expect(i76_resource_get_stats(store).references == 0U,
           "parse-only read releases source bytes");
    expect(i76_level_prepare(store, "missing.level", prepared) ==
        i76_level_result::not_found
            && !prepared.ready, "reject absent transitive asset atomically");
    expect(i76_level_prepare(store, "empty.level", prepared) ==
        i76_level_result::invalid_data,
           "reject empty manifest");
    expect(i76_resource_get_stats(store).cached_count == 0U
           && i76_resource_get_stats(store).references == 0U,
           "all rejection paths relinquish temporary resource references");
    expect(i76_resource_shutdown(store) == i76_resource_result::ok,
        "cleanup fixtures");
}

// -----------------------------------------------------------------------------
// Run the test cases and return a failure status when any assertion fails.
// -----------------------------------------------------------------------------
int main()
{
    test_parser();
    test_transactional_lifecycle();
    test_missing_dependencies();
    return failures == 0U ? 0 : 1;
}
