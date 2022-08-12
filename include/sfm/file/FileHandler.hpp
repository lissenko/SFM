#pragma once

#include <filesystem>
#include <vector>

#include "sfm/file/FileDecorator.hpp"

namespace fs = std::filesystem;

class FileHandler
{
        FileDecorator fileDecorator {};
private:
        static bool isDir(const fs::directory_entry&);
public:
        size_t populate(const fs::path&, std::vector<fs::directory_entry>&, std::vector<std::string>&, bool) const noexcept;
        void remove(const fs::path&) const noexcept;
        void rename(const fs::path&, const fs::path&) const noexcept;
};
