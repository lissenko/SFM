#pragma once

#include "sfm/window/InputWindow.hpp"

class Popup : private InputWindow
{
private:
        virtual void draw() noexcept override;
        virtual int askInput() noexcept override;
        virtual void processInput(const int&) noexcept override;

        std::string buffer {};
        std::string title {};

public:
        Popup(const std::string&) noexcept;
        std::string getInput() noexcept;
};
