#include <bits/stdc++.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define glf GLfloat

class Colour
{
private:
    glf r,g,b;

public:
    Colour();

    Colour(const glf &param_r, const glf &param_g, const glf &param_b);

    Colour(const Colour &c);

    glf getR();

    glf getG();

    glf getB();

    void setX(const glf &param_r);

    void setG(const glf &param_g);

    void setB(const glf &param_b);

};
