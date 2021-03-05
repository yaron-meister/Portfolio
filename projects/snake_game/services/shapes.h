/*****************************************************************************
* File name:   shapes.h
* Developer:   Yaron
* Date:        2021-02-19 11:04:53
* Description: Header file for graphical shapes rendering
*****************************************************************************/

#ifndef __SHAPES_H__
#define __SHAPES_H__

#include <vector>
#include <deque>

#include "graphical.h"


class CGroup : public CComposite
{
public:
  CGroup() {}                                                                  
  ~CGroup();                                                                   

  const CPos getCenter() const;                                                  
  void move(const CPos&);                                                    
  void setColor(const CColor&);                                                
  void draw(CRenderer& renderer) const;                                              
  void scale(int);                                                         

  void addMember(CComposite* shape);
  void removeOldestMember();
  size_t getMembersNum() const;

private:
  /* No need to implement. These are here to forbide usage */
  CGroup(const CGroup&);
  CGroup& operator=(const CGroup&);

  std::deque<CComposite*> m_members;
};

/* ===================================================================== */
class CSuperGroup
{
public:
  void addGroup(const CGroup* group);
  void draw(CRenderer& renderer);

private:
  std::vector<const CGroup*> m_groups;
};

/* ===================================================================== */
class CShape : public CComposite
{
public:
  /* CPos's default: CPos(0,0) */
  CShape(const CColor& color, const CPos& center);                             

  const CPos getCenter() const;
  void setCenter(CPos newCenter);
  void move(const CPos&);                                                    
  void setColor(const CColor&);                                                
  const CColor& getColor() const;                                              

  virtual void draw(CRenderer& renderer) const = 0;                                  
  virtual void scale(int) = 0;      

private:
  CColor m_color;
  CPos m_center;
};

/* ===================================================================== */
class CLine : public CShape
{
public:
  CLine(const CColor& color, const CPos& first_point, const CPos& second_point);                                            

  const CPos getFirstPoint() const;
  const CPos getSecondPoint() const;
  void setFirstPoint(const CPos&);
  void setSecondPoint(const CPos&);
  void draw(CRenderer& renderer) const;
  void scale(int multiplier);                                                                       

private:
  const CPos getLineCenter(const CPos& first_point, const CPos& second_point) const;

  CPos m_firstPoint;
  CPos m_secondPoint;
};

/* ===================================================================== */
class CRectangle : public CShape
{
public:
  CRectangle(const CColor& color, const CPos& center, const std::size_t height, const std::size_t width, bool isFull);

  const std::size_t getWidth() const;
  const std::size_t getHeight() const;
  void setWidth(const std::size_t);
  void setHeight(const std::size_t);
  void draw(CRenderer& renderer) const; 
  void scale(int multiplier);

private:
  std::size_t m_width;
  std::size_t m_height;

  bool m_isFull;
};

/* ===================================================================== */
class CSquare : public CShape
{
public:
  CSquare(const CColor& color, const CPos& center, const std::size_t side);    

  const std::size_t getSide() const;
  void setSide(const std::size_t);
  void draw(CRenderer& renderer) const;
  void scale(int multiplier);                                                                                                                                 
private:
  std::size_t m_side;
};

/* ===================================================================== */
class CCircle : public CShape
{
public:
  CCircle(const CColor& color, const CPos& center, const std::size_t radius);    

  const std::size_t getRadius() const;
  void setRadius(const std::size_t);
  void draw(CRenderer& renderer) const;                                                                                                                                  
  void scale(int multiplier);                                                                                                                                            
private:
  std::size_t m_radius;
};


#endif // __SHAPES_H__