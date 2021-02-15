/*****************************************************************************
 * File name:   position.h
 * Developer:   Yaron Meister
 * Date:        2021-01-29
 * Description: Header file for the class 'CPos'
 *****************************************************************************/

#ifndef __POSITION_H__
#define __POSITION_H__

class CPos
{
public:
	// CTor
	CPos(int x = 0, int y = 0);

	bool operator==(const CPos& other);
	bool operator!=(const CPos& other);

	inline int getX() const;
	inline int getY() const;
	inline void setX(int x);
	inline void setY(int y);

	const CPos operator+(const CPos& rhs);
	const CPos operator-(const CPos& rhs);
	CPos& operator+=(const CPos& point);
	CPos& operator-=(const CPos& point);
	CPos& operator*=(int multiplier);
	CPos& operator/=(int multiplier);

private:
	int m_x;
	int m_y;
};

/////////////////////////////////////////////////////////////////////////////
//                        Functions's implementations
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
inline int CPos::getX() const
{
	return (m_x);
}

/////////////////////////////////////////////////////////////////////////////
inline int CPos::getY() const
{
	return (m_y);
}

/////////////////////////////////////////////////////////////////////////////
inline void CPos::setX(int x)
{
	m_x = x;
}

/////////////////////////////////////////////////////////////////////////////
inline void CPos::setY(int y)
{
	m_y = y;
}

/////////////////////////////////////////////////////////////////////////////


#endif // __POSITION_H__