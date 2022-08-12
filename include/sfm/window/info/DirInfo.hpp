#pragma once

#include <filesystem>
#include <vector>

#include "sfm/window/info/Info.hpp"

namespace fs = std::filesystem;

class FileWindow;

class DirInfo
{
private:
        using fileIterator = std::vector<fs::directory_entry>::const_iterator;

        std::vector<fs::directory_entry> currentFiles {};
        std::vector<std::string> currentFilesCharacteristics {};
        std::vector<fs::directory_entry> checkedFiles {};
        size_t dirCount {};
        size_t highlight {};
        size_t offset {};

        Info& info;
        fs::path& selectedPath;
        DirInfo(Info&, fs::path&) noexcept;
        friend FileWindow;

        void fixOffset() noexcept;
        fileIterator findFile(const std::vector<fs::directory_entry>&, const fs::directory_entry&) const;
        void removeFileFromIndex(const std::ptrdiff_t&);

public:
        static const fs::path NOT_FOUND;

        void down() noexcept;
        void up() noexcept;
        void bottom() noexcept;
        void top() noexcept;
        const fs::path removeSelected() noexcept;
        const std::vector<fs::directory_entry> removeChecked() noexcept;
        void toggleChecked() noexcept;
        bool isChecked(const fs::directory_entry&) const noexcept;
        bool isAnyFileChecked() const noexcept;
        bool isCurrentDir() const noexcept;

        /* Getters */
        const size_t& getHighlight() const noexcept;
        const size_t& getOffset() const noexcept;
        const size_t& getDirCount() const noexcept;
        const size_t& getHeight() const noexcept;
        const bool& getBox() const noexcept;
        const std::vector<fs::directory_entry>& getFiles() const noexcept;
        std::vector<fs::directory_entry>& getFiles() noexcept;
        const std::vector<std::string>& getCharacteristics() const noexcept;
        std::vector<std::string>& getCharacteristics() noexcept;
        const fs::path& getSelectedPath() const noexcept;

        /* Setters */
        void setOffset(size_t) noexcept;
        void setDircount(size_t) noexcept;
        void setHighlightFromPath(const fs::path&) noexcept;
        void setSelectedPath() noexcept;

};
