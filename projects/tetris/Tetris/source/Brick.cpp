// TODO::YARON - Add documentations
// TODO::YARON - Add headres

#include "..\headers\Brick.hpp"
#include <algorithm>

////////////////////////////////////////////////////////////////////////////////
Brick::Brick()
{
    _currState = static_cast<EDirection>(rand() % static_cast<int>(EDirection::NumOfDirections));
}

////////////////////////////////////////////////////////////////////////////////
void Brick::Rotate()
{
    _lastRelativeLinks = _relativeLinks;
    RotateRight();

    _currState = static_cast<EDirection>(static_cast<int>(_currState) + 1);
    if (EDirection::NumOfDirections == _currState)
    {
        _currState = EDirection::Left;
    }
}

////////////////////////////////////////////////////////////////////////////////
void Brick::UndoRotation()
{
    _relativeLinks = _lastRelativeLinks;

    if (EDirection::Left == _currState)
    {
        _currState = EDirection::Down;
    }
    else
    {
        _currState = static_cast<EDirection>(static_cast<int>(_currState) - 1);
    }
}

////////////////////////////////////////////////////////////////////////////////
void Brick::RotateSymetric()
{
    int factor(1);
    if (EDirection::Up == _currState || EDirection::Down == _currState)
    {
        factor *= -1;
    }

    for (auto idx(0); idx < NUM_OF_RELATIVE_LINKS; ++idx)
    {
        std::swap(_relativeLinks[idx].x, _relativeLinks[idx].y);
        _relativeLinks[idx] *= factor;
    }
}

////////////////////////////////////////////////////////////////////////////////
Square::Square()
{
    switch (_currState)
    {
        case EDirection::Left:
            {
                _relativeLinks[0].x = -1;
                _relativeLinks[0].y = -1;

                _relativeLinks[1].x = 0;
                _relativeLinks[1].y = -1;

                _relativeLinks[2].x = -1;
                _relativeLinks[2].y = 0;
            }
            break;
        case EDirection::Up:
            {
                _relativeLinks[0].x = 0;
                _relativeLinks[0].y = -1;

                _relativeLinks[1].x = 1;
                _relativeLinks[1].y = -1;

                _relativeLinks[2].x = 1;
                _relativeLinks[2].y = 0;
            }
            break;
        case EDirection::Right:
            {
                _relativeLinks[0].x = 1;
                _relativeLinks[0].y = 0;

                _relativeLinks[1].x = 0;
                _relativeLinks[1].y = 1;

                _relativeLinks[2].x = 1;
                _relativeLinks[2].y = 1;
            }
            break;
        case EDirection::Down:
            {
                _relativeLinks[0].x = -1;
                _relativeLinks[0].y = 0;

                _relativeLinks[1].x = -1;
                _relativeLinks[1].y = 1;

                _relativeLinks[2].x = 0;
                _relativeLinks[2].y = 1;
            }
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////
void Square::RotateRight()
{
    // TODO::YARON - Optimize
    switch (_currState)
    {
    case EDirection::Left:
        {
            _relativeLinks[0].x = 0;
            _relativeLinks[0].y = -1;

            _relativeLinks[1].x = 1;
            _relativeLinks[1].y = -1;

            _relativeLinks[2].x = 0;
            _relativeLinks[2].y = 1;
        }
        break;
    case EDirection::Up:
        {
            _relativeLinks[0].x = 1;
            _relativeLinks[0].y = 0;

            _relativeLinks[1].x = 1;
            _relativeLinks[1].y = 1;

            _relativeLinks[2].x = 0;
            _relativeLinks[2].y = 1;
        }
        break;
    case EDirection::Right:
        {
            _relativeLinks[0].x = 0;
            _relativeLinks[0].y = 1;

            _relativeLinks[1].x = -1;
            _relativeLinks[1].y = 1;

            _relativeLinks[2].x = -1;
            _relativeLinks[2].y = 0;
        }
        break;
    case EDirection::Down:
        {
            _relativeLinks[0].x = -1;
            _relativeLinks[0].y = 0;

            _relativeLinks[1].x = -1;
            _relativeLinks[1].y = -1;

            _relativeLinks[2].x = 0;
            _relativeLinks[2].y = -1;
        }
        break;
    }
}


////////////////////////////////////////////////////////////////////////////////
Plus::Plus()
{
    switch (_currState)
    {
    case EDirection::Left:
    {
        _relativeLinks[0].x = -1;
        _relativeLinks[0].y = 0;

        _relativeLinks[1].x = 0;
        _relativeLinks[1].y = -1;

        _relativeLinks[2].x = 0;
        _relativeLinks[2].y = 1;
    }
    break;
    case EDirection::Up:
    {
        _relativeLinks[0].x = -1;
        _relativeLinks[0].y = 0;

        _relativeLinks[1].x = 0;
        _relativeLinks[1].y = -1;

        _relativeLinks[2].x = 1;
        _relativeLinks[2].y = 0;
    }
    break;
    case EDirection::Right:
    {
        _relativeLinks[0].x = 0;
        _relativeLinks[0].y = -1;

        _relativeLinks[1].x = 1;
        _relativeLinks[1].y = 0;

        _relativeLinks[2].x = 0;
        _relativeLinks[2].y = 1;
    }
    break;
    case EDirection::Down:
    {
        _relativeLinks[0].x = -1;
        _relativeLinks[0].y = 0;

        _relativeLinks[1].x = 1;
        _relativeLinks[1].y = 0;

        _relativeLinks[2].x = 0;
        _relativeLinks[2].y = 1;
    }
    break;
    }
}

////////////////////////////////////////////////////////////////////////////////
void Plus::RotateRight()
{
    RotateSymetric();
}

////////////////////////////////////////////////////////////////////////////////
Line::Line()
{
    switch (_currState)
    {
    case EDirection::Left:
        {
            _relativeLinks[0].x = -1;
            _relativeLinks[0].y = 0;

            _relativeLinks[1].x = -2;
            _relativeLinks[1].y = 0;

            _relativeLinks[2].x = -3;
            _relativeLinks[2].y = 0;
        }
        break;
    case EDirection::Up:
        {
            _relativeLinks[0].x = 0;
            _relativeLinks[0].y = -1;

            _relativeLinks[1].x = 0;
            _relativeLinks[1].y = -2;

            _relativeLinks[2].x = 0;
            _relativeLinks[2].y = -3;
        }
        break;
    case EDirection::Right:
        {
            _relativeLinks[0].x = 1;
            _relativeLinks[0].y = 0;

            _relativeLinks[1].x = 2;
            _relativeLinks[1].y = 0;

            _relativeLinks[2].x = 3;
            _relativeLinks[2].y = 0;
        }
        break;
    case EDirection::Down:
        {
            _relativeLinks[0].x = 0;
            _relativeLinks[0].y = 1;

            _relativeLinks[1].x = 0;
            _relativeLinks[1].y = 2;

            _relativeLinks[2].x = 0;
            _relativeLinks[2].y = 3;
        }
        break;
    }
}

////////////////////////////////////////////////////////////////////////////////
void Line::RotateRight()
{
    RotateSymetric();
}

////////////////////////////////////////////////////////////////////////////////
El::El()
{
    switch (_currState)
    {
    case EDirection::Left:
        {
            _relativeLinks[0].x = -2;
            _relativeLinks[0].y = 0;

            _relativeLinks[1].x = -1;
            _relativeLinks[1].y = 0;

            _relativeLinks[2].x = 0;
            _relativeLinks[2].y = -1;
        }
        break;
    case EDirection::Up:
        {
            _relativeLinks[0].x = 0;
            _relativeLinks[0].y = -2;

            _relativeLinks[1].x = 0;
            _relativeLinks[1].y = -1;

            _relativeLinks[2].x = 1;
            _relativeLinks[2].y = 0;
        }
        break;
    case EDirection::Right:
        {
            _relativeLinks[0].x = 1;
            _relativeLinks[0].y = 0;

            _relativeLinks[1].x = 2;
            _relativeLinks[1].y = 0;

            _relativeLinks[2].x = 0;
            _relativeLinks[2].y = 1;
        }
        break;
    case EDirection::Down:
        {
            _relativeLinks[0].x = -1;
            _relativeLinks[0].y = 0;

            _relativeLinks[1].x = 0;
            _relativeLinks[1].y = 1;

            _relativeLinks[2].x = 0;
            _relativeLinks[2].y = 2;
        }
        break;
    }
}

////////////////////////////////////////////////////////////////////////////////
void El::RotateRight()
{
    // TODO::YARON - Optimize
    switch (_currState)
    {
    case EDirection::Left:
        {
            _relativeLinks[0].x = 0;
            _relativeLinks[0].y = -2;

            _relativeLinks[1].x = 0;
            _relativeLinks[1].y = -1;

            _relativeLinks[2].x = 1;
            _relativeLinks[2].y = 0;
        }
    break;
    case EDirection::Up:
        {
            _relativeLinks[0].x = 1;
            _relativeLinks[0].y = 0;

            _relativeLinks[1].x = 2;
            _relativeLinks[1].y = 0;

            _relativeLinks[2].x = 0;
            _relativeLinks[2].y = 1;
        }
        break;
    case EDirection::Right:
        {
            _relativeLinks[0].x = -1;
            _relativeLinks[0].y = 0;

            _relativeLinks[1].x = 0;
            _relativeLinks[1].y = 1;

            _relativeLinks[2].x = 0;
            _relativeLinks[2].y = 2;
        }
        break;
    case EDirection::Down:
        {
            _relativeLinks[0].x = -2;
            _relativeLinks[0].y = 0;

            _relativeLinks[1].x = -1;
            _relativeLinks[1].y = 0;

            _relativeLinks[2].x = 0;
            _relativeLinks[2].y = -1;
        }
        break;
    }
}

////////////////////////////////////////////////////////////////////////////////
Weirdo::Weirdo()
{
    switch (_currState)
    {
    case EDirection::Left:
        {
            _relativeLinks[0].x = -1;
            _relativeLinks[0].y = 0;

            _relativeLinks[1].x = 0;
            _relativeLinks[1].y = 1;

            _relativeLinks[2].x = 1;
            _relativeLinks[2].y = 1;
        }
        break;
    case EDirection::Up:
        {
            _relativeLinks[0].x = 0;
            _relativeLinks[0].y = -1;

            _relativeLinks[1].x = -1;
            _relativeLinks[1].y = 0;

            _relativeLinks[2].x = -1;
            _relativeLinks[2].y = 1;
        }
        break;
    case EDirection::Right:
        {
            _relativeLinks[0].x = -1;
            _relativeLinks[0].y = -1;

            _relativeLinks[1].x = 0;
            _relativeLinks[1].y = -1;

            _relativeLinks[2].x = 1;
            _relativeLinks[2].y = 0;
        }
        break;
    case EDirection::Down:
        {
            _relativeLinks[0].x = 1;
            _relativeLinks[0].y = -1;

            _relativeLinks[1].x = 1;
            _relativeLinks[1].y = 0;

            _relativeLinks[2].x = 0;
            _relativeLinks[2].y = 1;
        }
        break;
    }
}

////////////////////////////////////////////////////////////////////////////////
void Weirdo::RotateRight()
{
    // TODO::YARON - Optimize
    switch (_currState)
    {
    case EDirection::Left:
        {
            _relativeLinks[0].x = 0;
            _relativeLinks[0].y = -1;

            _relativeLinks[1].x = -1;
            _relativeLinks[1].y = 0;

            _relativeLinks[2].x = -1;
            _relativeLinks[2].y = 1;
        }
        break;
    case EDirection::Up:
        {
            _relativeLinks[0].x = -1;
            _relativeLinks[0].y = -1;

            _relativeLinks[1].x = 0;
            _relativeLinks[1].y = -1;

            _relativeLinks[2].x = 1;
            _relativeLinks[2].y = 0;
        }
        break;
    case EDirection::Right:
        {
            _relativeLinks[0].x = 1;
            _relativeLinks[0].y = -1;

            _relativeLinks[1].x = 1;
            _relativeLinks[1].y = 0;

            _relativeLinks[2].x = 0;
            _relativeLinks[2].y = 1;
        }
        break;
    case EDirection::Down:
        {
            _relativeLinks[0].x = -1;
            _relativeLinks[0].y = 0;

            _relativeLinks[1].x = 0;
            _relativeLinks[1].y = 1;

            _relativeLinks[2].x = 1;
            _relativeLinks[2].y = 1;
        }
        break;
    }
}
