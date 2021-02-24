/*****************************************************************************
* File name:   graphical.cpp
* Developer:   Yaron
* Date:        2021-02-19 11:04:53
* Description: Source file for class the Graphical app service
*****************************************************************************/

#include <exception>    /* std::exception                                   */
#include <cstdio>       /* std::fprintf(), stderr                           */
#include <cmath>        /* std::sin(), std::cos(), std::acos()              */

#include "graphical.h"


// Namespaces

// Macros
static const double PI = std::acos(-1);
static const unsigned int FULL_CIRCLE_DEG = 360;

// Global variables
const char* CRenderer::windowTitle = "Shapes";

/////////////////////////////////////////////////////////////////////////////
//                        Functions's implementations
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
CRenderer& CRenderer::GetInstance()
{
  static CRenderer instance;
  return (instance);
}

/////////////////////////////////////////////////////////////////////////////
CRenderer::CRenderer()
{
  static unsigned int is_created = 0;
  if (0 != is_created)
  {
    std::fprintf(stderr, "Renderer: only one Renderer instance is "
      "permitted!\n");
    throw std::exception();
  }
  ++is_created;

  if (0 != SDL_Init(SDL_INIT_VIDEO))
  {
    std::fprintf(stderr, "Renderer: failed to initialize SDL: %s\n",
      SDL_GetError());
    throw std::exception();
  }

  m_window = SDL_CreateWindow(windowTitle,
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (0 == m_window)
  {
    std::fprintf(stderr, "Renderer: failed to create a window: %s\n",
      SDL_GetError());

    SDL_Quit();

    throw std::exception();
  }

  m_renderer = SDL_CreateRenderer(m_window, /* first device */ -1,
    /* no flags */ 0);
  if (0 == m_renderer)
  {
    std::fprintf(stderr, "Renderer: failed to create a SDL_Renderer: %s\n",
      SDL_GetError());

    SDL_DestroyWindow(m_window);
    m_window = 0;

    SDL_Quit();

    throw std::exception();
  }
}

/////////////////////////////////////////////////////////////////////////////
void CRenderer::commit()
{
  SDL_RenderPresent(m_renderer);
}

/////////////////////////////////////////////////////////////////////////////
CRenderer::~CRenderer()
{
  SDL_DestroyRenderer(m_renderer);

  SDL_DestroyWindow(m_window);

  SDL_Quit();
}

/////////////////////////////////////////////////////////////////////////////
void CRenderer::clear(const CColor& color)
{
  setRendererColor(color);

  SDL_RenderClear(m_renderer);
}

/////////////////////////////////////////////////////////////////////////////
void CRenderer::setRendererColor(const CColor& color)
{
  SDL_SetRenderDrawColor(m_renderer,
    color.GetR(), color.GetG(), color.GetB(),
    SDL_ALPHA_OPAQUE);
}

/////////////////////////////////////////////////////////////////////////////
int CRenderer::sanitizeCoordinate(long int c, int max)
{
  int result = static_cast<int>(c);

  if (result < 0)
  {
    result = 0;
  }

  if (result >= max)
  {
    result = max - 1;
  }

  return (result);
}

/////////////////////////////////////////////////////////////////////////////
void CRenderer::drawLine(const CPos& start, const CPos& end, const CColor& color)
{
  int s_x = sanitizeCoordinate(start.getX(), SCREEN_WIDTH);
  int s_y = sanitizeCoordinate(start.getY(), SCREEN_HEIGHT);
  int e_x = sanitizeCoordinate(end.getX(), SCREEN_WIDTH);
  int e_y = sanitizeCoordinate(end.getY(), SCREEN_HEIGHT);

  setRendererColor(color);

  SDL_RenderDrawLine(m_renderer, s_x, s_y, e_x, e_y);
}

/////////////////////////////////////////////////////////////////////////////
void CRenderer::drawRectangle(const CPos& topleft, std::size_t w, std::size_t h, const CColor& color, bool isFull)
{
  SDL_Rect rect;

  setRendererColor(color);

  rect.x = sanitizeCoordinate(topleft.getX(), SCREEN_WIDTH);
  rect.y = sanitizeCoordinate(topleft.getY(), SCREEN_HEIGHT);

  /* This ugly code fixed the "lava lamp" bug */
  rect.w = static_cast<int>(w) +
    static_cast<int>(topleft.getX() - static_cast<long int>(rect.x));

  rect.h = static_cast<int>(h) +
    static_cast<int>(topleft.getY() - static_cast<long int>(rect.y));

  if (isFull)
  {
    SDL_RenderFillRect(m_renderer, &rect);
  }
  else
  {
    SDL_RenderDrawRect(m_renderer, &rect);
  }
}

/////////////////////////////////////////////////////////////////////////////
void CRenderer::fillCircle(const CPos& center, std::size_t radius,
  const CColor& color)
{
  unsigned int angle_deg = 0;
  double angle_rad = 0;
  double sin_val = 0;
  double cos_val = 0;

  int raw_val = 0;

  SDL_Rect rect;

  setRendererColor(color);

  for (angle_deg = 1; angle_deg < FULL_CIRCLE_DEG / 2; ++angle_deg)
  {
    angle_rad = (2 * PI) * static_cast<double>(angle_deg) / FULL_CIRCLE_DEG;
    sin_val = std::sin(angle_rad);
    cos_val = std::cos(angle_rad);

    rect.w = static_cast<int>(2 * static_cast<double>(radius) *
      sin_val);
    rect.h = static_cast<int>(2 * static_cast<double>(radius) *
      cos_val);

    /* This ugly code fixed the "lava lamp" bug */
    raw_val = static_cast<int>(center.getX() - rect.w / 2);
    rect.x = sanitizeCoordinate(center.getX() - rect.w / 2, SCREEN_WIDTH);
    rect.w += raw_val - rect.x;

    raw_val = static_cast<int>(center.getY() - rect.h / 2);
    rect.y = sanitizeCoordinate(center.getY() - rect.h / 2, SCREEN_HEIGHT);
    rect.h += raw_val - rect.y;

    SDL_RenderFillRect(m_renderer, &rect);
  }
}

/////////////////////////////////////////////////////////////////////////////
CGraphicalApp::CGraphicalApp(const CColor& background)
  : m_renderer(CRenderer::GetInstance()), m_background(background)
{}

/////////////////////////////////////////////////////////////////////////////
void CGraphicalApp::endlessLoop(CComposite* supergroup, CallbackFunc callbackFunc)
{
  bool should_run = true;

  if (0 == supergroup)
  {
    throw std::exception();
  }

  do
  {
    should_run = !isExitPressed();

    m_renderer.clear(m_background);

    should_run = callbackFunc(supergroup);

    supergroup->draw(m_renderer);

    m_renderer.commit();

    sleepMS(DELAY_BETWEEN_FRAMES_MS);
  } while (should_run);
}

/////////////////////////////////////////////////////////////////////////////
bool CGraphicalApp::callbackDoNothing(CComposite* composite)
{
  static_cast<void>(composite);

  return (false);
}

/////////////////////////////////////////////////////////////////////////////
void CGraphicalApp::sleepMS(int ms)
{
  SDL_Delay(ms);
}

/////////////////////////////////////////////////////////////////////////////
bool CGraphicalApp::isExitPressed()
{
  SDL_Event e;

  while (0 != SDL_PollEvent(&e))
  {
    if (SDL_QUIT == e.type)
    {
      return (true);
    }
  }

  return (false);
}


