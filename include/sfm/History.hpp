#pragma once

#include <filesystem>
#include <map>

#include "sfm/window/info/DirInfo.hpp"


namespace fs = std::filesystem;

class History
{
private:
        struct Cookie
        {
                fs::path path {};
                size_t offset {};
        };

        std::map<fs::path, Cookie> tracker {};
public:
        void saveState(const fs::path&, const fs::path&, const size_t&) noexcept;
        void restoreState(const fs::path&, const fs::path&, DirInfo&) noexcept;
};
