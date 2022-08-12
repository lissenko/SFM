#include "sfm/Client.hpp"

#include <ncurses.h>

void Client::start()
{
        int c = 0;
        FileWindow& mainWindow = dynamic_cast<FileWindow&>(*windows.at(0));
        // mainWindow should not be refreshed by Window::refresh since wgetch() already does it
        mainWindow.setRefreshFlag(0);
        do {
                mainWindow.processInput(c);
                for (WindowPtr& win : windows) {
                        win->clear();
                        win->draw();
                        win->refresh();
                }
                c = mainWindow.askInput();
        } while (c != Config::K_LEAVE);

}
