/*****************************************************************************
* File name:   color.h
* Developer:   Yaron
* Date:        2021-02-14 11:04:53
* Description: Header file for class 'CColor'
*****************************************************************************/

#ifndef __COLOR_H__
#define __COLOR_H__

class CColor
{
public:
  CColor(unsigned char r, unsigned char g, unsigned char b);                   

  unsigned char GetR() const;                                                 
  unsigned char GetG() const;                                                 
  unsigned char GetB() const;                                                 

  void SetR(unsigned char r);                                                 
  void SetG(unsigned char g);                                                 
  void SetB(unsigned char b);                                                 
private:
  unsigned char m_r, m_g, m_b; // 0 - 255 each
};


#endif // __COLOR_H__ 












