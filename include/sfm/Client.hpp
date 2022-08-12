#pragma once

#include <array>
#include <filesystem>

#include "Config.hpp"
#include "sfm/window/FileWindow.hpp"
#include "sfm/window/PathWindow.hpp"
#include "sfm/window/PermissionWindow.hpp"
#include "sfm/window/Window.hpp"

constexpr std::size_t WINDOW_COUNT = 3;
constexpr bool ALLOW_BOXES = 1;

class Client
{
private:
        using WindowPtr = std::unique_ptr<Window>;
        std::array<WindowPtr, WINDOW_COUNT> windows {
                WindowPtr(new FileWindow(LINES-2, COLS, 1, ALLOW_BOXES)),
                WindowPtr(new PathWindow(0)),
                WindowPtr(new PermissionWindow(LINES-1))
                };
public:
        void start();
};
