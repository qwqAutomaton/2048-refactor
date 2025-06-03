#include "board.h"

namespace Game2048
{
    namespace Game
    {

        const int GameBoard::gen_allowed[2] = {2, 4};
        const double GameBoard::gen_prob[2] = {0.5, 0.5}; // 90% for 2, 10% for 4
        GameBoard::GameBoard(int size, int seed)
            : size_(size), score_(0), step_(0), rng_(seed),
              dist_(std::begin(gen_prob), std::end(gen_prob))
        {
            board_.clear();
            board_.resize(size * size, 0);
        }
        void GameBoard::initialize()
        {
            score_ = 0;
            step_ = 0;
            tile();
            tile();
        }
        std::pair<int, int> GameBoard::gen_tile()
        {
            std::vector<int> empty_tiles;
            for (int i = 0; i < size_ * size_; i++)
                if (board_[i] == 0)
                    empty_tiles.push_back(i);
            // no empty tile
            if (empty_tiles.empty())
                return {-1, -1};
            std::uniform_int_distribution<int> dist(0, empty_tiles.size() - 1);
            int index = empty_tiles[dist(rng_)];
            int value = gen_allowed[dist_(rng_)];
            return {index, value};
        }
        void GameBoard::tile()
        {
            auto tiles = gen_tile();
            int index = tiles.first;
            int value = tiles.second;
            if (index != -1)
                board_[index] = value;
            else
                throw std::runtime_error("No empty tile available");
        }
        bool GameBoard::move(Direction direction)
        {
            bool moved = false;
            switch (direction)
            {
            case UP:
                moved = move_up();
                break;
            case DOWN:
                moved = move_down();
                break;
            case LEFT:
                moved = move_left();
                break;
            case RIGHT:
                moved = move_right();
                break;
            default:
                throw std::invalid_argument("Invalid direction");
            }
            if (moved)
            {
                tile();
                step_++;
            }
            return moved;
        }
        bool GameBoard::move_up()
        {
            // pd array in old version
            std::vector<bool> merged(size_ * size_, false);
            bool moved = false;
            for (int i = 1; i < size_; i++)
            {
                for (int j = 0; j < size_; j++)
                {
                    if (board_[i * size_ + j] == 0)
                        continue;
                    int curr_pos = i;
                    while (curr_pos > 0 && board_[(curr_pos - 1) * size_ + j] == 0)
                        curr_pos--;
                    if (curr_pos != i)
                    {
                        board_[curr_pos * size_ + j] = board_[i * size_ + j];
                        board_[i * size_ + j] = 0;
                        moved = true;
                    }
                    if (curr_pos > 0)
                    {
                        int target_idx = (curr_pos - 1) * size_ + j;
                        int current_idx = curr_pos * size_ + j;
                        if (board_[target_idx] == board_[current_idx] && !merged[target_idx])
                        {
                            board_[target_idx] *= 2;
                            score_ += board_[target_idx];
                            board_[current_idx] = 0;
                            merged[target_idx] = true;
                            moved = true;
                        }
                    }
                }
            }
            return moved;
        }
        bool GameBoard::move_down()
        {
            std::vector<bool> merged(size_ * size_, false);
            bool moved = false;
            for (int i = size_ - 2; i >= 0; i--)
            {
                for (int j = 0; j < size_; j++)
                {
                    if (board_[i * size_ + j] == 0)
                        continue;
                    int curr_pos = i;
                    while (curr_pos < size_ - 1 && board_[(curr_pos + 1) * size_ + j] == 0)
                        curr_pos++;
                    if (curr_pos != i)
                    {
                        board_[curr_pos * size_ + j] = board_[i * size_ + j];
                        board_[i * size_ + j] = 0;
                        moved = true;
                    }
                    if (curr_pos < size_ - 1)
                    {
                        int target_idx = (curr_pos + 1) * size_ + j;
                        int current_idx = curr_pos * size_ + j;
                        if (board_[target_idx] == board_[current_idx] && !merged[target_idx])
                        {
                            board_[target_idx] *= 2;
                            score_ += board_[target_idx];
                            board_[current_idx] = 0;
                            merged[target_idx] = true;
                            moved = true;
                        }
                    }
                }
            }
            return moved;
        }
        bool GameBoard::move_left()
        {
            std::vector<bool> merged(size_ * size_, false);
            bool moved = false;
            for (int i = 0; i < size_; i++)
            {
                for (int j = 1; j < size_; j++)
                {
                    if (board_[i * size_ + j] == 0)
                        continue;
                    int curr_pos = j;
                    while (curr_pos > 0 && board_[i * size_ + (curr_pos - 1)] == 0)
                        curr_pos--;
                    if (curr_pos != j)
                    {
                        board_[i * size_ + curr_pos] = board_[i * size_ + j];
                        board_[i * size_ + j] = 0;
                        moved = true;
                    }
                    if (curr_pos > 0)
                    {
                        int target_idx = i * size_ + (curr_pos - 1);
                        int current_idx = i * size_ + curr_pos;
                        if (board_[target_idx] == board_[current_idx] && !merged[target_idx])
                        {
                            board_[target_idx] *= 2;
                            score_ += board_[target_idx];
                            board_[current_idx] = 0;
                            merged[target_idx] = true;
                            moved = true;
                        }
                    }
                }
            }
            return moved;
        }
        bool GameBoard::move_right()
        {
            std::vector<bool> merged(size_ * size_, false);
            bool moved = false;
            for (int i = 0; i < size_; i++)
            {
                for (int j = size_ - 2; j >= 0; j--)
                {
                    if (board_[i * size_ + j] == 0)
                        continue;
                    int curr_pos = j;
                    while (curr_pos < size_ - 1 && board_[i * size_ + (curr_pos + 1)] == 0)
                        curr_pos++;
                    if (curr_pos != j)
                    {
                        board_[i * size_ + curr_pos] = board_[i * size_ + j];
                        board_[i * size_ + j] = 0;
                        moved = true;
                    }
                    if (curr_pos < size_ - 1)
                    {
                        int target_idx = i * size_ + (curr_pos + 1);
                        int current_idx = i * size_ + curr_pos;
                        if (board_[target_idx] == board_[current_idx] && !merged[target_idx])
                        {
                            board_[target_idx] *= 2;
                            score_ += board_[target_idx];
                            board_[current_idx] = 0;
                            merged[target_idx] = true;
                            moved = true;
                        }
                    }
                }
            }
            return moved;
        }
        GameBoard::GameState GameBoard::get_state() const
        {
            for (int i = 0; i < size_ * size_; i++)
                if (board_[i] == 2048)
                    return WIN;
            for (int i = 0; i < size_; i++)
            {
                for (int j = 0; j < size_; j++)
                {
                    if (board_[i * size_ + j] == 0)
                        return ONGOING;
                    if (i > 0 && board_[i * size_ + j] == board_[(i - 1) * size_ + j])
                        return ONGOING;
                    if (j > 0 && board_[i * size_ + j] == board_[i * size_ + (j - 1)])
                        return ONGOING;
                }
            }
            return LOSE;
        }
        bool GameBoard::can_move(Direction direction) const
        {
            switch (direction)
            {
            case UP:
                return can_move_up();
            case DOWN:
                return can_move_down();
            case LEFT:
                return can_move_left();
            case RIGHT:
                return can_move_right();
            default:
                throw std::invalid_argument("Invalid direction");
            }
        }
        bool GameBoard::can_move_up() const
        {
            for (int i = 1; i < size_; i++)
            {
                for (int j = 0; j < size_; j++)
                {
                    if (board_[i * size_ + j] == 0)
                        continue;
                    if (board_[(i - 1) * size_ + j] == 0 ||
                        board_[i * size_ + j] == board_[(i - 1) * size_ + j])
                        return true;
                }
            }
            return false;
        }
        bool GameBoard::can_move_down() const
        {
            for (int i = 0; i < size_ - 1; i++)
            {
                for (int j = 0; j < size_; j++)
                {
                    if (board_[i * size_ + j] == 0)
                        continue;
                    if (board_[(i + 1) * size_ + j] == 0 ||
                        board_[i * size_ + j] == board_[(i + 1) * size_ + j])
                        return true;
                }
            }
            return false;
        }
        bool GameBoard::can_move_left() const
        {
            for (int i = 0; i < size_; i++)
            {
                for (int j = 1; j < size_; j++)
                {
                    if (board_[i * size_ + j] == 0)
                        continue;
                    if (board_[i * size_ + (j - 1)] == 0 ||
                        board_[i * size_ + j] == board_[i * size_ + (j - 1)])
                        return true;
                }
            }
            return false;
        }
        bool GameBoard::can_move_right() const
        {
            for (int i = 0; i < size_; i++)
            {
                for (int j = 0; j < size_ - 1; j++)
                {
                    if (board_[i * size_ + j] == 0)
                        continue;
                    if (board_[i * size_ + (j + 1)] == 0 ||
                        board_[i * size_ + j] == board_[i * size_ + (j + 1)])
                        return true;
                }
            }
            return false;
        }
    }
}
