#include "sfm/window/PermissionWindow.hpp"

#include "sfm/file/FileCommon.hpp"

PermissionWindow::PermissionWindow(int yPos) noexcept : Window(1, COLS, yPos, 0, 0)
{
}

void PermissionWindow::draw() noexcept
{
        std::string permissions = FileCommon::getFilePermissions(selectedPath);
        renderer.printFileInfo(window, permissions);
}

