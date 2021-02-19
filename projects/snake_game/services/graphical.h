/*****************************************************************************
* File name:   graphical.h
* Developer:   Yaron
* Date:        2021-02-19 11:04:53
* Description: Header file for the Graphical app service
*****************************************************************************/

#ifndef __GRAPHICAL_H__
#define __GRAPHICAL_H__

#include <SDL.h>        
#include <cstdlib>

#include "position.hpp"
#include "color.h"

// Forward declarations
class CComposite;

/* ===================================================================== */
class CRenderer
{
public:
  static CRenderer& GetInstance();
  ~CRenderer();

  void commit();
  void clear(const CColor&);

  void drawLine(const CPos& start, const CPos& end, const CColor& color);
  void fillRectangle(const CPos& topleft, std::size_t w, std::size_t h, const CColor& color);
  void fillCircle(const CPos& center, std::size_t radius, const CColor& color);

private:
  static const int SCREEN_WIDTH = 800;
  static const int SCREEN_HEIGHT = 600;
  static const char* windowTitle;

  SDL_Window* m_window;
  SDL_Renderer* m_renderer;

  CRenderer();
  /* copying is forbidden: */
  CRenderer(const CRenderer&);
  CRenderer& operator=(const CRenderer&);

  void setRendererColor(const CColor& color);
  int sanitizeCoordinate(long int c, int max);
};

/* ===================================================================== */
class CGraphicalApp
{
public:
  /* Default background: black */
  CGraphicalApp(const CColor& background = CColor(0, 0, 0));

  /* Before each drawing iteration calls callback(supergroup) */
  void endlessLoop(CComposite* supergroup,
    void (*callback)(CComposite*) = callbackDoNothing);

  /* Default callback for EndlessLoop: does nothing */
  static void callbackDoNothing(CComposite*);
private:
  /* no copying */
  CGraphicalApp(const CGraphicalApp&);
  CGraphicalApp& operator=(const CGraphicalApp&);

  static const int DELAY_BETWEEN_FRAMES_MS = 50;

  void sleepMS(int ms);
  bool isExitPressed();

  CRenderer& m_renderer;
  CColor m_background;
};

/* ===================================================================== */
class CComposite
{
public:
  virtual ~CComposite() {};
  virtual const CPos getCenter() const = 0;

  /* Move(Offset): moves all the composite relative to
   * its current position */
  virtual void move(const CPos&) = 0;
  virtual void setColor(const CColor&) = 0;
  virtual void draw(CRenderer& renderer) = 0;
  virtual void scale(double) = 0;
};

#endif // __GRAPHICAL_H__