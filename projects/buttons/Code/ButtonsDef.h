/*****************************************************************************
 * File name:   ButtonsDef.h
 * Developer:   Yaron Meister
 * Date:        2021-09-17 11:04:53
 * Description: Header file for Buttons related declarations && definitions
 *****************************************************************************/

#ifndef __BUTTONS_DEF_H__
#define __BUTTONS_DEF_H__


/* Enums */

typedef enum ButtonState
{
  OFF,
  ON,
  INVALID
}EButtonsStateType;

/* Structs */

typedef struct Button
{
  unsigned id;
  EButtonsStateType state;
}SButtonType;

#endif     /* __BUTTONS_DEF_H__ */