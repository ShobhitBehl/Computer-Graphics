#include <bits/stdc++.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../include/Point.h"

#define glf GLfloat

using namespace std;

Point::Point()
{

}

Point::Point(const glf &param_x, const glf &param_y, const glf &param_z)
{
    x = param_x;
    y = param_y;
    z = param_z;
}

Point::Point(const Point &p)
{
    x = p.x;
    y = p.y;
    z = p.z;
}

glf Point::getX()
{
    return x;
}

glf Point::getZ()
{
    return z;
}

glf Point::getY()
{
    return y;
}

void Point::setX(const glf &param_x)
{
    x = param_x;
}

void Point::setY(const glf &param_y)
{
    y = param_y;
}

void Point::setZ(const glf &param_z)
{
    z = param_z;
}
