#pragma once

#include "Brick.hpp"
#include "Board.hpp"
#include "Display.hpp"
#include <optional>

// A struct for representing optional user input
// for a certain frame
struct GameStateInput
{
    GameStateInput()
    {
        gameState.store(EGameState::Stop);
    }

    std::atomic<EGameState> gameState;
};

constexpr int NO_PRESS = -1;
constexpr int LEFT_KEY = 37;
constexpr int UP_KEY = 38;
constexpr int RIGHT_KEY = 39;
constexpr int DOWN_KEY = 40;
constexpr int ESC_KEY = 27;

class Tetris
{
    enum class EOperation
    {
        Rotate,
        MoveLeft,
        MoveRight,
        MoveDown,
        Drop
    };

public:
    Tetris() : _isRunning(true), _score(0)
    {
        _gameStateInput.gameState.store(EGameState::Stop);
    }

    void Run();
    void CallNewBrick();

private:
    void RunBrickRoutine();
    void CheckForInputs();
    void StartNewGame();
    void EndGame();
    void Move(EOperation operation);
    EBrickState MoveOneStep(EDirection direction);
    void UpdatePosition(std::array<cv::Point2i, NUM_OF_BRICK_LINKS> newBrickPosition);
    void Rotate();

    int _score;
    std::atomic_bool _isRunning;
    GameStateInput _gameStateInput;
    std::unique_ptr<Brick> _currBrick;
    std::array<cv::Point2i, NUM_OF_BRICK_LINKS> _currBrickPosition;
    Board _board;
    Display _display;
    std::mutex _moveMutex;
    std::mutex _pauseMutex;
};