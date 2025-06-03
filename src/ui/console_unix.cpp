#ifndef _WIN32
#include "console.h"

namespace Game2048
{
    namespace UI
    {
        bool Console::init()
        {
            israw() = false;
            tcgetattr(STDIN_FILENO, &old_tio());
            struct termios new_tio = old_tio();
            new_tio.c_lflag &= ~(ICANON | ECHO);
            new_tio.c_cc[VMIN] = 1;
            new_tio.c_cc[VTIME] = 0;
            if (tcsetattr(STDIN_FILENO, TCSANOW, &new_tio) < 0)
                return false;
            clear();
            israw() = true;
            return true;
        }
        void Console::cleanup()
        {
            if (israw())
            {
                israw() = false;
                tcsetattr(STDIN_FILENO, TCSANOW, &old_tio());
            }
            // clear styles
            printf("\033[0m");
            clear();
        }
        void Console::set_style(ConsoleColour fg, ConsoleColour bg, ConsoleFont font)
        {
            printf("\033[%d;%d;%dm",
                   static_cast<int>(font),
                   30 + static_cast<int>(fg),
                   40 + static_cast<int>(bg));
        }
        void Console::set_style(std::tuple<ConsoleColour, ConsoleColour, ConsoleFont> style)
        {
            auto [fg, bg, font] = style;
            set_style(fg, bg, font);
        }
        void Console::set_cursor(coord_t x, coord_t y)
        {
            printf("\033[%d;%dH", y, x);
        }
        void Console::clear()
        {
            printf("\033[2J");
            set_cursor(0, 0);
        }
        char Console::read_key()
        {
            return getchar();
        }
        void Console::sleep(uint32_t ms)
        {
            fflush(stdout);
            usleep(ms * 1000);
        }
    }
}
#endif
