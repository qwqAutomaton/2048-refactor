
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
        void Console::set_style(ConsoleColour fg, ConsoleColour bg = Default, ConsoleFont font = Reset)
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            WORD attributes = 0;
            attributes |= fg & 0x0F;
            attributes |= (bg & 0x0F) << 4;
            SetConsoleTextAttribute(hConsole, attributes);
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