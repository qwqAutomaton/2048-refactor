#pragma once
#include "../game/board.h"
#include "console.h"
#include <string>
#include <cstdio>
#include <tuple>

namespace Game2048
{
    namespace UI
    {
        class Display
        {
            constexpr static const char
                *row_ = "XXXXXXXXXX", // X * 10
                *col_ = "X        X",
                *space_ = "        ";

        public:
            const static std::tuple<ConsoleColour, ConsoleColour, ConsoleFont> STYLE[11];
            constexpr static int TILEHEIGHT = 5, TILEWIDTH = 10;
            static void print(const Game::GameBoard &board);
            static void print_tile(int x, int y, int value);
        };
    }
}