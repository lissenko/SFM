#pragma once

#include "sfm/Action.hpp"
#include "sfm/graphic/Renderer.hpp"
#include "sfm/window/info/Info.hpp"

class Window
{
private:
        bool clearFlag = 1;
        bool refreshFlag = 1;
protected:
        // static because there are multiple instances of Window
        static Renderer renderer;
        WINDOW* window;
        Info info {};
        // common to all windows
        static fs::path currentPath;
        static fs::path selectedPath;
public:
        Window(int, int, int, int, bool) noexcept;
        virtual ~Window();

        virtual void draw() noexcept;
        void clear() noexcept;
        void refresh() noexcept;

        void setRefreshFlag(bool);
        void setBox(bool);

        // TODO this is tmp: copying might be a good idea
	constexpr Window(const Window&) noexcept = delete;
	constexpr Window& operator=(const Window&) noexcept = delete;
};
