#include "AI.h"

namespace Game2048
{
    namespace Game
    {

        Direction CornerAI::next_move(GameBoard &board)
        {
            if (board.can_move(Direction::UP))
                return Direction::UP;
            if (board.can_move(Direction::LEFT))
                return Direction::LEFT;
            if (board.can_move(Direction::DOWN))
                return Direction::DOWN;
            return Direction::RIGHT;
        }

        Direction SwingAI::next_move(GameBoard &board)
        {
            state = !state;
            if (vertical_mode)
            {
                if (board.can_move(Direction::UP) && state)
                    return Direction::UP;
                if (board.can_move(Direction::DOWN))
                    return Direction::DOWN;
                vertical_mode = false;
                return next_move(board);
            }
            else
            {
                if (board.can_move(Direction::LEFT) && state)
                    return Direction::LEFT;
                if (board.can_move(Direction::RIGHT))
                    return Direction::RIGHT;
                vertical_mode = true;
                return next_move(board);
            }
        }

        Direction SwirlAI::next_move([[maybe_unused]] GameBoard &board)
        {
            Direction current_move = moves[step % moves.size()];
            step++;
            return current_move;
        }

        Direction RandomAI::next_move([[maybe_unused]] GameBoard &board)
        {
            static const Direction moves[] = {
                Direction::UP,
                Direction::RIGHT,
                Direction::DOWN,
                Direction::LEFT};
            return moves[dist(rng)];
        }

        std::unique_ptr<AIBase> create_ai(int tp)
        {
            switch (tp)
            {
            case static_cast<int>(AIType::CORNER):
                return std::make_unique<CornerAI>();
            case static_cast<int>(AIType::SWING):
                return std::make_unique<SwingAI>();
            case static_cast<int>(AIType::SWIRL):
                return std::make_unique<SwirlAI>(std::initializer_list<Direction>{
                    Direction::UP,
                    Direction::RIGHT,
                    Direction::DOWN,
                    Direction::LEFT});
            case static_cast<int>(AIType::RANDOM):
                return std::make_unique<RandomAI>();
            default:
                throw std::invalid_argument("Invalid AI type");
            }
        }

    } // namespace Game
} // namespace Game2048