/*****************************************************************************
 * File name:   shapes.cpp
 * Developer:   Yaron Meister
 * Reviewer:    Majd
 * Date:        2019-02-25 15:31:15
 * Description: Shapes implementation
 *****************************************************************************/
 
#include <iostream>     /* 		cout, cerr		*/

#include "shapes.h"     /* Forward declarations */



using namespace ilrd;
/*******************************************************************************
                           Functions Implementations
*******************************************************************************/
/******************************************************************************/
/* Color::Implementation */
/******************************************************************************/
Color::Color(unsigned char r, unsigned char g, unsigned char b) :
                                                          m_r(r), m_g(g), m_b(b)
{}

/********************                                      ********************/
unsigned char Color::GetR() const
{
    return (m_r);
}

/********************                                      ********************/
unsigned char Color::GetG() const
{
    return (m_g);
}

/********************                                      ********************/
unsigned char Color::GetB() const
{
    return (m_b);
}

/********************                                      ********************/
void Color::SetR(unsigned char r)
{
    m_r = r;
}

/********************                                      ********************/
void Color::SetG(unsigned char g)
{
    m_g = g;
}

/********************                                      ********************/
void Color::SetB(unsigned char b)
{
    m_b = b;
}


/* Point::Implementation */
/******************************************************************************/
Point::Point(long int x, long int y) : m_x(x), m_y(y)
{}

/********************                                      ********************/
void Point::SetX(long int x)
{
    m_x = x;
}

/********************                                      ********************/
void Point::SetY(long int y)
{
    m_y = y;
}

/********************                                      ********************/
long int Point::GetX() const
{
    return (m_x);
}

/********************                                      ********************/
long int Point::GetY() const
{
    return (m_y);
}

/********************                                      ********************/
const Point Point::operator+(const Point& rhs)
{
    Point sum(m_x, m_y); // Initialize 'sum' as 'this'

    sum += rhs;

    return (sum);
}

/********************                                      ********************/
const Point Point::operator-(const Point& rhs)
{
    Point diff(m_x, m_y); // Initialize 'diff' as 'this'

    diff -= rhs;

    return (diff);
}

/********************                                      ********************/
Point& Point::operator+=(const Point& point)
{
    m_x += point.GetX();
    m_y += point.GetY();

    return (*this);
}

/********************                                      ********************/
Point& Point::operator-=(const Point& point)
{
    m_x -= point.GetX();
    m_y -= point.GetY();
    
    return (*this);
}

/********************                                      ********************/
Point& Point::operator*=(double multiplier)
{
    m_x *= multiplier;
    m_y *= multiplier;

    return (*this);
}

/********************                                      ********************/
Point& Point::operator/=(double multiplier)
{
    m_x /= multiplier;
    m_y /= multiplier;

    return (*this);
}


/* Group::Implementation */
// Use cpp's vector API
/******************************************************************************/
Group::~Group()
{
    // While the group's vector is NOT empty, pop
    /*
    while (! m_members.empty())
    {
        m_members.pop_back();
    }
    */

   m_members.clear();
}

/********************                                      ********************/
const Point Group::GetCenter() const
{
    // Group's center point is calculated as the average point of
    //                       all of the shapes's center points in the group
    // AVG = sum(center points) / num_of_members
    std::size_t size = m_members.size();
    Point center;

    for (std::size_t i = 0; i < size; ++i)
    {
        center += m_members[i]->GetCenter();
    }

    return (center /= size);
}

/********************                                      ********************/
void Group::Move(const Point& new_point)
{
    std::size_t size = m_members.size();

    for (std::size_t i = 0; i < size; ++i)
    {
        m_members[i]->Move(new_point);
    }
}

/********************                                      ********************/
void Group::SetColor(const Color& new_color)
{
    std::size_t size = m_members.size();

    for (std::size_t i = 0; i < size; ++i)
    {
        m_members[i]->SetColor(new_color);
    }
}

/********************                                      ********************/
void Group::Draw(Renderer &renderer)
{
    std::size_t size = m_members.size();

    for (std::size_t i = 0; i < size; ++i)
    {
        m_members[i]->Draw(renderer);
    }
}

/********************                                      ********************/
void Group::Scale(double multiplier)
{
    std::size_t size = m_members.size();

    for (std::size_t i = 0; i < size; ++i)
    {
        m_members[i]->Scale(multiplier); 
    }
}

/********************                                      ********************/
void Group::AddMember(Composite* shape)
{
    m_members.push_back(shape);
}


/* Shape::Implementation */
/******************************************************************************/
Shape::Shape(const Color& color, const Point& center) :
                                                m_color(color), m_center(center)
{}

/********************                                      ********************/
const Point Shape::GetCenter() const
{
    return (m_center);
}

/********************                                      ********************/
void Shape::Move(const Point& relative_point)
{
    m_center += relative_point;
}

/********************                                      ********************/
void Shape::SetColor(const Color& color)
{
    m_color = color;
}

/********************                                      ********************/
const Color& Shape::GetColor() const
{
    return (m_color);
}


/* Line::Implementation */
/******************************************************************************/
Line::Line(const Color& color, 
               const Point& first_point, const Point& second_point) :
      Shape(color, GetLineCenter(first_point, second_point)),
      m_first_point(first_point), m_second_point(second_point)
{
    // Translation from absolute coordinates to relative ones
    m_first_point  -= GetCenter();
    m_second_point -= GetCenter();  
}

/********************                                      ********************/
const Point Line::GetFirstPoint() const
{
    return (m_first_point);
}

/********************                                      ********************/
const Point Line::GetSecondPoint() const
{
    return (m_second_point);
}

/********************                                      ********************/
void Line::SetFirstPoint(const Point& new_point)
{
    m_first_point = new_point;
}

/********************                                      ********************/
void Line::SetSecondPoint(const Point& new_point)
{
    m_second_point = new_point;
}       
               
/********************                                      ********************/
void Line::Scale(double multiplier)
{
    m_first_point  *= multiplier;
    m_second_point *= multiplier;
}

/********************                                      ********************/
void Line::Draw(Renderer& renderer)
{
    // Drawing according to absolute coordinates
    Point first_point  = m_first_point  + GetCenter();
    Point second_point = m_second_point + GetCenter();
    
    renderer.DrawLine(first_point, second_point, GetColor());
}

/********************                                      ********************/
const Point Line::GetLineCenter(const Point& first_point,
                                                const Point& second_point) const
{
    // Initialize avg(sum X, sum Y)
    Point avg(first_point.GetX() + second_point.GetX(), 
              first_point.GetY() + second_point.GetY());

    return (avg /= 2);
}


/* Rectangle::Implementation */
/******************************************************************************/
Rectangle::Rectangle(const Color& color, const Point& center,
                     const std::size_t height, const std::size_t width) : 
           Shape(color, center), m_width(width), m_height(height)
{}

/********************                                      ********************/
const std::size_t Rectangle::GetWidth() const
{
    return (m_width);
}

/********************                                      ********************/
const std::size_t Rectangle::GetHeight() const
{
    return (m_height);
}

/********************                                      ********************/
void Rectangle::SetWidth(const std::size_t new_width)
{
    m_width = new_width;
}

/********************                                      ********************/
void Rectangle::SetHeight(const std::size_t new_height)
{
    m_height = new_height;
}      

/********************                                      ********************/
void Rectangle::Draw(Renderer& renderer)
{
    // Top-Left point of a rectangle is a half size from the center point
    //                                                   for each coordinate
    Point top_left(GetCenter().GetX() - (m_width / 2),
                                           GetCenter().GetY() - (m_height / 2));
    
    renderer.FillRectangle(top_left, m_width, m_height, GetColor());
}

/********************                                      ********************/
void Rectangle::Scale(double multiplier)
{
    m_width  *= multiplier;
    m_height *= multiplier;
}

/* Square::Implementation */
// SQUARE can't be an inheritant of a RECTANGLE 
/******************************************************************************/
Square::Square(const Color& color, const Point& center, const std::size_t side): 
        Shape(color, center), m_side(side)
{}

/********************                                      ********************/
const std::size_t Square::GetSide() const
{
    return (m_side);
}

/********************                                      ********************/
void Square::SetSide(const std::size_t new_side)
{
    m_side = new_side;
}

/********************                                      ********************/
void Square::Draw(Renderer& renderer)
{
    // Top-Left point of a square is a half size from the center point
    //
    Point top_left(GetCenter().GetX() - (m_side / 2),
                                           GetCenter().GetY() - (m_side / 2));
    
    renderer.FillRectangle(top_left, m_side, m_side, GetColor());
}

/********************                                      ********************/
void Square::Scale(double multiplier)
{
    m_side  *= multiplier;
}

/* Circle::Implementation */
/******************************************************************************/
Circle::Circle(const Color& color, const Point& center,
               const std::size_t radius) : 
           Shape(color, center), m_radius(radius)
{}

/********************                                      ********************/
const std::size_t Circle::GetRadius() const
{
    return (m_radius);
}

/********************                                      ********************/
void Circle::SetRadius(const std::size_t new_radius)
{
    m_radius = new_radius;
}

/********************                                      ********************/
void Circle::Draw(Renderer &renderer)
{
    renderer.FillCircle(GetCenter(), m_radius, GetColor());
}

/********************                                      ********************/
void Circle::Scale(double multiplier)
{
    m_radius *= multiplier;
}

/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/   
