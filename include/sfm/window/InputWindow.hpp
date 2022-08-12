#pragma once

#include "sfm/window/Window.hpp"

class InputWindow : public Window
{
private:
public:
        InputWindow(int, int, int, int, bool) noexcept;
        virtual int askInput() noexcept = 0;
        virtual void processInput(const int&) noexcept = 0;
};
