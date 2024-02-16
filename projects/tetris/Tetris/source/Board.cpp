
#include "Board.hpp"

////////////////////////////////////////////////////////////////////////////////
Board::Board()
{
    // Initiating the board
    for (auto col(0); col < NUM_OF_COLS; ++col)
    {
        for (auto row(0); row < NUM_OF_ROWS; ++row)
        {
            _board[col][row] = false;
        }
    }

    InitPrevPosition();
}

////////////////////////////////////////////////////////////////////////////////
bool Board::IsPossibleMove(std::array<cv::Point2i, NUM_OF_BRICK_LINKS> currPosition)
{
    for (auto point : currPosition)
    {
        // If reched wall
        if (point.x < 0 || point.x >= NUM_OF_COLS || point.y >= NUM_OF_ROWS)
        {
            return false;
        }
        
        // If still up
        if (point.y < 0)
        {
            continue;
        }

        // If collided
        if (_board[point.x][point.y])
        {
            auto isOwnPoint(false);
            for (auto prevPoint : _prevPosition)
            {
                if (point == prevPoint)
                {
                    isOwnPoint = true;
                    break;
                }
            }

            if (!isOwnPoint)
            {
                return false;
            }
        }

    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////
void Board::Update(std::array<cv::Point2i, NUM_OF_BRICK_LINKS> currPosition)
{
    for (auto prevPoint : _prevPosition)
    {
        if (prevPoint.x >= 0 && prevPoint.y >= 0)
        {
            _board[prevPoint.x][prevPoint.y] = false;
        }
    }
    for (auto point : currPosition)
    {
        if (point.x >= 0 && point.y >= 0)
        {
            _board[point.x][point.y] = true;
        }
    }

    _prevPosition = currPosition;
}

////////////////////////////////////////////////////////////////////////////////
bool Board::HandleLanding()
{
    bool wasRowDeleted = DeletePossibleRows();
    InitPrevPosition();

    return wasRowDeleted;
}

////////////////////////////////////////////////////////////////////////////////
void Board::ResetBoard()
{
    for (auto col(0); col < NUM_OF_COLS; ++col)
    {
        for (auto row(0); row < NUM_OF_ROWS; ++row)
        {
            _board[col][row] = false;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
void Board::InitPrevPosition()
{
    for (auto idx(0); idx < NUM_OF_BRICK_LINKS; ++idx)
    {
        _prevPosition[idx].x = 0;
        _prevPosition[idx].y = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////
bool Board::DeletePossibleRows()
{
    bool wasRowDeleted(false);
    for (auto row(0); row < NUM_OF_ROWS; ++row)
    {
        auto col(0);
        while (col < NUM_OF_COLS)
        {
            // If the point is empty
            if (!_board[col][row])
            {
                break;
            }

            ++col;
        }

        if (NUM_OF_COLS == col)
        {
            DeleteRow(row);
            wasRowDeleted = true;
        }
    }

    return wasRowDeleted;
}

////////////////////////////////////////////////////////////////////////////////
void Board::DeleteRow(unsigned int row)
{
    for (auto currRow(row); currRow > 0; --currRow)
    {
        for (auto col(0); col < NUM_OF_COLS; ++col)
        {
            _board[col][currRow] = _board[col][currRow - 1];
        }
    }
}



