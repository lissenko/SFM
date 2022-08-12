#pragma once

#include "Config.hpp"
#include "sfm/window/info/DirInfo.hpp"
#include "sfm/file/FileHandler.hpp"
#include "sfm/History.hpp"

class Action
{
private:
        bool showDots = Config::DEFAULT_DOT_FILE;
        const FileHandler fileHandler {};
        History history {};
        void remove(DirInfo&) const noexcept;
        void rename(DirInfo&, const fs::path&) const noexcept;

public:
        size_t populate(const fs::path&, std::vector<fs::directory_entry>&, std::vector<std::string>&) noexcept;
        bool processInput(const int&, DirInfo&);
        void processInputWithMovement(const int&, DirInfo&, fs::path&);
};
