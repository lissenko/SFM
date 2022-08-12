#pragma once

#include "sfm/window/Window.hpp"

class PathWindow : public Window
{
private:
public:
        PathWindow(int) noexcept;
        virtual void draw() noexcept override;
};
