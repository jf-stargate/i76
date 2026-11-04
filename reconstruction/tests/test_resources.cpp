#include "i76/resource.h"

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

static std::uint32_t failures = 0;

// -----------------------------------------------------------------------------
// Record a test failure when the expected condition is false.
// -----------------------------------------------------------------------------
static void expect(bool condition, const char* label)
{
    if (!condition) {
        std::cerr << "FAIL: " << label << '\n';
        ++failures;
    }
}

// -----------------------------------------------------------------------------
// Verify resource key normalization rejects unsafe paths.
// -----------------------------------------------------------------------------
static void test_normalize()
{
    std::string name = {};
    const char* invalid[] = {"", "/file", "../file", "a/../file", "a/./b",
        "a//b",
                             "a/", "a b", "a:b", ".", "..", "a\\..\\b",
                             "a\x01b"};

    expect(i76_resource_normalize_name("PATH\\MiXeD.GEO",
        name) == i76_resource_result::ok &&
               name == "path/mixed.geo", "portable logical normalization");
    for (const char* entry : invalid) {
        expect(i76_resource_normalize_name(entry,
            name) == i76_resource_result::invalid_argument &&
                   name.empty(), "reject invalid path");
    }
    expect(i76_resource_normalize_name(std::string(256U, 'a'), name) ==
               i76_resource_result::invalid_argument,
                   "reject long resource name");
    expect(i76_resource_normalize_name("a/.hidden",
        name) == i76_resource_result::ok,
           "legitimate dotted filename");
}

// -----------------------------------------------------------------------------
// Verify cache sharing, resource leases, and stale handle behavior.
// -----------------------------------------------------------------------------
static void test_memory_and_lifetime()
{
    i76_resource_store store = {};
    i76_resource_handle first = {};
    i76_resource_handle repeated = {};
    i76_resource_handle newer = {};
    i76_resource_stats stats = {};
    const i76_resource_entry* entry = nullptr;
    const std::uint8_t bytes[] = {'a','b','c'};
    const std::uint8_t replacement[] = {'z'};

    expect(!store.initialized && store.mounts.empty() && store.entries.empty(),
           "zero initialized resource store");
    expect(i76_resource_shutdown(store) == i76_resource_result::not_initialized,
           "shutdown before initialize");
    expect(i76_resource_acquire(store, "hi", first) ==
        i76_resource_result::not_initialized &&
               first.slot == 0U, "acquire before initialize");
    expect(i76_resource_initialize(store) == i76_resource_result::ok,
        "initialize store");
    expect(i76_resource_initialize(store) ==
        i76_resource_result::already_initialized,
           "duplicate initialization rejected");
    expect(i76_resource_add_memory(store, "missing", "item.dat", bytes) ==
               i76_resource_result::not_found, "unknown memory mount rejected");
    expect(i76_resource_mount_memory(store, "base") == i76_resource_result::ok,
        "mount memory");
    expect(i76_resource_mount_memory(store, "base") ==
        i76_resource_result::invalid_argument,
           "duplicate memory mount rejected");
    expect(i76_resource_add_memory(store, "base", "Item.DAT", bytes) ==
               i76_resource_result::ok, "add resource");
    expect(i76_resource_add_memory(store, "base", "item.dat", bytes) ==
               i76_resource_result::invalid_argument,
                   "duplicate normalized key rejected");
    expect(i76_resource_add_memory(store, "base", "../bad", bytes) ==
               i76_resource_result::invalid_argument,
                   "invalid memory key rejected");
    expect(i76_resource_acquire(store, "NOT-HERE", first) ==
        i76_resource_result::not_found &&
               first.slot == 0U, "missing name rejected without handle");
    expect(i76_resource_acquire(store, "ITEM.dat", first) ==
        i76_resource_result::ok,
           "acquire mixed-case key");
    expect(first.slot == 1U && first.generation == 1U,
        "initial cache identity");
    entry = i76_resource_lookup(store, first);
    expect(entry != nullptr && entry->bytes.size() == 3U && entry->bytes[1] ==
        'b' &&
               entry->source == "base", "bytes and source provenance");
    expect(i76_resource_acquire(store, "item.dat", repeated) ==
        i76_resource_result::ok &&
               repeated.slot == first.slot && repeated.generation ==
                   first.generation,
           "shared decoded byte lease");
    stats = i76_resource_get_stats(store);
    expect(stats.mount_count == 1U && stats.cached_count == 1U &&
        stats.cached_bytes == 3U &&
               stats.references == 2U, "reference stats");
    expect(i76_resource_shutdown(store) == i76_resource_result::busy,
           "cannot shutdown with outstanding leases");
    expect(i76_resource_release(store, first) == i76_resource_result::ok &&
               i76_resource_lookup(store, repeated) != nullptr,
                   "release one reference");
    expect(i76_resource_release(store, repeated) == i76_resource_result::ok &&
               i76_resource_lookup(store, first) == nullptr,
                   "last release invalidates handle");
    expect(i76_resource_release(store, first) ==
        i76_resource_result::invalid_argument,
           "stale release rejected");
    expect(i76_resource_release(store,
        {}) == i76_resource_result::invalid_argument,
           "zero handle rejected");
    expect(i76_resource_get_stats(store).cached_count == 0U,
           "cache eviction after last reference");
    expect(i76_resource_mount_memory(store, "overlay") ==
        i76_resource_result::ok,
           "add higher priority mount");
    expect(i76_resource_add_memory(store, "overlay", "item.dat", replacement) ==
               i76_resource_result::ok, "add overriding name");
    expect(i76_resource_acquire(store, "item.dat", newer) ==
        i76_resource_result::ok &&
               newer.generation > first.generation, "reacquire new generation");
    entry = i76_resource_lookup(store, newer);
    expect(entry != nullptr && entry->source == "overlay" && entry->bytes[0] ==
        'z',
           "newest mount wins uncached lookup");
    expect(i76_resource_release(store, newer) == i76_resource_result::ok,
           "release replacement");
    expect(i76_resource_shutdown(store) == i76_resource_result::ok &&
               !store.initialized && store.mounts.empty(),
                   "shutdown releases mounts");
    expect(i76_resource_initialize(store) == i76_resource_result::ok &&
               i76_resource_mount_memory(store, "again") ==
                   i76_resource_result::ok,
           "reinitialize and mount");
    expect(i76_resource_add_memory(store, "again", "item.dat", replacement) ==
               i76_resource_result::ok &&
               i76_resource_acquire(store, "item.dat", newer) ==
                   i76_resource_result::ok &&
               newer.generation > repeated.generation,
                   "generation survives shutdown");
    expect(i76_resource_release(store, newer) == i76_resource_result::ok &&
               i76_resource_shutdown(store) == i76_resource_result::ok,
                   "final cleanup");
}

// -----------------------------------------------------------------------------
// Verify mount IDs and retention semantics across unmount attempts.
// -----------------------------------------------------------------------------
static void test_unmount_identity_and_leases()
{
    i76_resource_store store = {};
    i76_resource_handle old_handle = {};
    i76_resource_handle new_handle = {};
    const i76_resource_entry* entry = nullptr;
    const std::uint8_t first[] = {'a'};
    const std::uint8_t second[] = {'b'};
    std::uint64_t overlay_id = 0;
    std::uint64_t first_id = 0;

    expect(i76_resource_unmount(store,
        1U) == i76_resource_result::not_initialized,
           "unmount needs initialized store");
    expect(i76_resource_initialize(store) == i76_resource_result::ok,
        "unmount test init");
    expect(i76_resource_unmount(store,
        0U) == i76_resource_result::invalid_argument,
           "zero mount id rejected");
    expect(i76_resource_unmount(store, 1000U) == i76_resource_result::not_found,
           "unknown mount id rejected");
    expect(i76_resource_mount_memory(store, "base") == i76_resource_result::ok,
           "first mount");
    first_id = store.mounts.back().id;
    expect(first_id != 0U && i76_resource_add_memory(store, "base", "a.dat",
        first) ==
               i76_resource_result::ok, "first stable mount id");
    expect(i76_resource_mount_memory(store, "overlay") ==
        i76_resource_result::ok,
           "second mount");
    overlay_id = store.mounts.back().id;
    expect(overlay_id > first_id, "mount ids monotonically increase");
    expect(i76_resource_add_memory(store, "overlay", "a.dat", second) ==
               i76_resource_result::ok, "overlay file");
    expect(i76_resource_acquire(store, "a.dat", old_handle) ==
        i76_resource_result::ok,
           "acquire overriding resource");
    entry = i76_resource_lookup(store, old_handle);
    expect(entry != nullptr && entry->source_mount_id == overlay_id &&
               entry->bytes.front() == 'b',
                   "leases associate with exact source mount id");
    expect(i76_resource_unmount(store, overlay_id) == i76_resource_result::busy
        &&
               store.mounts.size() == 2U, "cannot unmount retained resource");
    expect(i76_resource_unmount(store, first_id) == i76_resource_result::ok &&
               store.mounts.size() == 1U && store.mounts.front().id ==
                   overlay_id,
           "unmount independent idle mount without shifting ids");
    expect(i76_resource_release(store, old_handle) == i76_resource_result::ok,
           "release allows unmount");
    expect(i76_resource_unmount(store, overlay_id) == i76_resource_result::ok &&
               store.mounts.empty(), "unmount after lease release");
    expect(i76_resource_acquire(store, "a.dat", new_handle) ==
               i76_resource_result::not_found,
                   "removed mount is no longer visible");
    expect(i76_resource_mount_memory(store, "base") == i76_resource_result::ok
        &&
               store.mounts.back().id > overlay_id,
                   "remount never reuses mount ID");
    expect(i76_resource_add_memory(store, "base", "a.dat", first) ==
               i76_resource_result::ok &&
               i76_resource_acquire(store, "a.dat", new_handle) ==
               i76_resource_result::ok && new_handle.generation >
                   old_handle.generation,
           "remounted resource has fresh lease identity");
    expect(i76_resource_release(store, new_handle) == i76_resource_result::ok &&
               i76_resource_shutdown(store) == i76_resource_result::ok,
           "unmount test shutdown");
    expect(i76_resource_initialize(store) == i76_resource_result::ok &&
               i76_resource_mount_memory(store, "after_shutdown") ==
               i76_resource_result::ok && store.mounts.back().id > overlay_id,
           "mount ID history survives reinitialize");
    expect(i76_resource_shutdown(store) == i76_resource_result::ok,
        "final release");
    expect(i76_resource_initialize(store) == i76_resource_result::ok,
           "initialize for mount ID overflow test");
    store.last_mount_id = std::numeric_limits<std::uint64_t>::max();
    expect(i76_resource_mount_memory(store, "overflow") ==
               i76_resource_result::capacity_exceeded && store.mounts.empty(),
           "mount ID overflow rejected without mutation");
    expect(i76_resource_shutdown(store) == i76_resource_result::ok,
           "shutdown after overflow rejection");
}

// -----------------------------------------------------------------------------
// Verify directory resource lookup and safe path resolution.
// -----------------------------------------------------------------------------
static void test_directory()
{
    i76_resource_store store = {};
    i76_resource_handle handle = {};
    const i76_resource_entry* entry = nullptr;
    std::filesystem::path root = std::filesystem::temp_directory_path() /
        "i76_resource_test_1";
    std::filesystem::path outside = std::filesystem::temp_directory_path() /
        "i76_resource_test_outside";
    std::error_code error = {};
    std::ofstream stream = {};

    std::filesystem::remove_all(root, error);
    std::filesystem::create_directories(root / "sub", error);
    expect(!error, "create local provider fixture");
    stream.open(root / "sub" / "scene.level", std::ios::binary);
    stream << "abc";
    stream.close();
    stream.open(outside, std::ios::binary);
    stream << "private";
    stream.close();
    expect(i76_resource_initialize(store) == i76_resource_result::ok,
        "directory store init");
    expect(i76_resource_mount_directory(store, "/unlikely-i76-missing-path") ==
               i76_resource_result::invalid_argument,
                   "reject absent directory");
    expect(i76_resource_mount_directory(store, root.string()) ==
        i76_resource_result::ok,
           "mount directory");
    expect(i76_resource_mount_directory(store, root.string()) ==
               i76_resource_result::invalid_argument,
                   "reject duplicate directory mount");
    expect(i76_resource_acquire(store, "sub/scene.level", handle) ==
        i76_resource_result::ok,
           "read directory file");
    entry = i76_resource_lookup(store, handle);
    expect(entry != nullptr && entry->bytes.size() == 3U && entry->bytes[2] ==
        'c',
           "directory data and length");
    expect(i76_resource_release(store, handle) == i76_resource_result::ok,
           "release directory file");
    expect(i76_resource_acquire(store, "sub/unknown", handle) ==
               i76_resource_result::not_found, "missing file is reported");
    expect(i76_resource_acquire(store, "../i76_resource_test_outside",
        handle) ==
               i76_resource_result::invalid_argument, "traversal rejected");
    std::filesystem::create_symlink(outside, root / "link.dat", error);
    if (!error) {
        expect(i76_resource_acquire(store, "link.dat", handle) ==
                   i76_resource_result::invalid_argument,
               "symlink cannot escape mounted root");
    }
    expect(i76_resource_shutdown(store) == i76_resource_result::ok,
        "directory shutdown");
    std::filesystem::remove_all(root, error);
    std::filesystem::remove(outside, error);
}

// -----------------------------------------------------------------------------
// Run the test suite or produce a fixture for functional tests.
// -----------------------------------------------------------------------------
int main()
{
    test_normalize();
    test_memory_and_lifetime();
    test_unmount_identity_and_leases();
    test_directory();
    return failures == 0U ? 0 : 1;
}
