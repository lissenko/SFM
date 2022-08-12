#pragma once

#include <filesystem>

namespace fs = std::filesystem;

/*
 * This class extracts characteristics of the files to be displayed. Unlike
 * FileHandler, it only deals with visible elements and has no influence on the
 * filesystem.
 */
class FileDecorator
{
private:
        /*
         * Convert a number of bytes into a human readable format.
         */
        const std::string humandReadable(const uintmax_t&) const;
public:
        const std::string extractCharacteristic(const fs::directory_entry&) const noexcept;
};
