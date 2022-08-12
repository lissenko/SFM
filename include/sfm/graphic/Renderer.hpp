#pragma once

#include <ncurses.h>

#include "sfm/graphic/Color.hpp"
#include "sfm/file/FileDecorator.hpp"
#include "sfm/window/info/DirInfo.hpp" 

constexpr int EOL = -1;

class Renderer
{
private:
        struct FileParameter
        {
                const std::string& path;
                const std::string& characteristic;
                const unsigned& x;
                const unsigned& y;
                const attr_t& style;
                const short& pair;
        };

        Color colorPicker {};
        void printFile(WINDOW*, const FileParameter&) noexcept;
public:
        static bool init() noexcept;
        static void leaveCurseMode() noexcept;
        ~Renderer() noexcept;
        void drawFiles(WINDOW*, const DirInfo&) noexcept;
        void printCurrentFile(WINDOW*, const fs::path&, const fs::path&) noexcept;
        void printUserInfo(WINDOW*, const std::string&, const std::string&) noexcept;
        void printFileInfo(WINDOW*, const std::string&) noexcept;
        void printUserInput(WINDOW*, const std::string&, const std::string&) noexcept;
        void clearWindow(WINDOW*&) noexcept;
        void drawBox(WINDOW*&) noexcept;
        void refreshWindow(WINDOW*&) noexcept;
        int askInput(WINDOW*&) noexcept;
        void allowKeypadInput(WINDOW*&) noexcept;
};
