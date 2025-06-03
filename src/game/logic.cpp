#include "logic.h"

namespace Game2048
{
    namespace Game
    {
        using namespace UI;
        Game::Game()
        {
            mode_ = Console::init() ? GameMode::RUNNING : GameMode::FAIL;
        }
        Game::~Game()
        {
            Console::cleanup();
        }
        bool Game::run()
        {
            if (mode_ == GameMode::FAIL)
            {
                printf("Console initialization failed.\n");
                return false;
            }
            Console::clear();
            Console::set_cursor(1, 1);
            Console::set_style(Default, Default, Reset);
            printf("A Simple 2048 Game\n");
            printf("Input the size of the map (3~8, 'q' to quit). <_>\b\b");
            char chr = Console::read_key();
            while ((!isdigit(chr) && chr != 'q') ||
                   (isdigit(chr) &&
                    (chr < '3' || chr > '8')))
                chr = Console::read_key();
            if (chr == 'q')
                return false;
            board_ = GameBoard(chr - '0');
            Console::set_style(Green, Default, Underline);
            printf("%d\n", chr - '0');
            Console::set_style(Default, Default, Reset);
            printf("You will be playing a ");
            Console::set_style(Green, Default, Bold);
            printf("%d", board_.size());
            Console::set_style(Default, Default, Reset);
            printf(" x ");
            Console::set_style(Green, Default, Bold);
            printf("%d", board_.size());
            Console::set_style(Default, Default, Reset);
            printf(" map.\n");
            Console::sleep(500);
            printf("Press '1' to play yourself!\n");
            printf("Press '2' to watch the computer play the game.\n");
            printf("Press 'q' to quit.\n");
            while (chr != '1' && chr != '2' && chr != 'q')
                chr = Console::read_key();
            switch (chr)
            {
            case '1':
                human();
                break;
            case '2':
                AI();
                break;
            default:
                break;
            }
            return true;
        }
        void Game::human()
        {
            board_.initialize();
            Display::print(board_);
            Console::set_style(Default, Default, Reset);
            printf("Press w/a/s/d to move, q to quit.\n");
            char chr = ' ';
            while (chr != 'q' &&
                   GameBoard::GameState::ONGOING == board_.get_state())
            {
                chr = Console::read_key();
                bool res = false;
                switch (chr)
                {
                case 'w':
                    res = board_.move(UP);
                    break;
                case 's':
                    res = board_.move(DOWN);
                    break;
                case 'a':
                    res = board_.move(LEFT);
                    break;
                case 'd':
                    res = board_.move(RIGHT);
                    break;
                default:
                    break;
                }
                if (!res)
                    continue;
                Display::print(board_);
                Console::set_style(Default, Default, Reset);
                printf("Press w/a/s/d to move, q to quit.\n");
                switch (board_.get_state())
                {
                case GameBoard::GameState::WIN:
                    Console::sleep(1000);
                    Console::clear();
                    Console::set_cursor(1, 1);
                    Console::set_style(Green, Default, Bold);
                    printf("You Win.\n");
                    Console::set_style(Default, Default, Reset);
                    printf("Step used: ");
                    Console::set_style(Green, Default, Bold);
                    printf("%d\n", board_.get_step());
                    Console::set_style(Default, Default, Reset);
                    printf("Total score: ");
                    Console::set_style(Green, Default, Bold);
                    printf("%d\n", board_.get_score());
                    Console::set_style(Default, Default, Reset);
                    printf("Press any key to continue.\n");
                    Console::read_key();
                    break;
                case GameBoard::GameState::LOSE:
                    Console::sleep(1000);
                    Console::clear();
                    Console::set_cursor(1, 1);
                    Console::set_style(Red, Default, Bold);
                    printf("You Lose.\n");
                    Console::set_style(Default, Default, Reset);
                    printf("Step used: ");
                    Console::set_style(Red, Default, Bold);
                    printf("%d\n", board_.get_step());
                    Console::set_style(Default, Default, Reset);
                    printf("Total score: ");
                    Console::set_style(Red, Default, Bold);
                    printf("%d\n", board_.get_score());
                    Console::set_style(Default, Default, Reset);
                    printf("Press any key to continue.\n");
                    Console::read_key();
                    break;
                case GameBoard::GameState::ONGOING:
                    break;
                }
            }
        }
        void Game::AI()
        {
            printf("Choose AI Type.\n");
            printf("%s", AIList);
            char choice = Console::read_key();
            while (choice != 'q' && (choice <= '0' || choice > AICount + '0'))
                choice = Console::read_key();
            if (choice == 'q')
                return;
            std::unique_ptr<AIBase> ai_;
            try
            {
                ai_ = Game2048::Game::create_ai(choice - '0' - 1);
            }
            catch (const std::invalid_argument &e)
            {
                printf("Invalid AI type: \'%c\' (ASCII %d)\nExceprion msg: \"%s\"\n", choice, choice, e.what());
                Console::read_key();
                return;
            }
            // run board
            board_.initialize();
            Display::print(board_);
            Console::set_style(Default, Default, Reset);
            printf("Current AI: ");
            Console::set_style(Green, Default, Bold);
            printf("%s", ai_->name());
            Console::set_style(Default, Default, Reset);
            printf(".\n");
            while (GameBoard::GameState::ONGOING == board_.get_state())
            {
                Direction dir = ai_->next_move(board_);
                if (!board_.move(dir))
                    continue;
                Display::print(board_);
                Console::set_style(Default, Default, Reset);
                printf("Current AI: ");
                Console::set_style(Green, Default, Bold);
                printf("%s", ai_->name());
                Console::set_style(Default, Default, Reset);
                printf(". AI move: ");
                Console::set_style(Red, Default, Bold);
                printf("%s", dir == UP ? "↑" : dir == DOWN ? "↓"
                                           : dir == LEFT   ? "←"
                                                           : "→");
                switch (board_.get_state())
                {
                case GameBoard::GameState::WIN:
                    Console::sleep(1000);
                    Console::clear();
                    Console::set_cursor(1, 1);
                    Console::set_style(Green, Default, Bold);
                    printf("AI wins.\n");
                    Console::set_style(Default, Default, Reset);
                    printf("Step used: ");
                    Console::set_style(Green, Default, Bold);
                    printf("%d\n", board_.get_step());
                    Console::set_style(Default, Default, Reset);
                    printf("Total score: ");
                    Console::set_style(Green, Default, Bold);
                    printf("%d\n", board_.get_score());
                    Console::set_style(Default, Default, Reset);
                    printf("Press any key to continue.\n");
                    Console::read_key();
                    break;
                case GameBoard::GameState::LOSE:
                    Console::sleep(1000);
                    Console::clear();
                    Console::set_cursor(1, 1);
                    Console::set_style(Red, Default, Bold);
                    printf("AI Lose.\n");
                    Console::set_style(Default, Default, Reset);
                    printf("Step used: ");
                    Console::set_style(Red, Default, Bold);
                    printf("%d\n", board_.get_step());
                    Console::set_style(Default, Default, Reset);
                    printf("Total score: ");
                    Console::set_style(Red, Default, Bold);
                    printf("%d\n", board_.get_score());
                    Console::set_style(Default, Default, Reset);
                    printf("Press any key to continue.\n");
                    Console::read_key();
                    break;
                case GameBoard::GameState::ONGOING:
                    break;
                }
                Console::sleep(300);
            }
        }
    }
}
