#include <bits/stdc++.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Point.h"
#include "Colour.h"

#define glf GLfloat

using namespace std;

class Rectangle
{
private:
    Point top_left, bottom_right;
    double clicked_x, clicked_y;
    int clicked,hover;
    char text;
    Colour c;
    glf hover_angle;

public:
    Rectangle();

    Rectangle(const Point &param_top_left, const Point &param_bottom_right, char param_text, const Colour &param_c);

    Rectangle(const Rectangle &r);

    Point getTopLeft();

    Point getBottomRight();

    char getText();

    int getClicked();

    Colour getColour();

    double getClickedX();

    double getClickedY();

    int getHover();

    glf getHoverAngle();

    void setTopLeft(const Point &param_top_left);

    void setBottomRight(const Point &param_bottom_right);

    void setText(char param_text);

    void setClicked(int param_clicked);

    void setColour(const Colour &param_c);

    void setClickedX(double param_clicked_x);

    void setClickedY(double param_clicked_y);

    void setHover(int param_hover);

    void setHoverAngle(glf param_hover_angle);
};
