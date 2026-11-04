#include "i76/resource.h"

#include <limits>
#include <utility>

// Defined by the optional-in-practice but always compiled directory provider.
i76_resource_result i76_resource_directory_validate(std::string_view path,
    std::string& root);
i76_resource_result i76_resource_directory_read(const std::string& root,
    const std::string& name,
                                                 std::vector<std::uint8_t>&
                                                 bytes);

// -----------------------------------------------------------------------------
// Find a live resource lease by generation-checked handle.
// -----------------------------------------------------------------------------
static const i76_resource_entry* lookup_entry(const i76_resource_store& store,
    i76_resource_handle handle) noexcept
{
    const i76_resource_entry* entry = nullptr;

    if (!store.initialized || handle.slot == 0U || handle.generation == 0U ||
        handle.slot > store.entries.size()) {
        return nullptr;
    }
    entry = &store.entries[handle.slot - 1U];
    return entry->occupied && entry->handle.generation == handle.generation ?
        entry : nullptr;
}

// -----------------------------------------------------------------------------
// Normalize a logical resource name and reject unsafe paths.
// -----------------------------------------------------------------------------
i76_resource_result i76_resource_normalize_name(std::string_view name,
    std::string& normalized)
{
    std::size_t index = 0;
    char character = 0;
    bool segment_start = true;

    normalized.clear();
    if (name.empty() || name.size() > i76_resource_max_name_length) {
        return i76_resource_result::invalid_argument;
    }
    normalized.reserve(name.size());
    for (index = 0; index < name.size(); ++index) {
        character = name[index];
        if (character == '\\') {
            character = '/';
        }
        if (character == '/') {
            if (segment_start || index + 1U == name.size()) {
                normalized.clear();
                return i76_resource_result::invalid_argument;
            }
            segment_start = true;
        } else {
            if (!((character >= 'a' && character <= 'z') ||
                  (character >= 'A' && character <= 'Z') ||
                  (character >= '0' && character <= '9') || character == '_' ||
                  character == '-' || character == '.')) {
                normalized.clear();
                return i76_resource_result::invalid_argument;
            }
            if (character >= 'A' && character <= 'Z') {
                character = static_cast<char>(character - 'A' + 'a');
            }
            segment_start = false;
        }
        normalized.push_back(character);
    }
    if (normalized == "." || normalized == ".." ||
        normalized.find("/../") != std::string::npos ||
        normalized.find("/./") != std::string::npos ||
        normalized.starts_with("../") || normalized.starts_with("./") ||
        normalized.ends_with("/..") || normalized.ends_with("/.")) {
        normalized.clear();
        return i76_resource_result::invalid_argument;
    }
    return i76_resource_result::ok;
}

// -----------------------------------------------------------------------------
// Initialize the resource store while retaining generation history.
// -----------------------------------------------------------------------------
i76_resource_result i76_resource_initialize(i76_resource_store& store) noexcept
{
    if (store.initialized) {
        return i76_resource_result::already_initialized;
    }
    store.initialized = true;
    return i76_resource_result::ok;
}

// -----------------------------------------------------------------------------
// Release resource storage after all outstanding leases end.
// -----------------------------------------------------------------------------
i76_resource_result i76_resource_shutdown(i76_resource_store& store) noexcept
{
    std::size_t index = 0;
    std::vector<i76_resource_entry> empty_entries = {};
    std::vector<i76_resource_mount> empty_mounts = {};

    if (!store.initialized) {
        return i76_resource_result::not_initialized;
    }
    for (index = 0; index < store.entries.size(); ++index) {
        if (store.entries[index].occupied) {
            return i76_resource_result::busy;
        }
    }
    store.entries.swap(empty_entries);
    store.mounts.swap(empty_mounts);
    store.initialized = false;
    return i76_resource_result::ok;
}

// -----------------------------------------------------------------------------
// Mount a named memory-backed resource provider.
// -----------------------------------------------------------------------------
i76_resource_result i76_resource_mount_memory(i76_resource_store& store,
    std::string_view name)
{
    std::size_t index = 0;
    i76_resource_mount mount = {};

    if (!store.initialized) {
        return i76_resource_result::not_initialized;
    }
    if (name.empty() || name.size() > i76_resource_max_name_length) {
        return i76_resource_result::invalid_argument;
    }
    if (store.mounts.size() >= i76_resource_max_mounts ||
        store.last_mount_id == std::numeric_limits<std::uint64_t>::max()) {
        return i76_resource_result::capacity_exceeded;
    }
    for (index = 0; index < store.mounts.size(); ++index) {
        if (store.mounts[index].name == name) {
            return i76_resource_result::invalid_argument;
        }
    }
    mount.name = name;
    mount.kind = i76_resource_provider_kind::memory;
    mount.id = store.last_mount_id + 1U;
    store.mounts.push_back(std::move(mount));
    ++store.last_mount_id;
    return i76_resource_result::ok;
}

// -----------------------------------------------------------------------------
// Validate and mount a directory-backed resource provider.
// -----------------------------------------------------------------------------
i76_resource_result i76_resource_mount_directory(i76_resource_store& store,
    std::string_view path)
{
    std::string root = {};
    std::size_t index = 0;
    i76_resource_mount mount = {};
    i76_resource_result status = i76_resource_result::ok;

    if (!store.initialized) {
        return i76_resource_result::not_initialized;
    }
    if (store.mounts.size() >= i76_resource_max_mounts ||
        store.last_mount_id == std::numeric_limits<std::uint64_t>::max()) {
        return i76_resource_result::capacity_exceeded;
    }
    status = i76_resource_directory_validate(path, root);
    if (status != i76_resource_result::ok) {
        return status;
    }
    for (index = 0; index < store.mounts.size(); ++index) {
        if (store.mounts[index].kind == i76_resource_provider_kind::directory &&
            store.mounts[index].root == root) {
            return i76_resource_result::invalid_argument;
        }
    }
    mount.kind = i76_resource_provider_kind::directory;
    mount.id = store.last_mount_id + 1U;
    mount.name = root;
    mount.root = std::move(root);
    store.mounts.push_back(std::move(mount));
    ++store.last_mount_id;
    return i76_resource_result::ok;
}

// -----------------------------------------------------------------------------
// Remove an idle resource mount without invalidating other IDs.
// -----------------------------------------------------------------------------
i76_resource_result i76_resource_unmount(i76_resource_store& store,
                                         std::uint64_t mount_id) noexcept
{
    std::size_t index = 0;
    std::size_t entry_index = 0;

    if (!store.initialized) {
        return i76_resource_result::not_initialized;
    }
    if (mount_id == 0U) {
        return i76_resource_result::invalid_argument;
    }
    for (index = 0; index < store.mounts.size(); ++index) {
        if (store.mounts[index].id != mount_id) {
            continue;
        }
        for (entry_index = 0; entry_index < store.entries.size(); ++entry_index)
            {
            if (store.entries[entry_index].occupied &&
                store.entries[entry_index].source_mount_id == mount_id) {
                return i76_resource_result::busy;
            }
        }
        store.mounts.erase(store.mounts.begin() +
            static_cast<std::ptrdiff_t>(index));
        return i76_resource_result::ok;
    }
    return i76_resource_result::not_found;
}

// -----------------------------------------------------------------------------
// Resolve an existing mount by ID-independent name or path.
// -----------------------------------------------------------------------------
i76_resource_result i76_resource_find_mount(const i76_resource_store& store,
    std::string_view name,
    std::uint64_t& mount_id)
{
    std::string root = {};
    std::size_t index = 0;
    std::uint64_t found_id = 0;
    i76_resource_result status = i76_resource_result::ok;

    mount_id = 0U;
    if (!store.initialized) {
        return i76_resource_result::not_initialized;
    }
    if (name.empty()) {
        return i76_resource_result::invalid_argument;
    }
    // Match the printed mount name first; canonicalize directory aliases only
    // when a literal name is not present. Windows may normalize path spelling.
    for (index = 0; index < store.mounts.size(); ++index) {
        if (store.mounts[index].name == name) {
            if (found_id != 0U) {
                return i76_resource_result::invalid_argument;
            }
            found_id = store.mounts[index].id;
        }
    }
    if (found_id == 0U) {
        status = i76_resource_directory_validate(name, root);
        if (status == i76_resource_result::ok) {
            for (index = 0; index < store.mounts.size(); ++index) {
                if (store.mounts[index].kind ==
                    i76_resource_provider_kind::directory &&
                    store.mounts[index].root == root) {
                    found_id = store.mounts[index].id;
                    break;
                }
            }
        }
    }
    if (found_id == 0U) {
        return i76_resource_result::not_found;
    }
    mount_id = found_id;
    return i76_resource_result::ok;
}

// -----------------------------------------------------------------------------
// Register a bounded in-memory file in the selected mount.
// -----------------------------------------------------------------------------
i76_resource_result i76_resource_add_memory(i76_resource_store& store,
    std::string_view mount,
    std::string_view name,
    std::span<const std::uint8_t> bytes)
{
    std::size_t index = 0;
    std::size_t file_index = 0;
    std::string key = {};
    i76_resource_result status = i76_resource_result::ok;
    i76_resource_file file = {};

    if (!store.initialized) {
        return i76_resource_result::not_initialized;
    }
    status = i76_resource_normalize_name(name, key);
    if (status != i76_resource_result::ok || bytes.size() >
        i76_resource_max_bytes) {
        return i76_resource_result::invalid_argument;
    }
    for (index = 0; index < store.mounts.size(); ++index) {
        if (store.mounts[index].kind != i76_resource_provider_kind::memory ||
            store.mounts[index].name != mount) {
            continue;
        }
        for (file_index = 0; file_index < store.mounts[index].files.size();
            ++file_index) {
            if (store.mounts[index].files[file_index].name == key) {
                return i76_resource_result::invalid_argument;
            }
        }
        file.name = key;
        file.bytes.assign(bytes.begin(), bytes.end());
        store.mounts[index].files.push_back(std::move(file));
        return i76_resource_result::ok;
    }
    return i76_resource_result::not_found;
}

// -----------------------------------------------------------------------------
// Find or cache resource bytes and issue a counted lease.
// -----------------------------------------------------------------------------
i76_resource_result i76_resource_acquire(i76_resource_store& store,
                                         std::string_view name,
                                         i76_resource_handle& handle)
{
    std::string key = {};
    i76_resource_result status = i76_resource_result::ok;
    std::size_t index = 0;
    std::size_t source_index = 0;
    std::size_t file_index = 0;
    std::size_t selected_slot = 0;
    bool found = false;
    i76_resource_entry entry = {};
    i76_resource_handle new_handle = {};
    std::vector<std::uint8_t> bytes = {};
    std::string source = {};
    std::uint64_t source_mount_id = 0;

    handle = {};
    if (!store.initialized) {
        return i76_resource_result::not_initialized;
    }
    status = i76_resource_normalize_name(name, key);
    if (status != i76_resource_result::ok) {
        return status;
    }
    for (index = 0; index < store.entries.size(); ++index) {
        if (store.entries[index].occupied && store.entries[index].name == key) {
            if (store.entries[index].references ==
                std::numeric_limits<std::uint32_t>::max()) {
                return i76_resource_result::capacity_exceeded;
            }
            ++store.entries[index].references;
            handle = store.entries[index].handle;
            return i76_resource_result::ok;
        }
    }
    if (store.last_generation == std::numeric_limits<std::uint64_t>::max()) {
        return i76_resource_result::capacity_exceeded;
    }
    for (source_index = store.mounts.size(); source_index != 0U; --source_index)
        {
        const i76_resource_mount& mount = store.mounts[source_index - 1U];
        if (mount.kind == i76_resource_provider_kind::memory) {
            for (file_index = 0; file_index < mount.files.size(); ++file_index)
                {
                if (mount.files[file_index].name == key) {
                    bytes = mount.files[file_index].bytes;
                    source = mount.name;
                    source_mount_id = mount.id;
                    found = true;
                    break;
                }
            }
        } else {
            status = i76_resource_directory_read(mount.root, key, bytes);
            if (status == i76_resource_result::ok) {
                source = mount.name;
                source_mount_id = mount.id;
                found = true;
            } else if (status != i76_resource_result::not_found) {
                return status;
            }
        }
        if (found) {
            break;
        }
    }
    if (!found) {
        return i76_resource_result::not_found;
    }
    selected_slot = store.entries.size();
    for (index = 0; index < store.entries.size(); ++index) {
        if (!store.entries[index].occupied) {
            selected_slot = index;
            break;
        }
    }
    if (selected_slot >= i76_resource_max_cache_entries) {
        return i76_resource_result::capacity_exceeded;
    }
    new_handle.slot = static_cast<std::uint32_t>(selected_slot + 1U);
    new_handle.generation = store.last_generation + 1U;
    entry.occupied = true;
    entry.handle = new_handle;
    entry.name = std::move(key);
    entry.source = std::move(source);
    entry.source_mount_id = source_mount_id;
    entry.bytes = std::move(bytes);
    entry.references = 1U;
    if (selected_slot == store.entries.size()) {
        store.entries.push_back(std::move(entry));
    } else {
        store.entries[selected_slot] = std::move(entry);
    }
    store.last_generation = new_handle.generation;
    handle = new_handle;
    return i76_resource_result::ok;
}

// -----------------------------------------------------------------------------
// Release a resource lease without reviving stale handles.
// -----------------------------------------------------------------------------
i76_resource_result i76_resource_release(i76_resource_store& store,
                                         i76_resource_handle handle) noexcept
{
    std::size_t index = 0;

    if (!store.initialized) {
        return i76_resource_result::not_initialized;
    }
    if (lookup_entry(store, handle) == nullptr) {
        return i76_resource_result::invalid_argument;
    }
    index = handle.slot - 1U;
    --store.entries[index].references;
    if (store.entries[index].references == 0U) {
        store.entries[index] = {};
    }
    return i76_resource_result::ok;
}

// -----------------------------------------------------------------------------
// Return the cached bytes for a live generation-checked lease.
// -----------------------------------------------------------------------------
const i76_resource_entry* i76_resource_lookup(const i76_resource_store& store,
    i76_resource_handle handle) noexcept
{
    return lookup_entry(store, handle);
}

// -----------------------------------------------------------------------------
// Summarize current mounts, cached entries, and byte leases.
// -----------------------------------------------------------------------------
i76_resource_stats i76_resource_get_stats(const i76_resource_store& store
                                          ) noexcept
{
    i76_resource_stats stats = {};
    std::size_t index = 0;

    if (!store.initialized) {
        return stats;
    }
    stats.mount_count = store.mounts.size();
    for (index = 0; index < store.entries.size(); ++index) {
        if (store.entries[index].occupied) {
            ++stats.cached_count;
            stats.cached_bytes += store.entries[index].bytes.size();
            stats.references += store.entries[index].references;
        }
    }
    return stats;
}
