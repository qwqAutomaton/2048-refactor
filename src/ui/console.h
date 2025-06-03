#pragma once
#include <cstdint>
#include <tuple>
#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#include <cstdio>
#endif

namespace Game2048
{
    namespace UI
    {
        enum ConsoleColour
        {
            Black = 0,
            Red,
            Green,
            Yellow,
            Blue,
            Magenta,
            Cyan,
            White,
            Default = 9
        };
        enum ConsoleFont
        {
            Reset = 0,
            Bold,
            Dim,
            Italic,
            Underline,
        };
        class Console
        {
        private:
#ifndef _WIN32 // a strange singleton for C++14
            static termios &old_tio()
            {
                static termios old_tio;
                return old_tio;
            };
            static bool &israw()
            {
                static bool israw;
                return israw;
            };
#endif
        public:
            using coord_t = int16_t;
            struct Coord
            {
                coord_t x, y;
                Coord(coord_t x_, coord_t y_) : x(x_), y(y_) {}
            };
            static bool init();
            static void cleanup();
            static void set_style(ConsoleColour fg, ConsoleColour bg = Default, ConsoleFont font = Reset);
            static void set_style(std::tuple<ConsoleColour, ConsoleColour, ConsoleFont> style);
            static void set_cursor(coord_t x, coord_t y);
            static void clear();
            static char read_key();
            static void sleep(uint32_t ms);
        };
    }
}