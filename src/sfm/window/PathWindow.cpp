#include "sfm/window/PathWindow.hpp"

#include <unistd.h>
#include <limits.h>

PathWindow::PathWindow(int yPos) noexcept : Window(1, COLS, yPos, 0, 0)
{
}

void PathWindow::draw() noexcept
{
        char hostname[HOST_NAME_MAX];
        char username[LOGIN_NAME_MAX];
        gethostname(hostname, HOST_NAME_MAX);
        getlogin_r(username, LOGIN_NAME_MAX);
        renderer.printUserInfo(window, username, hostname);
        renderer.printCurrentFile(window, currentPath, selectedPath);
}
