#pragma once

#include "Brick.hpp"
#include "GlobalConsts.hpp"

enum class EBrickState
{
    Floating,
    Landed,
    ReachedWall,
    ReachedUp
};

class Board
{
public:
    Board();

    bool IsPossibleMove(std::array<cv::Point2i, NUM_OF_BRICK_LINKS> currPosition);
    void Update(std::array<cv::Point2i, NUM_OF_BRICK_LINKS> currPosition);
    bool HandleLanding();
    void ResetBoard();
    inline std::array<std::array<bool, NUM_OF_ROWS>, NUM_OF_COLS> GetBoard() { return _board; }

private:
    void InitPrevPosition();
    bool DeletePossibleRows();
    void DeleteRow(unsigned int rowNumber);

    std::array<std::array<bool, NUM_OF_ROWS>, NUM_OF_COLS> _board;
    std::array<cv::Point2i, NUM_OF_BRICK_LINKS> _prevPosition;
};