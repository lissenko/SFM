#include "sfm/Action.hpp"

#include "sfm/file/FileCommon.hpp"
#include "sfm/window/Popup.hpp"
#include <iostream>

bool Action::processInput(const int& c, DirInfo& dirInfo)
{
        using namespace Config;
        switch (c) {
        case K_DOWN: case K_DOWN_AUX:
                dirInfo.down();
                break;
        case K_UP: case K_UP_AUX:
                dirInfo.up();
                break;
        case K_BOTTOM:
                dirInfo.bottom();
                break;
        case K_TOP:
                dirInfo.top();
                break;
        case K_REMOVE:
                remove(dirInfo);
                break;
        case K_TOGGLE_CHECK:
                dirInfo.toggleChecked();
                dirInfo.down();
                break;
        case K_RIGHT: case K_RIGHT_AUX: {
                const fs::path& selectedPath = dirInfo.getSelectedPath();
                if (dirInfo.isCurrentDir()) return false;
                Renderer::leaveCurseMode();
                std::string command = "xdg-open \"" + selectedPath.string() + '\"';
                std::cerr << command << std::endl;
                std::system(command.c_str());
                }
                break;
        default:
                return false;
        }
        return true;
}

void Action::processInputWithMovement(const int& c, DirInfo& dirInfo, fs::path& currentPath)
{
        using namespace Config;
        fs::path previousPath = currentPath;
        history.saveState(currentPath, dirInfo.getSelectedPath(), dirInfo.getOffset());

        switch (c) {
        case K_RIGHT: case K_RIGHT_AUX: {
                const fs::path& selectedPath = dirInfo.getSelectedPath();
                if (dirInfo.isCurrentDir() && FileCommon::isReadAllowed(selectedPath))
                        currentPath = selectedPath;
                }
                break;
        case K_LEFT: case K_LEFT_AUX:
                currentPath = currentPath.parent_path();
                break;
        case K_RENAME:
                rename(dirInfo, currentPath);
                break;
        case K_TOGGLE_DOT_FILE:
                showDots = !showDots;
                dirInfo.top();
                break;
        }

        // WARNING: populate must stay before restoreState
        size_t dirCount = populate(currentPath, dirInfo.getFiles(), dirInfo.getCharacteristics());
        dirInfo.setDircount(dirCount);
        history.restoreState(currentPath, previousPath, dirInfo);
}

void Action::remove(DirInfo& dirInfo) const noexcept
{
        if (Popup("Remove? (Y/N)").getInput() != "Y") return;
        if (dirInfo.isAnyFileChecked()) {
                const std::vector<fs::directory_entry>& filesToRemove = dirInfo.removeChecked();
                for (const fs::path& toRemove : filesToRemove)
                        fileHandler.remove(toRemove);
        } else {
                const fs::path toRemove = dirInfo.removeSelected();
                if (toRemove != DirInfo::NOT_FOUND)
                        fileHandler.remove(toRemove);
        }
}

void Action::rename(DirInfo& dirInfo, const fs::path& currentPath) const noexcept
{
        const fs::path& oldP = dirInfo.getSelectedPath();
        std::string input = Popup("Rename").getInput();
        if (!input.empty()) {
                const fs::path newP = currentPath / input;
                fileHandler.rename(oldP, newP);
        }
}

size_t Action::
populate(const fs::path& path, std::vector<fs::directory_entry>& files,
         std::vector<std::string>& characteristics) noexcept
{
        files.clear();
        characteristics.clear();
        return fileHandler.populate(path, files, characteristics, showDots);
}
