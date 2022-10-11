#pragma once

#include <string>

#include <ncurses.h>

#include "sfm/graphic/Color.hpp"

namespace Config
{
        /* Themes to pick from:
         * GREEN, BLUE, RED, BLACK, YELLOW, MAGENTA, CYAN 
         */
        constexpr Theme theme = RED;
        constexpr Theme checkedTheme = YELLOW;
        constexpr Theme altColorTheme = BLUE;

        /* Keys configuration */
        constexpr int K_DOWN = 'j';
        constexpr int K_DOWN_AUX = KEY_DOWN;
        constexpr int K_UP = 'k';
        constexpr int K_UP_AUX = KEY_UP;
        constexpr int K_LEFT = 'h';
        constexpr int K_LEFT_AUX = KEY_LEFT;
        constexpr int K_RIGHT = 'l';
        constexpr int K_RIGHT_AUX = KEY_RIGHT;
        constexpr int K_TOP = 'g';
        constexpr int K_BOTTOM = 'G';
        constexpr int K_REMOVE = 'd';
        constexpr int K_LEAVE = 'q';
        constexpr int K_RENAME = 'r';
        constexpr int K_TOGGLE_CHECK = ' ';
        constexpr int K_RETURN = 10;
        constexpr int K_ESCAPE = 27;
        constexpr int K_TOGGLE_DOT_FILE = '.';

        /* Windows configuration */
        constexpr bool BOXES = 1;
        constexpr bool DEFAULT_DOT_FILE = 0;

};
