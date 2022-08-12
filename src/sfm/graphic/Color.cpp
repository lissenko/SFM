#include "sfm/graphic/Color.hpp"

#include <iostream>

#include <ncurses.h>

#include "Config.hpp"

Color::Color() noexcept
{
        colors.insert(  {GREEN, std::pair(GREEN_FG, GREEN_BG)}  );
        colors.insert(  {BLUE, std::pair(BLUE_FG, BLUE_BG)}  );
        colors.insert(  {RED, std::pair(RED_FG, RED_BG)}  );
        colors.insert(  {BLACK, std::pair(BLACK_FG, BLACK_BG)}  );
        colors.insert(  {YELLOW, std::pair(YELLOW_FG, YELLOW_BG)}  );
        colors.insert(  {MAGENTA, std::pair(MAGENTA_FG, MAGENTA_BG)}  );
        colors.insert(  {CYAN, std::pair(CYAN_FG, CYAN_BG)}  );
}

const std::pair<Color::ColorStyle, Color::ColorStyle>& Color::pick(const Theme& theme) const 
{
        return colors.at(theme);
}

bool Color::init() noexcept
{
	if (!has_colors()) {
		std::cerr << "Terminal does not support color\n";
		return false;
	}
	use_default_colors();
	start_color();
        init_pair(GREEN_FG, COLOR_GREEN, COLOR_DEFAULT);
	init_pair(GREEN_BG, COLOR_BLACK, COLOR_GREEN);

	init_pair(RED_FG, COLOR_RED, COLOR_DEFAULT);
	init_pair(RED_BG, COLOR_BLACK, COLOR_RED);

	init_pair(BLUE_FG, COLOR_BLUE, COLOR_DEFAULT);
	init_pair(BLUE_BG, COLOR_BLACK, COLOR_BLUE);

	init_pair(BLACK_FG, COLOR_WHITE, COLOR_DEFAULT);
	init_pair(BLACK_BG, COLOR_BLACK, COLOR_WHITE);

	init_pair(YELLOW_FG, COLOR_YELLOW, COLOR_DEFAULT);
	init_pair(YELLOW_BG, COLOR_BLACK, COLOR_YELLOW);

	init_pair(MAGENTA_FG, COLOR_MAGENTA, COLOR_DEFAULT);
	init_pair(MAGENTA_BG, COLOR_BLACK, COLOR_MAGENTA);

	init_pair(CYAN_FG, COLOR_CYAN, COLOR_DEFAULT);
	init_pair(CYAN_BG, COLOR_BLACK, COLOR_CYAN);

	init_pair(DEFAULT_FG, COLOR_WHITE, COLOR_DEFAULT);
        return true;
}

void Color::
pickUpColor(bool isDir, bool isSelected, bool isChecked, unsigned& style, short& pair) noexcept
{
        auto normalColors = pickThemeColor();
        auto checkedColors = pick(Config::checkedTheme);
        /* checked with highlight */
        if (isChecked && isSelected)
                {style = A_BOLD; pair = checkedColors.second;}
        /* checked directory*/
        else if (isChecked && isDir)
                {style = A_BOLD; pair = checkedColors.first;}
        /* checked file */
        else if (isChecked)
                {style = A_BOLD; pair = checkedColors.first;}
        /* directory with highlight */
        else if (isSelected && isDir)
                {style = A_BOLD; pair = normalColors.second;}
        /* file with highlight */
        else if (isSelected)
                {style = A_BOLD | A_STANDOUT; pair = DEFAULT_FG;}
        /* directory */
        else if (isDir)
                {style = A_BOLD; pair = normalColors.first;}
        /* file */
        else
                {style = A_NORMAL; pair = DEFAULT_FG;}
}

const std::pair<Color::ColorStyle, Color::ColorStyle>& Color::pickThemeColor() const noexcept
{
        return pick(Config::theme);
}

Color::ColorStyle Color::pickThemeFileColor() const noexcept
{
        return DEFAULT_FG;
}

const std::pair<Color::ColorStyle, Color::ColorStyle>& Color::pickAltColor() const noexcept
{
        return pick(Config::altColorTheme);
}
