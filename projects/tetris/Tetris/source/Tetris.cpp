
#include "Tetris.hpp"
#include "Factory.hpp"
#include <thread>

////////////////////////////////////////////////////////////////////////////////
void Tetris::Run()
{
    cv::namedWindow(WINDOW_NAME, 1);
    cv::setMouseCallback(WINDOW_NAME, [](int event, int x, int y, int flags, void* userdata) {
        
        if (event == cv::EVENT_LBUTTONDOWN)
        {
            auto gameStateInput = static_cast<GameStateInput*>(userdata);
            auto gameState = gameStateInput->gameState.load(std::memory_order_relaxed);
            switch (gameState)
            {
            case EGameState::Play:
                gameStateInput->gameState.store(EGameState::Pause);
                break;
            case EGameState::Pause:
                gameStateInput->gameState.store(EGameState::Play);
                break;
            }
        }
    }, &_gameStateInput);

    std::thread brickRoutineThread(&Tetris::RunBrickRoutine, this);
    while (_isRunning)
    {
        CheckForInputs();
        _display.Refresh(_board.GetBoard(), _gameStateInput.gameState.load(std::memory_order_relaxed), _score);
    }

    brickRoutineThread.join();
}

////////////////////////////////////////////////////////////////////////////////
void Tetris::RunBrickRoutine()
{
    auto brickState(EBrickState::Floating);
    while (_isRunning)
    {
        if (EGameState::Play == _gameStateInput.gameState.load(std::memory_order_relaxed))
        {
            brickState = MoveOneStep(EDirection::Down);
            switch (brickState)
            {
            case EBrickState::Landed:
                CallNewBrick();
                break;
            case EBrickState::ReachedUp:
                EndGame();
                break;
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

////////////////////////////////////////////////////////////////////////////////
void Tetris::CheckForInputs()
{
    auto keyVal = cv::waitKey(1);

    if (NO_PRESS == keyVal)
    {
        return;
    }

    switch (keyVal)
    {
    case 'r':
    case 'R':
        if (EGameState::Stop == _gameStateInput.gameState.load(std::memory_order_relaxed))
        {
            StartNewGame();
        }
        break;
    case LEFT_KEY:
    case 'a':
    case 'A':
        Move(EOperation::MoveLeft);
        break;
    case UP_KEY:
    case 'w':
    case 'W':
        Move(EOperation::Rotate);
        break;
    case RIGHT_KEY:
    case 'd':
    case 'D':
        Move(EOperation::MoveRight);
        break;
    case DOWN_KEY:
    case 's':
    case 'S':
        Move(EOperation::MoveDown);
        break;
    case 'x':
    case 'X':
        Move(EOperation::Drop);
        break;
    case 'p':
    case 'P':
        switch (_gameStateInput.gameState.load(std::memory_order_relaxed))
        {
        case EGameState::Play:
            _gameStateInput.gameState.store(EGameState::Pause);
            break;
        case EGameState::Pause:
            _gameStateInput.gameState.store(EGameState::Play);
            break;
        }
        break;
    case 'o':
    case 'O':
        EndGame();
        break;
    case ESC_KEY:
        _isRunning = false;
        break;
    }
}

////////////////////////////////////////////////////////////////////////////////
void Tetris::StartNewGame()
{
    CallNewBrick();
    _gameStateInput.gameState.store(EGameState::Play);
}

////////////////////////////////////////////////////////////////////////////////
void Tetris::EndGame()
{
    _score = 0;
    _board.ResetBoard();
    _gameStateInput.gameState.store(EGameState::Stop);
}

////////////////////////////////////////////////////////////////////////////////
void Tetris::Move(EOperation operation)
{
    if (EGameState::Play == _gameStateInput.gameState.load(std::memory_order_relaxed))
    {
        switch (operation)
        {
        case EOperation::Rotate:
            // TODO::YARON - Make sure Rotate is valid and if not push it
            Rotate();
            break;
        case EOperation::MoveLeft:
            MoveOneStep(EDirection::Left);
            break;
        case EOperation::MoveRight:
            MoveOneStep(EDirection::Right);
            break;
        case EOperation::MoveDown:
            MoveOneStep(EDirection::Down);
            break;
        case EOperation::Drop:
            auto brickState(EBrickState::Floating);
            while (EBrickState::Floating == brickState)
            {
                brickState = MoveOneStep(EDirection::Down);
            }
            break;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
EBrickState Tetris::MoveOneStep(EDirection direction)
{
    std::lock_guard<std::mutex> moveLock(_moveMutex);

    std::array<cv::Point2i, NUM_OF_BRICK_LINKS> newBrickPosition(_currBrickPosition);

    switch (direction)
    {
    case EDirection::Left:
        for (auto idx(0); idx < NUM_OF_BRICK_LINKS; ++idx)
        {
            newBrickPosition[idx].x -= 1;
        }
        break;
    case EDirection::Right:
        for (auto idx(0); idx < NUM_OF_BRICK_LINKS; ++idx)
        {
            newBrickPosition[idx].x += 1;
        }
        break;
    case EDirection::Down:
        for (auto idx(0); idx < NUM_OF_BRICK_LINKS; ++idx)
        {
            newBrickPosition[idx].y += 1;
        }
        break;
        // Up is not a valid move in Tetris
    case EDirection::Up:
    default:
        break;
    }

    if (!_board.IsPossibleMove(newBrickPosition))
    {
        for (auto point : newBrickPosition)
        {
            if (direction == EDirection::Down)
            {
                for (auto point : newBrickPosition)
                {
                    if (point.y < 0)
                    {
                        return EBrickState::ReachedUp;
                    }
                }

                // If a row has being deleted
                if (_board.HandleLanding())
                {
                    _score += 10;
                }

                return EBrickState::Landed;
            }
            else
            {
                return EBrickState::ReachedWall;
            }
        }
    }

    UpdatePosition(newBrickPosition);

    return EBrickState::Floating;
}

////////////////////////////////////////////////////////////////////////////////
void Tetris::UpdatePosition(std::array<cv::Point2i, NUM_OF_BRICK_LINKS> newBrickPosition)
{
    _currBrickPosition = newBrickPosition;
    _board.Update(_currBrickPosition);
}

////////////////////////////////////////////////////////////////////////////////
void Tetris::Rotate()
{
    std::lock_guard<std::mutex> moveLock(_moveMutex);

    _currBrick->Rotate();

    auto currBrickState = _currBrick->GetState();
    auto numOfRelativeLinks = currBrickState.size();
    auto rotatedPosition = _currBrickPosition;
    
    for (auto idx(0); idx < numOfRelativeLinks; ++idx)
    {
        rotatedPosition[idx + 1].x = rotatedPosition[0].x + currBrickState[idx].x;
        rotatedPosition[idx + 1].y = rotatedPosition[0].y + currBrickState[idx].y;
    }

    // TODO::YARON - Try moving sides if possible
    if (_board.IsPossibleMove(rotatedPosition))
    {
        UpdatePosition(rotatedPosition);
    }
    else
    {
        _currBrick->UndoRotation();
    }
}

////////////////////////////////////////////////////////////////////////////////
void Tetris::CallNewBrick()
{
    auto newBrickType = static_cast<EBrickType>(rand() % static_cast<int>(EBrickType::NumOfTypes));
    
    _currBrickPosition[0].x = (NUM_OF_COLS / 2) - 1;
    _currBrickPosition[0].y = -1;
    _currBrick = Factory::CreateNewBrick(newBrickType);

    auto currBrickState = _currBrick->GetState();
    auto numOfRelativeLinks = currBrickState.size();
    for (auto idx(0); idx < numOfRelativeLinks; ++idx)
    {
        _currBrickPosition[idx + 1].x = _currBrickPosition[0].x + currBrickState[idx].x;
        _currBrickPosition[idx + 1].y = _currBrickPosition[0].y + currBrickState[idx].y;
    }
}
