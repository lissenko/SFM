#include "sfm/window/info/DirInfo.hpp"

#include <algorithm>

const fs::path DirInfo::NOT_FOUND {};

DirInfo::DirInfo(Info& pInfo, fs::path& pSelectedPath) noexcept : info(pInfo), selectedPath(pSelectedPath)
{
        selectedPath = getSelectedPath();
}

void DirInfo::fixOffset() noexcept
{
        int tmp = static_cast<int>(highlight - info.getHeight()+1);
        offset = (tmp > 0) ? static_cast<size_t>(tmp) : 0;
}

void DirInfo::down() noexcept
{
        if (highlight != currentFiles.size()-1) {
                ++highlight;
                if ( (highlight - offset) >= info.getHeight())
                        ++offset;
        }

}

void DirInfo::up() noexcept
{
        if (highlight == offset && offset != 0)
                --offset;
        if ((highlight - offset) != 0)
                --highlight;

}

void DirInfo::bottom() noexcept
{
	highlight = currentFiles.size() - 1;
        fixOffset();
}

void DirInfo::top() noexcept
{
        highlight = 0;
        offset = 0;
}

void DirInfo::removeFileFromIndex(const std::ptrdiff_t& idx)
{
        currentFiles.erase(currentFiles.begin() + idx);
        // decrement dir counter
        if (isCurrentDir())
                --dirCount;
        // fix highlight
        if (highlight >= currentFiles.size())
                highlight = currentFiles.size() - 1;
        if (offset)
                --offset;
}

const fs::path DirInfo::removeSelected() noexcept
{
        if (!currentFiles.empty()) {
                const fs::directory_entry path = currentFiles.at(highlight);
                removeFileFromIndex(static_cast<std::ptrdiff_t>(highlight));
                return path;
        }
        return NOT_FOUND;
}

const std::vector<fs::directory_entry> DirInfo::removeChecked() noexcept
{
        const std::vector<fs::directory_entry> cpy = checkedFiles;
        for (const fs::directory_entry& entry : checkedFiles) {
                fileIterator it = findFile(currentFiles, entry);
                std::ptrdiff_t idx = std::distance(currentFiles.cbegin(), it);
                removeFileFromIndex(idx);
        }
        checkedFiles.clear();
        return cpy;
}

DirInfo::fileIterator DirInfo::
findFile(const std::vector<fs::directory_entry>& vec, const fs::directory_entry& file) const {
        fileIterator begin = vec.begin();
        fileIterator end = vec.end();
        fileIterator result = std::find(begin, end, file);
        return result;
}


void DirInfo::toggleChecked() noexcept
{
        const fs::directory_entry& toToggle = currentFiles.at(highlight);
        fileIterator result = findFile(checkedFiles, toToggle);
        if (result == checkedFiles.end())
                checkedFiles.push_back({toToggle});
        else
                checkedFiles.erase(result);
}

bool DirInfo::isChecked(const fs::directory_entry& file) const noexcept
{
        return (findFile(checkedFiles, file) != checkedFiles.end());
}

bool DirInfo::isAnyFileChecked() const noexcept{
        return !checkedFiles.empty();
}

bool DirInfo::isCurrentDir() const noexcept
{
        return (highlight < dirCount);
}


const size_t& DirInfo::getHighlight() const noexcept
{
        return highlight;
}

const size_t& DirInfo::getDirCount() const noexcept
{
        return dirCount;
}

const size_t& DirInfo::getHeight() const noexcept
{
        return info.getHeight();
}

const bool& DirInfo::getBox() const noexcept
{
        return info.getBox();
}

const size_t& DirInfo::getOffset() const noexcept
{
        return offset;
}

const std::vector<fs::directory_entry>& DirInfo::getFiles() const noexcept
{
        return currentFiles;
}

std::vector<fs::directory_entry>& DirInfo::getFiles() noexcept
{
        return currentFiles;
}

const std::vector<std::string>& DirInfo::getCharacteristics() const noexcept
{
        return currentFilesCharacteristics;
}

std::vector<std::string>& DirInfo::getCharacteristics() noexcept
{
        return currentFilesCharacteristics;
}

const fs::path& DirInfo::getSelectedPath() const noexcept
{
        if (!currentFiles.empty())
                return currentFiles.at(highlight).path();
        return NOT_FOUND;
}

void DirInfo::setOffset(size_t nOffset) noexcept
{
        offset = nOffset;
}

void DirInfo::setDircount(size_t nDirCount) noexcept
{
        dirCount = nDirCount;
}

void DirInfo::setHighlightFromPath(const fs::path& path) noexcept
{
        const fs::directory_entry entry = fs::directory_entry(path);
        const fileIterator it = findFile(currentFiles, entry);
        std::ptrdiff_t idx {};
        if (it == currentFiles.end())
                idx = 0;
        else 
                idx = std::distance(currentFiles.cbegin(), it);
        highlight = static_cast<size_t>(idx);
        fixOffset();
}

void DirInfo::setSelectedPath() noexcept
{
        selectedPath = getSelectedPath();
}
