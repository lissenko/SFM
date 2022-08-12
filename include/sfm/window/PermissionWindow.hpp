#pragma once

#include "sfm/window/Window.hpp"

class PermissionWindow : public Window
{
private:
public:
        PermissionWindow(int) noexcept;
        virtual void draw() noexcept override;
};
