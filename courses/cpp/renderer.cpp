#include <exception>    /* std::exception                                   */
#include <cstdio>       /* std::fprintf(), stderr                           */
#include <cmath>        /* std::sin(), std::cos(), std::acos()              */
#include <SDL.h>        /* SDL_*()                                          */

#include "shapes.h"     /* Declarations                                     */

using namespace ilrd;

const char *ilrd::Renderer::WindowTitle = "Shapes";

static const double Pi = std::acos(-1);
static const unsigned int FullCircleDeg = 360;

/* ========================================================================= */
Renderer& Renderer::GetInstance()
{
    static Renderer instance;
    return (instance);
}

/* ========================================================================= */
Renderer::Renderer()
{
    static unsigned int is_created = 0;
    if (0 != is_created)
    {
        std::fprintf(stderr, "Renderer: only one Renderer instance is "
                "permitted!\n");
        throw std::exception();
    }
    ++is_created;

    if(0 != SDL_Init(SDL_INIT_VIDEO))
    {
        std::fprintf(stderr, "Renderer: failed to initialize SDL: %s\n",
                SDL_GetError());
        throw std::exception();
    }

    m_window = SDL_CreateWindow(WindowTitle,
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN);
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

/* ========================================================================= */
void Renderer::Commit()
{
    SDL_RenderPresent(m_renderer);
}

/* ========================================================================= */
Renderer::~Renderer()
{
    SDL_DestroyRenderer(m_renderer);

    SDL_DestroyWindow(m_window);

    SDL_Quit();
}

/* ========================================================================= */
void Renderer::Clear(const Color& color)
{
    SetRendererColor(color);

    SDL_RenderClear(m_renderer);
}

/* ========================================================================= */
void Renderer::SetRendererColor(const Color& color)
{
    SDL_SetRenderDrawColor(m_renderer,
            color.GetR(), color.GetG(), color.GetB(),
            SDL_ALPHA_OPAQUE);
}

/* ========================================================================= */
int Renderer::SanitizeCoordinate(long int c, int max)
{
    int result = static_cast<int>(c);

    if (result < 0)
    {
        result = 0;
    }

    if (result >= max)
    {
        result = max-1;
    }

    return (result);
}

/* ========================================================================= */
void Renderer::DrawLine(const Point& start, const Point& end, const Color& color)
{
    int s_x = SanitizeCoordinate(start.GetX(), ScreenWidth);
    int s_y = SanitizeCoordinate(start.GetY(), ScreenHeight);
    int e_x = SanitizeCoordinate(end.GetX(), ScreenWidth);
    int e_y = SanitizeCoordinate(end.GetY(), ScreenHeight);

    SetRendererColor(color);

    SDL_RenderDrawLine(m_renderer, s_x, s_y, e_x, e_y);
}

/* ========================================================================= */
void Renderer::FillRectangle(const Point& topleft, std::size_t w, std::size_t h,
        const Color& color)
{
    SDL_Rect rect;

    SetRendererColor(color);

    rect.x = SanitizeCoordinate(topleft.GetX(), ScreenWidth);
    rect.y = SanitizeCoordinate(topleft.GetY(), ScreenHeight);

    /* This ugly code fixed the "lava lamp" bug */
    rect.w = static_cast<int>(w) +
        static_cast<int>(topleft.GetX() - static_cast<long int>(rect.x));

    rect.h = static_cast<int>(h) +
        static_cast<int>(topleft.GetY() - static_cast<long int>(rect.y));

    SDL_RenderFillRect(m_renderer, &rect);
}

/* ========================================================================= */
void Renderer::FillCircle(const Point& center, std::size_t radius,
        const Color& color)
{
    unsigned int angle_deg = 0;
    double angle_rad = 0;
    double sin_val = 0;
    double cos_val = 0;

    int raw_val = 0;

    SDL_Rect rect;

    SetRendererColor(color);

    for (angle_deg = 1; angle_deg < FullCircleDeg / 2; ++angle_deg)
    {
        angle_rad = (2 * Pi) * static_cast<double>(angle_deg) / FullCircleDeg;
        sin_val = std::sin(angle_rad);
        cos_val = std::cos(angle_rad);

        rect.w = static_cast<int>(2 * static_cast<double>(radius) *
                sin_val);
        rect.h = static_cast<int>(2 * static_cast<double>(radius) *
                cos_val);

        /* This ugly code fixed the "lava lamp" bug */
        raw_val = static_cast<int>(center.GetX() - rect.w / 2);
        rect.x = SanitizeCoordinate(center.GetX() - rect.w / 2, ScreenWidth);
        rect.w += raw_val - rect.x;

        raw_val = static_cast<int>(center.GetY() - rect.h / 2);
        rect.y = SanitizeCoordinate(center.GetY() - rect.h / 2, ScreenHeight);
        rect.h += raw_val - rect.y;

        SDL_RenderFillRect(m_renderer, &rect);
    }
}

/* ========================================================================= */
GraphicalApp::GraphicalApp(const Color& background)
    : m_renderer(Renderer::GetInstance()), m_background(background)
{}

/* ========================================================================= */
void GraphicalApp::EndlessLoop(Composite *supergroup,
        void (*callback)(Composite *))
{
    bool should_run = true;

    if (0 == supergroup)
    {
        throw std::exception();
    }

    do
    {
        should_run = ! IsExitPressed();

        m_renderer.Clear(m_background);

#ifdef TEST_SHITTY_DRAWINGS
        m_renderer.DrawLine(Point(10, 10), Point(50, 110), Color(0, 150, 0));
        m_renderer.FillRectangle(Point(10, 120), 100, 30, Color(150, 0, 0));

        m_renderer.FillCircle(Point(200, 200), 50, Color(0, 0, 150));
        m_renderer.DrawLine(Point(150, 150), Point(250, 250), Color(0, 150, 0));
        m_renderer.DrawLine(Point(250, 150), Point(150, 250), Color(0, 150, 0));
#endif

        callback(supergroup);

        supergroup->Draw(m_renderer);

        m_renderer.Commit();

        SleepMS(DelayBetweenFramesMS);
    } while (should_run);
}

/* ========================================================================= */
void GraphicalApp::CallbackDoNothing(Composite *composite)
{
    static_cast<void>(composite);
}

/* ========================================================================= */
void GraphicalApp::SleepMS(int ms)
{
    SDL_Delay(ms);
}

/* ========================================================================= */
bool GraphicalApp::IsExitPressed()
{
    SDL_Event e;

    while(0 != SDL_PollEvent(&e))
    {
        if(SDL_QUIT == e.type)
        {
            return (true);
        }
    }

    return (false);
}
