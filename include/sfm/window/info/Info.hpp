#pragma once

#include <cstddef>

class Window;

class Info {
private:
        bool box {};
        size_t height {};
        friend Window;
public:

        const bool& getBox() const noexcept;
        const size_t& getHeight() const noexcept;
};
