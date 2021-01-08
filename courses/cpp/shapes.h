/*****************************************************************************
 * File name:   shapes.h
 * Developer:   HRD7
 * Version:     3
 * Date:        2019-02-25 15:31:15
 * Description: Shapes header
 *****************************************************************************/

#ifndef __SHAPES_H__
#define __SHAPES_H__

#include <iostream>
#include <vector>

#include <SDL.h>        /* Renderer uses these. SDL_*()                     */

/* ========================================================================= */
namespace ilrd
{
    /* Forward declaration */
    class Composite;

/* ===================================================================== */
    class Color
    {
    public:
        Color(unsigned char r, unsigned char g, unsigned char b);                   //

        unsigned char GetR() const;                                                 //
        unsigned char GetG() const;                                                 //
        unsigned char GetB() const;                                                 //

        void SetR(unsigned char r);                                                 //
        void SetG(unsigned char g);                                                 //
        void SetB(unsigned char b);                                                 //
    private:
        unsigned char m_r, m_g, m_b; // 0 - 255 each
    };

/* ===================================================================== */
    class Point
    {
    public:
        /* Top-left corner is (0, 0),
         * bottom-right corner is (+W, +H)
         */
        explicit Point(long int x = 0, long int y = 0);                             //
        void SetX(long int);                                                        //
        void SetY(long int);                                                        //
        long int GetX() const;                                                      //
        long int GetY() const;                                                      //

        const Point operator+(const Point& rhs);                                    //
        const Point operator-(const Point& rhs);                                    //
        Point& operator+=(const Point&);                                            //
        Point& operator-=(const Point&);                                            //
        Point& operator*=(double);                                                  //
        Point& operator/=(double);                                                  //
    private:
        long int m_x, m_y;
    };

/* ===================================================================== */
      class Renderer
    {
    public:
        static Renderer& GetInstance();
        ~Renderer();

        void Commit();
        void Clear(const Color&);

        void DrawLine(const Point& start, const Point& end, const Color& color);
        void FillRectangle(const Point& topleft, std::size_t w, std::size_t h,
                const Color& color);
        void FillCircle(const Point& center, std::size_t radius,
                const Color& color);
    private:
        static const int ScreenWidth  = 800;
        static const int ScreenHeight = 600;
        static const char *WindowTitle;

        SDL_Window* m_window;
        SDL_Renderer* m_renderer;

        Renderer();
        /* copying is forbidden: */
        Renderer(const Renderer&);
        Renderer& operator=(const Renderer&);

        void SetRendererColor(const Color& color);
        int SanitizeCoordinate(long int c, int max);
    };

/* ===================================================================== */
    class GraphicalApp
    {
    public:
        /* Default background: black */
        GraphicalApp(const Color& background = Color(0,0,0));

        /* Before each drawing iteration calls callback(supergroup) */
        void EndlessLoop(Composite *supergroup,
                void (*callback)(Composite *) = CallbackDoNothing);

        /* Default callback for EndlessLoop: does nothing */
        static void CallbackDoNothing(Composite *);
    private:
        /* no copying */
        GraphicalApp(const GraphicalApp&);
        GraphicalApp& operator=(const GraphicalApp&);

        static const int DelayBetweenFramesMS = 50;

        void SleepMS(int ms);
        bool IsExitPressed();

        Renderer &m_renderer;
        Color m_background;
    };



/* ===================================================================== */
    class Composite
    {
    public:
        virtual ~Composite() {};
        virtual const Point GetCenter() const = 0;

        /* Move(Offset): moves all the composite relative to
         * its current position */
        virtual void Move(const Point&) = 0;                    
        virtual void SetColor(const Color&) = 0;
        virtual void Draw(Renderer &renderer) = 0;
        virtual void Scale(double) = 0;
    };

/* ===================================================================== */
    class Group : public Composite
    {
    public:
        Group(){}                                                                   //
        ~Group();                                                                   //

        const Point GetCenter() const;                                              //    
        void Move(const Point&);                                                    //
        void SetColor(const Color&);                                                //
        void Draw(Renderer &renderer);                                              //
        void Scale(double);                                                         //

        void AddMember(Composite* shape);                                           //
    private:
        /* No need to implement. These are here to forbide usage */
        Group(const Group&);
        Group& operator=(const Group&);

        std::vector<Composite*> m_members;
    };

/* ===================================================================== */
    class Shape : public Composite
    {
    public:
        /* Point's default: Point(0,0) */
        Shape(const Color& color, const Point& center);                             //

        const Point GetCenter() const;                                              //
        void Move(const Point&);                                                    //
        void SetColor(const Color&);                                                //
        const Color& GetColor() const;                                              //

        virtual void Draw(Renderer &renderer) = 0;                                  //
        virtual void Scale(double) = 0;                                             //
    private:
        Color m_color;
        Point m_center;
    };

/* ===================================================================== */
    class Line : public Shape
    {
    public:
        Line(const Color& color, const Point& first_point,
             const Point& second_point);                                            //

        const Point GetFirstPoint() const;
        const Point GetSecondPoint() const;
        void SetFirstPoint(const Point&);
        void SetSecondPoint(const Point&);
        void Draw(Renderer &renderer);                                              //
        void Scale(double multiplier);                                              //                         

    private:
       Point m_first_point;
       Point m_second_point;
       const Point GetLineCenter(const Point& first_point,
                                               const Point& second_point) const; 
    };

/* ===================================================================== */
    class Rectangle : public Shape
    {
    public:
        Rectangle(const Color& color, const Point& center,
                  const std::size_t height, const std::size_t width);               //

        const std::size_t GetWidth() const;
        const std::size_t GetHeight() const;
        void SetWidth(const std::size_t);
        void SetHeight(const std::size_t);
        void Draw(Renderer &renderer);                                              //
        void Scale(double multiplier);                                              //                                                                                   

    private:
       std::size_t m_width;
       std::size_t m_height; 
    };

/* ===================================================================== */
    class Square : public Shape
    {
    public:
        Square(const Color& color, const Point& center, const std::size_t side);    //

        const std::size_t GetSide() const;
        void SetSide(const std::size_t);
        void Draw(Renderer &renderer);                                              //
        void Scale(double multiplier);                                              //                                                                                   

    private:
       std::size_t m_side;
    };

/* ===================================================================== */
    class Circle : public Shape
    {
    public:
        Circle(const Color& color, const Point& center,
                                                      const std::size_t radius);    //

        const std::size_t GetRadius() const;
        void SetRadius(const std::size_t);
        void Draw(Renderer &renderer);                                              //                                                                                     
        void Scale(double multiplier);                                              //                                                                                              

    private:
       std::size_t m_radius; 
    };

} // ilrd

 
#endif     /* __SHAPES_H__ */


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/
