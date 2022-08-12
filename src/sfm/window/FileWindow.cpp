#include "sfm/window/FileWindow.hpp"

#include <iostream>

#include "Config.hpp"

FileWindow::FileWindow(int height, int width, int yPos, bool allowBox) noexcept :
        InputWindow(height, width, yPos, 0, allowBox)
{
}

int FileWindow::askInput() noexcept
{
        return renderer.askInput(window);
}

void FileWindow::processInput(const int& c) noexcept
{
        bool processed = action.processInput(c, dirInfo);
        if (!processed) {
                action.processInputWithMovement(c, dirInfo, currentPath);
        }
        dirInfo.setSelectedPath();
}


void FileWindow::draw() noexcept
{
        renderer.drawFiles(window, dirInfo);
        Window::draw();
}

