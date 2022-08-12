#include "sfm/window/Window.hpp"

#include <iostream>

#include "Config.hpp"

Renderer Window::renderer {};
fs::path Window::currentPath = fs::current_path();
fs::path Window::selectedPath {};

// TODO re calculate height when resize
Window::Window(int height, int width, int yPos, int xPos, bool allowBox) noexcept : window(newwin(height, width, yPos, xPos))
{
        if (window == nullptr)
                std::cerr << "window failed to create\n";
        info.box = (allowBox) ? Config::BOXES : 0;
        size_t tmpHeight = static_cast<size_t>(height);
        info.height = info.box ? tmpHeight - 2 : tmpHeight;
        renderer.allowKeypadInput(window);
}

Window::~Window()
{
        delwin(window);
}

void Window::draw() noexcept
{
        if (info.box)
                renderer.drawBox(window);
}

void Window::clear() noexcept
{
        if (clearFlag)
                renderer.clearWindow(window);
}

void Window::refresh() noexcept
{
        if (refreshFlag)
                renderer.refreshWindow(window);
}

void Window::setRefreshFlag(bool f)
{
        refreshFlag = f;
}

void Window::setBox(bool f) {
        info.box = f;
}
