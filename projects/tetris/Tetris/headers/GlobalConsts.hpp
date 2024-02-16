#pragma once

#include <opencv2/core.hpp>

enum class EGameState
{
    Play,
    Pause,
    Stop
};

enum class EDirection
{
    Left,
    Up,
    Right,
    Down,
    NumOfDirections
};

constexpr int NUM_OF_ROWS = 32;
constexpr int NUM_OF_COLS = 16;
constexpr unsigned int NUM_OF_BRICK_LINKS = 4;
constexpr unsigned int NUM_OF_RELATIVE_LINKS = NUM_OF_BRICK_LINKS - 1;
const cv::String WINDOW_NAME = "Game";
