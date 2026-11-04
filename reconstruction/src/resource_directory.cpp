#include "i76/resource.h"

#include <filesystem>
#include <fstream>
#include <system_error>

// Platform filesystem operations are deliberately confined to this provider.
static bool is_within(const std::filesystem::path& root,
                      const std::filesystem::path& candidate)
{
    std::filesystem::path::const_iterator left = root.begin();
    std::filesystem::path::const_iterator right = candidate.begin();

    while (left != root.end()) {
        if (right == candidate.end() || *left != *right) {
            return false;
        }
        ++left;
        ++right;
    }
    return true;
}

i76_resource_result i76_resource_directory_validate(std::string_view path, std::string& root)
{
    std::error_code error = {};
    std::filesystem::path directory = {};

    root.clear();
    if (path.empty()) {
        return i76_resource_result::invalid_argument;
    }
    directory = std::filesystem::canonical(std::filesystem::path(std::string(path)), error);
    if (error || !std::filesystem::is_directory(directory, error) || error) {
        return i76_resource_result::invalid_argument;
    }
    root = directory.string();
    return i76_resource_result::ok;
}

i76_resource_result i76_resource_directory_read(const std::string& root, const std::string& name,
                                                 std::vector<std::uint8_t>& bytes)
{
    std::error_code error = {};
    std::filesystem::path root_path = {};
    std::filesystem::path candidate = {};
    std::uintmax_t count = 0;
    std::ifstream stream = {};
    std::streamsize requested = 0;

    bytes.clear();
    root_path = std::filesystem::path(root);
    candidate = std::filesystem::weakly_canonical(root_path / std::filesystem::path(name), error);
    if (error || !is_within(root_path, candidate)) {
        return i76_resource_result::invalid_argument;
    }
    error.clear();
    if (!std::filesystem::is_regular_file(candidate, error)) {
        if (!error || error == std::errc::no_such_file_or_directory) {
            return i76_resource_result::not_found;
        }
        return i76_resource_result::io_error;
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
