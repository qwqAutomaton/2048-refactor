// I HATE WINDOWS API
// WHY DONT YOU SUPPORT ANSI
#ifdef _WIN32
#include "console.h"
namespace Game2048
{
    namespace UI
    {
        bool Console::init()
        {
            clear();
            console_handle() = GetStdHandle(STD_OUTPUT_HANDLE);
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            GetConsoleScreenBufferInfo(console_handle(), &csbi);
            old_csbi() = csbi;
            return true;
        }
        void Console::cleanup()
        {
            // clear styles
            set_style(ConsoleColour::Default, ConsoleColour::Default);
            clear();
        }
        // RUBBISH WINDOWS DOES NOT SUPPORT ANSI :ANGRY:
        // SO IGNORE FONT AND DEALS ONLY WITH COLOUR :VERY ANGRY:
        void Console::set_style(ConsoleColour fg, ConsoleColour bg, ConsoleFont font)
        {
            HANDLE hConsole = console_handle();
            static const int cmap[] = {
                0, // Black
                4, // Red
                2, // Green
                6, // Yellow
                1, // Blue
                5, // Magenta
                3, // Cyan
                7, // White
            };

            WORD fg_win = (fg == Default) ? (old_csbi().wAttributes & 0xf) : cmap[fg];
            WORD bg_win = (bg == Default) ? ((old_csbi().wAttributes >> 4) & 0xf) : cmap[bg];
            WORD colour = fg_win | (bg_win << 4);
            switch (font)
            {
            case Bold:
                colour |= FOREGROUND_INTENSITY;
                break;
            case Italic:    // not supported
            case Underline: // not supported
            case Dim:
                colour &= ~FOREGROUND_INTENSITY;
                break;
            case Reset:
                colour &= ~FOREGROUND_INTENSITY;
                colour |= old_csbi().wAttributes & 0x8;
                break;
            }
            SetConsoleTextAttribute(hConsole, colour);
        }
        void Console::set_style(std::tuple<ConsoleColour, ConsoleColour, ConsoleFont> style)
        {
            auto [fg, bg, font] = style;
            set_style(fg, bg, font);
        }
        void Console::set_cursor(coord_t x, coord_t y)
        {
            COORD coord = {x, y};
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        }
        void Console::clear()
        {
            system("cls");
        }
        char Console::read_key()
        {
            return getch();
        }
        void Console::sleep(uint32_t ms)
        {
            Sleep(ms);
        }
    }
}
#endif