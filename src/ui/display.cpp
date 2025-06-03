#include "display.h"

namespace Game2048
{
    namespace UI
    {
        const std::tuple<ConsoleColour, ConsoleColour, ConsoleFont> Display::STYLE[] = {
            {White, Black, Reset},  // 2
            {Cyan, Black, Reset},   // 4
            {Green, Black, Reset},  // 8
            {Yellow, Black, Reset}, // 16
            {Red, White, Reset},    // 32
            {Blue, White, Reset},   // 64
            {Magenta, White, Bold}, // 128
            {White, Black, Bold},   // 256
            {Cyan, Black, Bold},    // 512
            {Green, Black, Bold},   // 1024
            {Yellow, Black, Bold},  // 2048
        };
        void Display::print(const Game::GameBoard &board)
        {
            Console::clear();
            auto matrix = board.get_board();
            int size = board.size();
            for (int i = 0; i < size; i++)
                for (int j = 0; j < size; j++)
                    print_tile(i, j, matrix[i * size + j]);
            Console::set_style(White, Black);
            Console::set_cursor(0, size * TILEHEIGHT + 1);
            for (int i = 0; i < size * TILEWIDTH; i++)
                printf("-");
            // print score & step
            Console::set_cursor((size * TILEWIDTH + 1) / 2 - 1, size * 5 + 2); // centralise
            Console::set_style(Default, Default, Reset);
            printf("Step: ");
            Console::set_style(Green, Default, Bold);
            printf("%d", board.get_step());
            Console::set_cursor((size * TILEWIDTH + 1) / 2 - 2, size * 5 + 3);
            Console::set_style(Default, Default, Reset);
            printf("Score: ");
            Console::set_style(Green, Default, Bold);
            printf("%d", board.get_score());
            Console::set_cursor(1, size * 5 + 4);
        }
        void Display::print_tile(int x, int y, int value)
        {
            // skip empty tile
            std::swap(x, y);
            if (value == 0)
                return;
            int xpos = x * TILEWIDTH + 1, ypos = y * TILEHEIGHT + 1;
            auto style = STYLE[30 - __builtin_clz(value)]; // log2(value) - 1
            // outline
            Console::set_style(std::get<0>(style),
                               std::get<1>(style),
                               std::get<2>(style));
            Console::set_cursor(xpos, ypos);
            printf(row_);
            Console::set_cursor(xpos, ypos + TILEHEIGHT - 1);
            printf(row_);
            for (int i = 1; i < TILEHEIGHT - 1; i++)
            {
                Console::set_cursor(xpos, ypos + i);
                printf(col_);
            }
            // number
            // inverted style
            Console::set_style(std::get<1>(style),
                               std::get<0>(style),
                               std::get<2>(style));
            // unify style
            for (int i = 1; i < TILEHEIGHT - 1; i++)
            {
                Console::set_cursor(xpos + 1, ypos + i);
                printf(space_);
            }
            int len = snprintf(nullptr, 0, "%d", value);
            // centralise
            Console::set_cursor(xpos + 1, ypos + 2);
            printf("%*d", (TILEWIDTH + len - 1) / 2, value);
        }
    }
}