#pragma once

#include <map>

constexpr int COLOR_DEFAULT = -1;

enum Theme {
        GREEN,
        BLUE,
        RED,
        BLACK,
        YELLOW,
        MAGENTA,
        CYAN,
};


class Color
{
private:
        enum ColorStyle {
                GREEN_FG = 1,
                GREEN_BG,
                RED_FG,
                RED_BG,
                BLUE_FG, 
                BLUE_BG,
                BLACK_FG,
                BLACK_BG,
                YELLOW_FG,
                YELLOW_BG,
                MAGENTA_FG,
                MAGENTA_BG,
                CYAN_FG,
                CYAN_BG,
                DEFAULT_FG
        };

        /*
         * First: normal color
         * Second: highlight color
         */
        std::map<Theme, std::pair<ColorStyle, ColorStyle>> colors {};
        const std::pair<ColorStyle, ColorStyle>& pick(const Theme&) const;
public:
        static bool init() noexcept;
        Color() noexcept;
        void pickUpColor(bool, bool, bool, unsigned&, short&) noexcept;
        const std::pair<ColorStyle, ColorStyle>& pickThemeColor() const noexcept;
        ColorStyle pickThemeFileColor() const noexcept;
        const std::pair<ColorStyle, ColorStyle>& pickAltColor() const noexcept;
};
