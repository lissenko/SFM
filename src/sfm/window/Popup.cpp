#include "Config.hpp"
#include "sfm/window/Popup.hpp"

Popup::Popup(const std::string& titleP) noexcept :
        InputWindow(
               3,
               COLS/3,
               LINES / 2 - (LINES/4) / 2,
               COLS / 2 - (COLS / 3)/2,
               true),
        title(titleP)
{
        setBox(true); // always force boxes for popups
}

std::string Popup::getInput() noexcept
{
        int c = '\0';
        // no need to call refresh(), wgetch already does it
        do {
                processInput(c);
                clear();
                draw();
                if (c == Config::K_ESCAPE)
                        break;
                c = askInput();
        } while (c != Config::K_RETURN);
        return buffer;
}

int Popup::askInput() noexcept
{
        return renderer.askInput(window);
}

void Popup::processInput(const int& c) noexcept
{
        switch (c) {
        case KEY_BACKSPACE:
                if (!buffer.empty())
                        buffer.pop_back();
                break;
        case Config::K_ESCAPE:
                buffer = "";
                break;
        default:
                if (c != '\0')
                        buffer += static_cast<char>(c);
                break;
        }
}

void Popup::draw() noexcept
{
        Window::draw();
        renderer.printUserInput(window, buffer, title);
}
