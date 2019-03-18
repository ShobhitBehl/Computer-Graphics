#include <bits/stdc++.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../include/Rectangle.h"

#define glf GLfloat

using namespace std;

Rectangle::Rectangle()
{

}

Rectangle::Rectangle(const Point &param_top_left, const Point &param_bottom_right, char param_text, const Colour &param_c)
{
    top_left = param_top_left;
    bottom_right = param_bottom_right;
    text = param_text;
    c = param_c;
    clicked = 0;
    hover = 0;
    hover_angle = -45.0f;
}

Rectangle::Rectangle(const Rectangle &r)
{
    top_left = r.top_left;
    bottom_right = r.bottom_right;
    text = r.text;
    c = r.c;
    clicked = r.clicked;
}

Point Rectangle::getTopLeft()
{
    return top_left;
}

Point Rectangle::getBottomRight()
{
    return bottom_right;
}

char Rectangle::getText()
{
    return text;
}

int Rectangle::getClicked()
{
    return clicked;
}

Colour Rectangle::getColour()
{
    return c;
}

double Rectangle::getClickedX()
{
    return clicked_x;
}

double Rectangle::getClickedY()
{
    return clicked_y;
}

int  Rectangle::getHover()
{
    return hover;
}

glf Rectangle::getHoverAngle()
{
    return hover_angle;
}

void Rectangle::setTopLeft(const Point &param_top_left)
{
    top_left = param_top_left;
}

void Rectangle::setBottomRight(const Point &param_bottom_right)
{
    bottom_right = param_bottom_right;
}

void Rectangle::setText(char param_text)
{
    text = param_text;
}

void Rectangle::setClicked(int param_clicked)
{
    clicked = param_clicked;
}

void Rectangle::setColour(const Colour &param_c)
{
    c = param_c;
}

void Rectangle::setClickedX(double param_clicked_x)
{
    clicked_x = param_clicked_x;
}

void Rectangle::setClickedY(double param_clicked_y)
{
    clicked_y = param_clicked_y;
}

void Rectangle::setHover(int param_hover)
{
    hover = param_hover;
}

void Rectangle::setHoverAngle(glf param_hover_angle)
{
    hover_angle = param_hover_angle;
}
