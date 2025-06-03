#pragma once
#include "board.h"
#include "../ui/display.h"
#include "../ui/console.h"
#include "AI.h"
#include "AI_TMP.h"
#include <cctype>
#include <memory>

namespace Game2048
{
    namespace Game
    {
        class Game
        {
        public:
            Game();
            ~Game();
            bool run();

        private:
            void human();
            void AI();
            GameBoard board_;
            enum class GameMode
            {
                RUNNING,
                FAIL = -1
            } mode_;
        };
    }
}