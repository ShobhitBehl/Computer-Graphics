#include <bits/stdc++.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define glf GLfloat

using namespace std;

class Point
{
private:
    glf x,y,z;

public:
    Point();

    Point(const glf &param_x, const glf &param_y, const glf &param_z);

    Point(const Point &p);

    glf getX();

    glf getZ();

    glf getY();

    void setX(const glf &param_x);

    void setY(const glf &param_y);

    void setZ(const glf &param_z);
};
