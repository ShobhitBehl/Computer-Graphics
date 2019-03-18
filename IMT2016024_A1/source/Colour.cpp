#include <bits/stdc++.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../include/Colour.h"

Colour::Colour()
{

}

Colour::Colour(const glf &param_r, const glf &param_g, const glf &param_b)
{
    r = param_r;
    g = param_g;
    b = param_b;
}

Colour::Colour(const Colour &c)
{
    r = c.r;
    g = c.g;
    b = c.b;
}

glf Colour::getR()
{
    return r;
}

glf Colour::getG()
{
    return g;
}

glf Colour::getB()
{
    return b;
}

void Colour::setX(const glf &param_r)
{
    r = param_r;
}

void Colour::setG(const glf &param_g)
{
    g = param_g;
}

void Colour::setB(const glf &param_b)
{
    b = param_b;
}
