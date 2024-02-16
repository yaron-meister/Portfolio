#pragma once

#include "Board.hpp"

class Display
{
public:
    const cv::Scalar GREEN = cv::Scalar(0, 255, 0);
    const cv::Scalar RED = cv::Scalar(0, 0, 255);
    const cv::Scalar BLUE = cv::Scalar(255, 0, 0);
    const cv::Scalar PURPLE = cv::Scalar(255, 0, 255);
    const cv::Scalar WHITE = cv::Scalar(255, 255, 255);
    const cv::Scalar BLACK = cv::Scalar(0, 0, 0);

    const unsigned int FRAME_THICKNESS = 4;
    const unsigned int LINK_SIDE_LENGTH = 20;
    const double FRAME_WIDTH = NUM_OF_COLS * LINK_SIDE_LENGTH + (2 * FRAME_THICKNESS);
    const double FRAME_HEIGHT = NUM_OF_ROWS * LINK_SIDE_LENGTH + (2 * FRAME_THICKNESS);
    const double FRAME_ORIGIN_X = 0.0;
    const double FRAME_ORIGIN_Y = 0.0;
    const double ORIGIN_X = 4.0;
    const double ORIGIN_Y = 4.0;
    const double CANVAS_HEIGHT = 648.0;
    const double CANVAS_WIDTH = 648.0;
    const double WINDOW_WIDTH = 500.0;
    const double WINDOW_HEIGHT = 300.0;
    const double WINDOW_ORIGIN_X = CANVAS_WIDTH / 2 - WINDOW_WIDTH / 2 + ORIGIN_X;
    const double WINDOW_ORIGIN_Y = CANVAS_HEIGHT / 2 - WINDOW_HEIGHT / 2 + ORIGIN_Y;
    const double SPACE_ROW = 25.0;

    // TODO::YARON - Handle warnings
    Display();

    void Refresh(std::array<std::array<bool, NUM_OF_ROWS>, NUM_OF_COLS> currBoard, EGameState gameState, int score);

private:
    void DrawWelcome();
    void DrawWindow();
    void DrawInstructions(int score);
    void DrawScore(int score);
    void DrawPauseWindow(int score);

    cv::Mat _canvas;
    cv::Point _headerPoint;
    cv::Point _instructionsPoint;
    cv::Point _scorePoint;
};
