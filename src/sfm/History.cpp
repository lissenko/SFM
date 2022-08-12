#include "sfm/History.hpp"

void History::saveState(const fs::path& currentPath, const fs::path& selectedPath, const size_t& offset) noexcept
{
        tracker[currentPath] = {selectedPath, offset};
}

void History::restoreState(const fs::path& currentPath, const fs::path& previousPath, DirInfo& dirInfo) noexcept
{
        // It is necessary to repopulate in case of renaming but the history should not be written.
        if (currentPath == previousPath) return;

        // already visited file
        if (tracker.count(currentPath)) {
                const Cookie& cookie = tracker.at(currentPath);
                dirInfo.setHighlightFromPath(cookie.path);
                dirInfo.setOffset(cookie.offset);
        // match file in filesystem hierarchy
        } else if (previousPath.string().size() > currentPath.string().size()) {
                dirInfo.setHighlightFromPath(previousPath);
        // new exploration
        } else {
                dirInfo.top();
        }
}
