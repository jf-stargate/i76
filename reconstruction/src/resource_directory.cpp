#include "i76/resource.h"

#include <filesystem>
#include <fstream>
#include <system_error>

// Platform filesystem operations are deliberately confined to this provider.

// -----------------------------------------------------------------------------
// Check that a resolved filesystem path remains below its mount root.
// -----------------------------------------------------------------------------
static bool is_within(const std::filesystem::path& root,
                      const std::filesystem::path& candidate)
{
    std::filesystem::path::const_iterator left = root.begin();
    std::filesystem::path::const_iterator right = candidate.begin();

    while (left != root.end()) {
        if (right == candidate.end()
            || *left != *right) {
            return false;
        }
        ++left;
        ++right;
    }
    return true;
}

// -----------------------------------------------------------------------------
// Resolve and validate a directory mount root.
// -----------------------------------------------------------------------------
i76_resource_result i76_resource_directory_validate(std::string_view path,
    std::string& root)
{
    std::error_code error = {};
    std::filesystem::path directory = {};

    root.clear();
    if (path.empty()) {
        return i76_resource_result::invalid_argument;
    }
    directory = std::filesystem::canonical(
        std::filesystem::path(std::string(path)), error);
    if (error
        || !std::filesystem::is_directory(directory, error)
        || error) {
        return i76_resource_result::invalid_argument;
    }
    root = directory.string();
    return i76_resource_result::ok;
}

// Legacy installations commonly have uppercase filenames. On case-sensitive
// filesystems, try a deterministic ASCII case-folded component lookup only when
// the literal normalized (lowercase) path does not exist. Ambiguity is an
// error.

// -----------------------------------------------------------------------------
// Compare ASCII filenames ignoring case for retail assets.
// -----------------------------------------------------------------------------
static bool ascii_case_match(const std::string& filename,
                             const std::string& expected) noexcept
{
    std::size_t index = 0;
    char character = 0;

    if (filename.size() != expected.size()) {
        return false;
    }
    for (index = 0; index < filename.size(); ++index) {
        character = filename[index];
        if (character >= 'A'
            && character <= 'Z') {
            character = static_cast<char>(character - 'A' + 'a');
        }
        if (character != expected[index]) {
            return false;
        }
    }
    return true;
}

// -----------------------------------------------------------------------------
// Resolve legacy filename casing without permitting path escapes.
// -----------------------------------------------------------------------------
static i76_resource_result find_casefolded(const std::filesystem::path& root,
                                           const std::string& name,
                                           std::filesystem::path& resolved)
{
    std::filesystem::path candidate = root;
    std::filesystem::path matching = {};
    std::filesystem::path component_path = {};
    std::string component = {};
    std::error_code error = {};
    std::filesystem::directory_iterator iterator = {};
    std::filesystem::directory_iterator end = {};
    bool found = false;

    for (const std::filesystem::path& part : std::filesystem::path(name)) {
        component = part.string();
        component_path = candidate / part;
        error.clear();
        if (!std::filesystem::exists(component_path, error)
            && !error) {
            found = false;
            iterator = std::filesystem::directory_iterator(candidate, error);
            if (error) {
                return error == std::errc::no_such_file_or_directory ?
                           i76_resource_result::not_found :
                           i76_resource_result::io_error;
            }
            while (iterator != end) {
                if (ascii_case_match(iterator->path().filename().string(),
                    component)) {
                    if (found) {
                        // ambiguous legacy spelling
                        return i76_resource_result::io_error;
                    }
                    matching = iterator->path();
                    found = true;
                }
                iterator.increment(error);
                if (error) {
                    return i76_resource_result::io_error;
                }
            }
            if (!found) {
                return i76_resource_result::not_found;
            }
            component_path = matching;
        } else if (error) {
            return i76_resource_result::io_error;
        }
        candidate = std::filesystem::weakly_canonical(component_path, error);
        if (error
            || !is_within(root, candidate)) {
            return i76_resource_result::invalid_argument;
        }
    }
    resolved = candidate;
    return i76_resource_result::ok;
}

// -----------------------------------------------------------------------------
// Read a bounded resource file from a validated mount.
// -----------------------------------------------------------------------------
i76_resource_result i76_resource_directory_read(const std::string& root,
    const std::string& name,
    std::vector<std::uint8_t>& bytes)
{
    std::error_code error = {};
    std::filesystem::path root_path = {};
    std::filesystem::path candidate = {};
    std::uintmax_t count = 0;
    std::ifstream stream = {};
    std::streamsize requested = 0;
    i76_resource_result result = i76_resource_result::ok;

    bytes.clear();
    root_path = std::filesystem::path(root);
    candidate = std::filesystem::weakly_canonical(root_path /
        std::filesystem::path(name), error);
    if (error
        || !is_within(root_path, candidate)) {
        return i76_resource_result::invalid_argument;
    }
    error.clear();
    if (!std::filesystem::is_regular_file(candidate, error)) {
        if (error
            && error != std::errc::no_such_file_or_directory) {
            return i76_resource_result::io_error;
        }
        result = find_casefolded(root_path, name, candidate);
        if (result != i76_resource_result::ok) {
            return result;
        }
        error.clear();
        if (!std::filesystem::is_regular_file(candidate, error)
            || error) {
            return error ? i76_resource_result::io_error :
                i76_resource_result::not_found;
        }
    }
    count = std::filesystem::file_size(candidate, error);
    if (error) {
        return i76_resource_result::io_error;
    }
    if (count > i76_resource_max_bytes) {
        return i76_resource_result::too_large;
    }
    stream.open(candidate, std::ios::binary);
    if (!stream) {
        return i76_resource_result::io_error;
    }
    bytes.resize(static_cast<std::size_t>(count));
    requested = static_cast<std::streamsize>(count);
    if (requested != 0) {
        stream.read(reinterpret_cast<char*>(bytes.data()), requested);
        if (stream.gcount() != requested) {
            bytes.clear();
            return i76_resource_result::io_error;
        }
    }
    return i76_resource_result::ok;
}
