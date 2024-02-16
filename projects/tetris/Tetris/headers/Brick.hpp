#pragma once

#include "GlobalConsts.hpp"

#include <array>
#include <opencv2/highgui/highgui.hpp>

class Brick
{
public:

    Brick();
    virtual ~Brick() {}

    void Rotate();
    void UndoRotation();
    inline std::array<cv::Point2i, NUM_OF_RELATIVE_LINKS> GetState() { return _relativeLinks; }

protected:
    virtual void RotateRight() = 0;
    void RotateSymetric();

    std::array<cv::Point2i, NUM_OF_RELATIVE_LINKS> _relativeLinks;
    std::array<cv::Point2i, NUM_OF_RELATIVE_LINKS> _lastRelativeLinks;
    EDirection _currState;
};

class Square : public Brick
{
public:
    Square();
    ~Square(){}

    virtual void RotateRight() override;
};

class Plus : public Brick
{
public:
    Plus();
    ~Plus(){}

    virtual void RotateRight() override;
};

class Line : public Brick
{
public:
    Line();
    ~Line(){}

    virtual void RotateRight() override;
};

class El : public Brick
{
public:
    El();
    ~El(){}

    virtual void RotateRight() override;
};

class Weirdo : public Brick
{
public:
    Weirdo();
    ~Weirdo(){}

    virtual void RotateRight() override;
};
