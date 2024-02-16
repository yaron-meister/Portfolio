#pragma once

#include "Brick.hpp"

enum class EBrickType
{
    Square,
    Plus,
    Line,
    El,
    Weirdo,
    NumOfTypes
};

class Factory
{
public:
    static std::unique_ptr<Brick> CreateNewBrick(EBrickType brickType)
    {
        switch (brickType)
        {
        case EBrickType::Square:
            return std::make_unique<Square>();
        case EBrickType::Plus:
            return std::make_unique<Plus>();
        case EBrickType::Line:
            return std::make_unique<Line>();
        case EBrickType::El:
            return std::make_unique<El>();
        case EBrickType::Weirdo:
            return std::make_unique<Weirdo>();
        case EBrickType::NumOfTypes:
        default:
            break;
        }

        return nullptr;
    }
};
