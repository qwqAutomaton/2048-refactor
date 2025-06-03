#pragma once
#include "board.h"
#include <random>
#include <memory>

namespace Game2048
{
    namespace Game
    {
        enum class AIType
        {
            CORNER = 0,
            SWING,
            SWIRL,
            RANDOM,
            _ecAIType_Cnt
        };
        class AIBase
        {
        public:
            virtual ~AIBase() = default;
            virtual Direction next_move([[maybe_unused]] GameBoard &board) = 0;
            virtual const char *name() const = 0;
        };
        class CornerAI : public AIBase
        {
        public:
            Direction next_move(GameBoard &board) override;
            const char *name() const override { return "Corner AI"; }
        };
        class SwingAI : public AIBase
        {
        private:
            bool vertical_mode;
            int state;

        public:
            SwingAI(bool vertical = true) : vertical_mode(vertical), state(0) {}
            Direction next_move(GameBoard &board) override;
            const char *name() const override { return "Swing AI"; }
        };
        class SwirlAI : public AIBase
        {
        private:
            int step = 0;
            std::vector<Direction> moves;

        public:
            SwirlAI(std::initializer_list<Direction> list) : moves(list) {}
            Direction next_move(GameBoard &board) override;
            const char *name() const override { return "Swirl AI"; }
        };
        class RandomAI : public AIBase
        {
        private:
            std::mt19937 rng;
            std::uniform_int_distribution<int> dist;

        public:
            RandomAI(int seed = 0) : rng(seed), dist(0, 3) {}
            Direction next_move(GameBoard &board) override;
            const char *name() const override { return "Random AI"; }
        };

        std::unique_ptr<AIBase> create_ai(int tp);
    }
}