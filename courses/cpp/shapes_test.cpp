/*****************************************************************************
 * File name:   shapes_test.cpp
 * Developer:   Yaron Meister
 * Reviewer:    Majd
 * Date:        2019-02-25 15:31:15
 * Test Flow:   Test cases
 *****************************************************************************/
 
#include <iostream>     /* 		cout, cerr		*/
#include <stdlib.h>     /*     EXIT_SUCCESS 	*/
 
#include "shapes.h"        /* Forward declarations */
 
using namespace ilrd;
/**************************** Forward Declarations ****************************/
void Callback(ilrd::Composite *supergroup);

void LineTest();
void RectangleTest();
void SquareTest();
void CircleTest();


/*******************************************************************************
                                Main Function
*******************************************************************************/  
int main()
{   
    LineTest();
    RectangleTest();
    SquareTest();
    CircleTest();

    return (EXIT_SUCCESS);
}

/*******************************************************************************
                                Test Functions
*******************************************************************************/  
/******************************************************************************/
void Callback(ilrd::Composite *supergroup)
{
    static long c = 0;
    ++c;

    if (200 == c)
    {
        c = 0;
    }
    if (c < 100)
    {
        supergroup->Move(Point(-1, 0));
        supergroup->Scale(0.95);
    }
    else 
    {
        supergroup->Move(Point(1, 0));
        supergroup->Scale(1 / 0.95);
    }
}

/******************************************************************************/
void LineTest()
{
    Color color1(0, 90, 0);
    Color color2(90, 0, 0);
    Color color3(0, 0, 90);

    Point first_point1(-100, -100);
    Point second_point1(100, 100);
    Point first_point2(200, 200);
    Point second_point2(400, 400);
    Point first_point3(500, 500);
    Point second_point3(900, 900);

	Line line1(color1, first_point1, second_point1); 
    Line line2(color2, first_point2, second_point2); 
	Line line3(color3, first_point3, second_point3); 

    Group group;
    GraphicalApp app;

    group.AddMember(&line1);
    group.AddMember(&line2);
    group.AddMember(&line3);

    app.EndlessLoop(&group, Callback);
}

/******************************************************************************/
void RectangleTest()
{
    Color color1(0, 90, 0);
    Color color2(90, 0, 0);
    Color color3(0, 0, 90);

    Point center_point1(100, 100);
    Point center_point2(250, 250);
    Point center_point3(500, 500);

	Rectangle rect1(color1, center_point1, 100, 200);
    Rectangle rect2(color2, center_point2, 50, 100);
    Rectangle rect3(color3, center_point3, 200, 100);

    Group group;
    GraphicalApp app;

    group.AddMember(&rect1);
    group.AddMember(&rect2);
    group.AddMember(&rect3);

    app.EndlessLoop(&group, Callback);
}

/******************************************************************************/
void SquareTest()
{
    Color color1(0, 90, 0);
    Color color2(90, 0, 0);
    Color color3(0, 0, 90);

    Point center_point1(100, 100);
    Point center_point2(250, 250);
    Point center_point3(500, 500);

	Square square1(color1, center_point1, 100);
    Square square2(color2, center_point2, 50);
    Square square3(color3, center_point3, 200);

    Group group;
    GraphicalApp app;

    group.AddMember(&square1);
    group.AddMember(&square2);
    group.AddMember(&square3);

    app.EndlessLoop(&group, Callback);
}

/******************************************************************************/
void CircleTest()
{
    Color color1(0, 90, 0);
    Color color2(90, 0, 0);
    Color color3(0, 0, 90);

    Point center_point1(100, 100);
    Point center_point2(250, 250);
    Point center_point3(500, 500);

	Circle circle1(color1, center_point1, 50);
    Circle circle2(color2, center_point2, 25);
    Circle circle3(color3, center_point3, 100);

    Group group;
    GraphicalApp app;

    group.AddMember(&circle1);
    group.AddMember(&circle2);
    group.AddMember(&circle3);

    app.EndlessLoop(&group, Callback);
}

/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/    
