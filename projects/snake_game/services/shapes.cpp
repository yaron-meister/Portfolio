/*****************************************************************************
* File name:   shapes.cpp
* Developer:   Yaron
* Date:        2021-02-19 11:04:53
* Description: Source file for graphical shapes rendering
*****************************************************************************/

#include "shapes.h"


// Namespaces
using namespace std;

// Macros

// Global variables

/////////////////////////////////////////////////////////////////////////////
//                        Functions's implementations
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
CGroup::~CGroup()
{
  m_members.clear();
}

/////////////////////////////////////////////////////////////////////////////
const CPos CGroup::getCenter() const
{
  // Group's center point is calculated as the average point of
  //                       all of the shapes's center points in the group
  // AVG = sum(center points) / num_of_members
  size_t size = m_members.size();
  CPos center;

  for (size_t i = 0; i < size; ++i)
  {
    center += m_members[i]->getCenter();
  }

  return (center /= static_cast<int>(size));
}

/////////////////////////////////////////////////////////////////////////////
void CGroup::move(const CPos& new_point)
{
  size_t size = m_members.size();

  for (size_t i = 0; i < size; ++i)
  {
    m_members[i]->move(new_point);
  }
}

/////////////////////////////////////////////////////////////////////////////
void CGroup::setColor(const CColor& new_color)
{
  size_t size = m_members.size();

  for (size_t i = 0; i < size; ++i)
  {
    m_members[i]->setColor(new_color);
  }
}

/////////////////////////////////////////////////////////////////////////////
void CGroup::draw(CRenderer& renderer) const
{
  size_t size = m_members.size();

  for (size_t i = 0; i < size; ++i)
  {
    m_members[i]->draw(renderer);
  }
}

/////////////////////////////////////////////////////////////////////////////
void CGroup::scale(int multiplier)
{
  size_t size = m_members.size();

  for (size_t i = 0; i < size; ++i)
  {
    m_members[i]->scale(multiplier);
  }
}

/////////////////////////////////////////////////////////////////////////////
void CGroup::addMember(CComposite* shape)
{
  m_members.push_back(shape);
}

/////////////////////////////////////////////////////////////////////////////
void CGroup::removeOldestMember()
{
  deque<CComposite*>::iterator it = m_members.begin();
  delete(*it);
  *it = nullptr;
  m_members.pop_front();
}

/////////////////////////////////////////////////////////////////////////////
size_t CGroup::getMembersNum() const
{
  return (m_members.size());
}

// CSuperGroup::Implementation 
/////////////////////////////////////////////////////////////////////////////
void CSuperGroup::addGroup(const CGroup* group)
{
  if (nullptr != group)
  {
    m_groups.push_back(group);
  }
}

/////////////////////////////////////////////////////////////////////////////
void CSuperGroup::draw(CRenderer& renderer)
{
  for (vector<const CGroup*>::iterator it = m_groups.begin(); it != m_groups.end(); ++it)
  {
    (*it)->draw(renderer);
  }
}

// CShape::Implementation 
/////////////////////////////////////////////////////////////////////////////
CShape::CShape(const CColor& color, const CPos& center) :
  m_color(color), m_center(center)
{}

/////////////////////////////////////////////////////////////////////////////
const CPos CShape::getCenter() const
{
  return (m_center);
}

/////////////////////////////////////////////////////////////////////////////
void CShape::setCenter(CPos newCenter)
{
  m_center = newCenter;
}

/////////////////////////////////////////////////////////////////////////////
void CShape::move(const CPos& relative_point)
{
  m_center += relative_point;
}

/////////////////////////////////////////////////////////////////////////////
void CShape::setColor(const CColor& color)
{
  m_color = color;
}

/////////////////////////////////////////////////////////////////////////////
const CColor& CShape::getColor() const
{
  return (m_color);
}


// CLine::Implementation 
/////////////////////////////////////////////////////////////////////////////
CLine::CLine(const CColor& color, const CPos& first_point, const CPos& second_point) :
  CShape(color, getLineCenter(first_point, second_point)),
  m_firstPoint(first_point), m_secondPoint(second_point)
{
  // Translation from absolute coordinates to relative ones
  m_firstPoint -= getCenter();
  m_secondPoint -= getCenter();
}

/////////////////////////////////////////////////////////////////////////////
const CPos CLine::getFirstPoint() const
{
  return (m_firstPoint);
}

/////////////////////////////////////////////////////////////////////////////
const CPos CLine::getSecondPoint() const
{
  return (m_secondPoint);
}

/////////////////////////////////////////////////////////////////////////////
void CLine::setFirstPoint(const CPos& new_point)
{
  m_firstPoint = new_point;
}

/////////////////////////////////////////////////////////////////////////////
void CLine::setSecondPoint(const CPos& new_point)
{
  m_secondPoint = new_point;
}

/////////////////////////////////////////////////////////////////////////////
void CLine::scale(int multiplier)
{
  m_firstPoint *= multiplier;
  m_secondPoint *= multiplier;
}

/////////////////////////////////////////////////////////////////////////////
void CLine::draw(CRenderer& renderer) const
{
  // Drawing according to absolute coordinates
  CPos first_point = const_cast<CPos&>(m_firstPoint) + getCenter();
  CPos second_point = const_cast<CPos&>(m_secondPoint) + getCenter();

  renderer.drawLine(first_point, second_point, getColor());
}

/////////////////////////////////////////////////////////////////////////////
const CPos CLine::getLineCenter(const CPos& first_point, const CPos& second_point) const
{
  // Initialize avg(sum X, sum Y)
  CPos avg(first_point.getX() + second_point.getX(),
    first_point.getY() + second_point.getY());

  return (avg /= 2);
}


// CRectangle::Implementation 
/////////////////////////////////////////////////////////////////////////////
CRectangle::CRectangle(const CColor& color, const CPos& center,
  const size_t height, const size_t width, bool isFull) :
  CShape(color, center), m_width(width), m_height(height), m_isFull(isFull)
{}

/////////////////////////////////////////////////////////////////////////////
const size_t CRectangle::getWidth() const
{
  return (m_width);
}

/////////////////////////////////////////////////////////////////////////////
const size_t CRectangle::getHeight() const
{
  return (m_height);
}

/////////////////////////////////////////////////////////////////////////////
void CRectangle::setWidth(const size_t new_width)
{
  m_width = new_width;
}

/////////////////////////////////////////////////////////////////////////////
void CRectangle::setHeight(const size_t new_height)
{
  m_height = new_height;
}

/////////////////////////////////////////////////////////////////////////////
void CRectangle::draw(CRenderer& renderer) const
{
  // Top-Left point of a rectangle is a half size from the center point
  //                                                   for each coordinate
  CPos top_left(static_cast<int>(getCenter().getX() - (m_width / 2)), 
    static_cast<int>(getCenter().getY() - (m_height / 2)));

  renderer.drawRectangle(top_left, m_width, m_height, getColor(), m_isFull);
}

/////////////////////////////////////////////////////////////////////////////
void CRectangle::scale(int multiplier)
{
  m_width *= multiplier;
  m_height *= multiplier;
}

// CSquare::Implementation
// SQUARE can't be an inheritant of a RECTANGLE 
/////////////////////////////////////////////////////////////////////////////
CSquare::CSquare(const CColor& color, const CPos& center, const size_t side) :
  CShape(color, center), m_side(side)
{}

/////////////////////////////////////////////////////////////////////////////
const size_t CSquare::getSide() const
{
  return (m_side);
}

/////////////////////////////////////////////////////////////////////////////
void CSquare::setSide(const size_t new_side)
{
  m_side = new_side;
}

/////////////////////////////////////////////////////////////////////////////
void CSquare::draw(CRenderer& renderer) const
{
  // Top-Left point of a square is a half size from the center point
  //
  CPos top_left(static_cast<int>(getCenter().getX() - (m_side / 2)),
    static_cast<int>(getCenter().getY() - (m_side / 2)));

  renderer.drawRectangle(top_left, m_side, m_side, getColor());
}

/////////////////////////////////////////////////////////////////////////////
void CSquare::scale(int multiplier)
{
  m_side *= multiplier;
}

// CCircle::Implementation
/////////////////////////////////////////////////////////////////////////////
CCircle::CCircle(const CColor& color, const CPos& center, const size_t radius) :
  CShape(color, center), m_radius(radius)
{}

/////////////////////////////////////////////////////////////////////////////
const size_t CCircle::getRadius() const
{
  return (m_radius);
}

/////////////////////////////////////////////////////////////////////////////
void CCircle::setRadius(const size_t newRadius)
{
  m_radius = newRadius;
}

/////////////////////////////////////////////////////////////////////////////
void CCircle::draw(CRenderer& renderer) const
{
  renderer.fillCircle(getCenter(), m_radius, getColor());
}

/////////////////////////////////////////////////////////////////////////////
void CCircle::scale(int multiplier)
{
  m_radius *= multiplier;
}
