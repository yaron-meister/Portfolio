
#include "Display.hpp"
#include "linker.hpp"
#include <format>
#include <opencv2/imgproc.hpp>

////////////////////////////////////////////////////////////////////////////////
Display::Display() : _headerPoint(390, 100), _instructionsPoint(370, 300), _scorePoint(370, 525)
{
    _canvas = cv::Mat::zeros(CANVAS_HEIGHT, CANVAS_WIDTH, CV_8UC3);
}

////////////////////////////////////////////////////////////////////////////////
void Display::Refresh(std::array<std::array<bool, NUM_OF_ROWS>, NUM_OF_COLS> currBoard, EGameState gameState, int score)
{
    // Clear canvas
    _canvas.setTo(0);
    
    // Draw Frame
    cv::Rect2d frame(FRAME_ORIGIN_X, FRAME_ORIGIN_Y, FRAME_WIDTH, FRAME_HEIGHT);
    cv::rectangle(_canvas, frame, PURPLE, FRAME_THICKNESS);

    // Draw Bricks
    for (auto row(0); row < NUM_OF_ROWS; ++row)
    {
        for (auto col(0); col < NUM_OF_COLS; ++col)
        {
            if (currBoard[col][row])
            {
                auto linkOriginX = ORIGIN_X + col * LINK_SIDE_LENGTH;
                auto linkOriginY = ORIGIN_Y + row * LINK_SIDE_LENGTH;
                cv::Rect2d link(linkOriginX, linkOriginY, LINK_SIDE_LENGTH, LINK_SIDE_LENGTH);
                cv::rectangle(_canvas, link, GREEN, cv::FILLED);
                cv::rectangle(_canvas, link, BLUE, 1);
            }
        }
    }

    // Header
    cv::putText(_canvas, "TETRIS", _headerPoint, cv::FONT_HERSHEY_SIMPLEX, 2.0, GREEN, 4);
    cv::putText(_canvas, "by Hen Orkin & Yaron Meister", cv::Point(_headerPoint.x - 20, _headerPoint.y + 25), cv::FONT_HERSHEY_SIMPLEX, 0.5, GREEN, 1);
    
    switch (gameState)
    {
    case EGameState::Play:
        DrawInstructions(score);
        break;
    case EGameState::Pause:
        DrawPauseWindow(score);
        break;
    case EGameState::Stop:
        DrawWelcome();
        break;
    }

    cv::imshow(WINDOW_NAME, _canvas);
}

////////////////////////////////////////////////////////////////////////////////
void Display::DrawWelcome()
{
    DrawWindow();

    cv::putText(_canvas, "Welcome to TETRIS", cv::Point(105.0, CANVAS_HEIGHT / 2 - 50.0),
                cv::FONT_HERSHEY_SIMPLEX, 1.5, WHITE, 2);
    cv::putText(_canvas, "Press \"R\" to start",
        cv::Point(120.0, CANVAS_HEIGHT / 2 + 50.0), cv::FONT_HERSHEY_SIMPLEX, 0.6, WHITE, 1);
    cv::putText(_canvas, "Press Esc to quit",
        cv::Point(120.0, CANVAS_HEIGHT / 2 + 100.0), cv::FONT_HERSHEY_SIMPLEX, 0.6, WHITE, 1);
}

////////////////////////////////////////////////////////////////////////////////
void Display::DrawWindow()
{
    cv::Rect2d welcomeWindow(WINDOW_ORIGIN_X, WINDOW_ORIGIN_Y, WINDOW_WIDTH, WINDOW_HEIGHT);
    cv::rectangle(_canvas, welcomeWindow, BLACK, cv::FILLED);
    cv::rectangle(_canvas, welcomeWindow, RED, 2);
}

////////////////////////////////////////////////////////////////////////////////
void Display::DrawInstructions(int score)
{
    cv::putText(_canvas, "Single step - W,A,D,S",
        _instructionsPoint,
        cv::FONT_HERSHEY_SIMPLEX, 0.5, WHITE, 1);
    cv::putText(_canvas, "Drop - X",
        cv::Point(_instructionsPoint.x, _instructionsPoint.y + SPACE_ROW),
        cv::FONT_HERSHEY_SIMPLEX, 0.5, WHITE, 1);
    cv::putText(_canvas, "Pause - P, Left mouse click",
        cv::Point(_instructionsPoint.x, _instructionsPoint.y + 2 * SPACE_ROW),
        cv::FONT_HERSHEY_SIMPLEX, 0.5, WHITE, 1);
    cv::putText(_canvas, "Stop - Esc",
        cv::Point(_instructionsPoint.x, _instructionsPoint.y + 3 * SPACE_ROW),
        cv::FONT_HERSHEY_SIMPLEX, 0.5, WHITE, 1);

    DrawScore(score);
}

////////////////////////////////////////////////////////////////////////////////
void Display::DrawScore(int score)
{
    std::ostringstream formattedScoreStr;
    formattedScoreStr << "Score: " << score;

    cv::putText(_canvas, formattedScoreStr.str(),
        cv::Point(_scorePoint.x, _scorePoint.y),
        cv::FONT_HERSHEY_SIMPLEX, 1.0, WHITE, 2);
    cv::putText(_canvas, "Record: 100",
        cv::Point(_scorePoint.x, _scorePoint.y + 2 * SPACE_ROW),
        cv::FONT_HERSHEY_SIMPLEX, 1.0, GREEN, 2);
}

////////////////////////////////////////////////////////////////////////////////
void Display::DrawPauseWindow(int score)
{
    DrawWindow();

    cv::putText(_canvas, "Game Paused", cv::Point(160.0, CANVAS_HEIGHT / 2 - 50.0),
        cv::FONT_HERSHEY_SIMPLEX, 1.5, WHITE, 2);
    cv::putText(_canvas, "Press \"P\" or click Left Mouse to continue",
        cv::Point(120.0, CANVAS_HEIGHT / 2 + 50.0), cv::FONT_HERSHEY_SIMPLEX, 0.6, WHITE, 1);

    DrawScore(score);
}
