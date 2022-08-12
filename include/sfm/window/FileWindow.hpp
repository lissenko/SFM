#pragma once

#include "sfm/window/Window.hpp"
#include "sfm/window/InputWindow.hpp"
#include "sfm/window/info/DirInfo.hpp"

class FileWindow : public InputWindow
{
private:
        Action action {};
        DirInfo dirInfo {info, selectedPath};
protected:

public:
        FileWindow(int, int, int, bool) noexcept;
        virtual int askInput() noexcept override;
        virtual void processInput(const int&) noexcept override;
        virtual void draw() noexcept override;

};

