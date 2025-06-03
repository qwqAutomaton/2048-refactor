#pragma once
#include <vector>
#include <random>
#include <stdexcept>

namespace Game2048
{
    namespace Game
    {
        enum Direction
        {
            UP = 1,
            DOWN,
            LEFT,
            RIGHT
        };
        class GameBoard
        {
        public:
            enum GameState
            {
                LOSE = -1,
                ONGOING,
                WIN,
            };
            explicit GameBoard(int size = 4, int seed = 0);
            bool move(Direction direction);
            bool can_move(Direction direction) const;
            void initialize();
            void tile();
            int size() const { return size_; }
            GameState get_state() const;
            int get_score() const { return score_; }
            int get_step() const { return step_; }
            const std::vector<int> &get_board() const { return board_; }

        private:
            std::pair<int, int> gen_tile();
            bool move_up();
            bool move_down();
            bool move_left();
            bool move_right();
            bool can_move_up() const;
            bool can_move_down() const;
            bool can_move_left() const;
            bool can_move_right() const;
            std::vector<int> board_;
            int size_;
            int score_, step_;
            std::mt19937 rng_;
            std::discrete_distribution<int> dist_;
            const static int gen_allowed[2];
            const static double gen_prob[2];
        };
    }
}