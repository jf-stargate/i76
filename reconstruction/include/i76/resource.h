#pragma once

#include <cstddef>
#include <cstdint>
#include <span>
#include <string>
#include <string_view>
#include <vector>

// Resource IDs are runtime identities, not retail cache-record pointers or names.
struct i76_resource_handle {
    std::uint32_t slot{};
    std::uint64_t generation{};
};

enum class i76_resource_result : std::uint8_t {
    ok = 0,
    already_initialized,
    not_initialized,
    invalid_argument,
    not_found,
    busy,
    too_large,
    io_error,
    capacity_exceeded,
};

enum class i76_resource_provider_kind : std::uint8_t {
    memory = 0,
    directory,
};

struct i76_resource_file {
    std::string name{};
    std::vector<std::uint8_t> bytes{};
};

struct i76_resource_mount {
    i76_resource_provider_kind kind{};
    std::string name{};
    std::string root{};
    std::vector<i76_resource_file> files{};
};

struct i76_resource_entry {
    bool occupied{};
    i76_resource_handle handle{};
    std::string name{};
    std::string source{};
    std::vector<std::uint8_t> bytes{};
    std::uint32_t references{};
};

struct i76_resource_store {
    bool initialized{};
    std::uint64_t last_generation{};
    std::vector<i76_resource_mount> mounts{};
    std::vector<i76_resource_entry> entries{};
};

struct i76_resource_stats {
    std::size_t mount_count{};
    std::size_t cached_count{};
    std::size_t cached_bytes{};
    std::uint64_t references{};
};

inline constexpr std::size_t i76_resource_max_bytes = 16U * 1024U * 1024U;
inline constexpr std::size_t i76_resource_max_mounts = 32U;
inline constexpr std::size_t i76_resource_max_cache_entries = 4096U;
inline constexpr std::size_t i76_resource_max_name_length = 255U;

i76_resource_result i76_resource_initialize(i76_resource_store& store) noexcept;
i76_resource_result i76_resource_shutdown(i76_resource_store& store) noexcept;
i76_resource_result i76_resource_mount_memory(i76_resource_store& store, std::string_view name);
i76_resource_result i76_resource_mount_directory(i76_resource_store& store, std::string_view path);
i76_resource_result i76_resource_add_memory(i76_resource_store& store, std::string_view mount,
                                             std::string_view name,
                                             std::span<const std::uint8_t> bytes);
i76_resource_result i76_resource_acquire(i76_resource_store& store, std::string_view name,
                                          i76_resource_handle& handle);
i76_resource_result i76_resource_release(i76_resource_store& store,
                                          i76_resource_handle handle) noexcept;
const i76_resource_entry* i76_resource_lookup(const i76_resource_store& store,
                                              i76_resource_handle handle) noexcept;
i76_resource_stats i76_resource_get_stats(const i76_resource_store& store) noexcept;
// Lowercase ASCII keys; never accept absolute paths, traversal or empty segments.
i76_resource_result i76_resource_normalize_name(std::string_view name, std::string& normalized);
