#include <bits/stdc++.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Rectangle.h"

#define glf GLfloat

using namespace std;

class Calculator
{
private:
    Rectangle rectangles[500];
    glf translate_x,translate_y,translate_z;
    glf scale_x,scale_y,scale_z;
    glf axis_x,axis_y,axis_z,angle;

public:

    Calculator();

    glf getScaleX();

    glf getScaleY();

    glf getScaleZ();

    glf getTranslateX();

    glf getTranslateY();

    glf getTranslateZ();

    glf getAngle();

    void setScaleX(glf param_scale_x);

    void setScaleY(glf param_scale_y);

    void setScaleZ(glf param_scale_z);

    void setTranslateX(glf param_translate_x);

    void setTranslateY(glf param_translate_y);

    void setTranslateZ(glf param_translate_z);

    void setAngle(glf param_angle);

    void construct();

    void display();

    int check(Rectangle r, double cursor_x, double cursor_y);

    void printText(double cursor_x, double cursor_y);

    void clickButton(double cursor_x, double cursor_y);

    void unclickButton(double cursor_x, double cursor_y);

    void Drag(double cursor_x, double cursor_y);

    void Hover(double cursor_x, double cursor_y);
};
