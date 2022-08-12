#include "sfm/graphic/Renderer.hpp"

#include <algorithm>
#include <iostream>
#include <vector>
#include <ncurses.h>

Renderer::~Renderer() noexcept
{
        leaveCurseMode();
}

void Renderer::leaveCurseMode() noexcept
{
        endwin();
}

bool Renderer::init() noexcept
{
	if (!initscr() || !Color::init()) {
		std::cerr << "Ncurses failed to launch\n";
		return false;
	}
	raw();
	noecho();
	curs_set(0);
	set_escdelay(0);
	return true;
}

void Renderer::
printFile(WINDOW* win, const FileParameter& params) noexcept
{
        const int y = static_cast<int>(params.y);
        const int x = static_cast<int>(params.x);
        const int characteristicX = getmaxx(win) - x - static_cast<int>(params.characteristic.size());
        attr_t attr = COLOR_PAIR(params.pair) | params.style;
        wattron(win, attr);
        mvwprintw(win, y, x, "%s", params.path.c_str());
        mvwprintw(win, y, characteristicX, "%s", params.characteristic.c_str());
        wattroff(win, attr);
        mvwchgat(win, y, static_cast<int>(params.path.size()), EOL, params.style, params.pair , nullptr);
}

void Renderer::drawFiles(WINDOW* window, const DirInfo& dirInfo) noexcept
{
        const std::vector<fs::directory_entry> files = dirInfo.getFiles();
        const std::vector<std::string> characteristics = dirInfo.getCharacteristics();
        const size_t max = std::min(files.size() - dirInfo.getOffset(), dirInfo.getHeight());
        const unsigned& boxOffset = dirInfo.getBox();
        unsigned style {};
        short pair {};

        // i = index in the file vector
        // y = line in the window 
        for (std::size_t i = dirInfo.getOffset(), y = 0; y < max; ++i, ++y) {
                const fs::directory_entry file = files.at(i);
                std::string filename = file.path().filename().string();
                const std::string characteristic = characteristics.at(i);
                const bool isDir = i < dirInfo.getDirCount();
                const bool isSelected = i == dirInfo.getHighlight();
                const bool isChecked = dirInfo.isChecked(file);
                const unsigned yPos = static_cast<unsigned>(y + boxOffset);
                if (isChecked)
                        filename.insert(0, " ");
                colorPicker.pickUpColor(isDir, isSelected, isChecked, style, pair);
                printFile(window, {filename, characteristic, boxOffset, yPos, style, pair});
        }

}

void Renderer::printCurrentFile(WINDOW* win, const fs::path& currentPath, const fs::path& selectedPath) noexcept
{
        std::string currentPathStr = currentPath.string();
        if (currentPathStr.size() != 1)
                currentPathStr.push_back('/');
        auto color = colorPicker.pickThemeColor();
        attr_t attr = COLOR_PAIR(color.first) | A_BOLD;
        wattron(win, attr);
        wprintw(win, "%s", currentPathStr.c_str());
        wattroff(win, attr);
        attr = COLOR_PAIR(colorPicker.pickThemeFileColor()) | A_BOLD;
        wattron(win, attr);
        wprintw(win, "%s", selectedPath.filename().c_str());
        wattroff(win, attr);
}

void Renderer::printUserInfo(WINDOW* win, const std::string& username, const std::string& hostname) noexcept
{
        auto color = colorPicker.pickAltColor().first;
        attr_t attr = COLOR_PAIR(color) | A_BOLD;
        wattron(win, attr);
        wprintw(win, "%s@%s ", username.c_str(), hostname.c_str());
        wattroff(win, attr);
}

void Renderer::printFileInfo(WINDOW* win, const std::string& perms) noexcept
{
        auto color = colorPicker.pickAltColor().first;
        attr_t attr = COLOR_PAIR(color) | A_NORMAL;
        wattron(win, attr);
        wprintw(win, "%s ", perms.c_str());
        wattroff(win, attr);
}

void Renderer::printUserInput(WINDOW* win, const std::string& input, const std::string& title) noexcept
{
        int middle = getmaxx(win) / 2 - static_cast<int>(title.size())+1;
        attr_t attr = A_BOLD;
        wattron(win, attr);
        mvwprintw(win, 0, middle, "%s", title.c_str());
        wattroff(win, attr);
        wmove(win, 1, 1); // skip border
        wprintw(win, "%s", input.c_str());
        attr = A_BLINK;
        wattron(win, attr);
        wprintw(win, "%c", '|');
        wattroff(win, attr);
}

void Renderer::clearWindow(WINDOW*& window) noexcept
{
        werase(window);
}

void Renderer::drawBox(WINDOW*& window) noexcept
{
        box(window, 0, 0);
}

void Renderer::refreshWindow(WINDOW*& window) noexcept
{
        wrefresh(window);
}

int Renderer::askInput(WINDOW*& window) noexcept
{
        return wgetch(window);
}

void Renderer::allowKeypadInput(WINDOW*& window) noexcept
{
        keypad(window, true);
}
