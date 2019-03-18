#include <bits/stdc++.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../include/Calculator.h"

#define glf GLfloat

using namespace std;

Calculator::Calculator()
{
    translate_x = 0.0;
    translate_y = 0.0;
    translate_z = 0.0;
    scale_x = 1.0;
    scale_y = 1.0;
    scale_z = 1.0;
    axis_x = 0.0;
    axis_y = 0.0;
    axis_z = 1.0;
    angle = 0.0;
}

glf Calculator::getScaleX()
{
    return scale_x;
}

glf Calculator::getScaleY()
{
    return scale_y;
}

glf Calculator::getScaleZ()
{
    return scale_z;
}

glf Calculator::getTranslateX()
{
    return translate_x;
}

glf Calculator::getTranslateY()
{
    return translate_y;
}

glf Calculator::getTranslateZ()
{
    return translate_z;
}

glf Calculator::getAngle()
{
    return angle;
}

void Calculator::setScaleX(glf param_scale_x)
{
    scale_x = param_scale_x;
}

void Calculator::setScaleY(glf param_scale_y)
{
    scale_y = param_scale_y;
}

void Calculator::setScaleZ(glf param_scale_z)
{
    scale_z = param_scale_z;
}

void Calculator::setTranslateX(glf param_translate_x)
{
    translate_x = param_translate_x;
}

void Calculator::setTranslateY(glf param_translate_y)
{
    translate_y = param_translate_y;
}

void Calculator::setTranslateZ(glf param_translate_z)
{
    translate_z = param_translate_z;
}

void Calculator::setAngle(glf param_angle)
{
    angle = param_angle;
}

void Calculator::construct()
{
    Colour grey(0.82f, 0.82f, 0.82f);
    Colour orange(1.0f, 0.64f, 0.0f);
    Colour dark_grey(0.63f,0.63f,0.63f);

    char text;

    string s = "CN%/789*456-123+0.=";

    for(int i = 0; i<4; i++)
    {
        for(int j = 0; j<4; j++)
        {
            Point top_left(-0.4f + 0.2f * j, 0.25 - 0.1f * i, 0.0f);
            Point bottom_right(-0.2f + 0.2f * j, 0.15 - 0.1f * i, 0.0f);

            Rectangle r(top_left, bottom_right, s[4*i + j], grey);

            if(i == 0)
            {
                r.setColour(dark_grey);
            }
            if(j == 3)
            {
                r.setColour(orange);
            }
            rectangles[4*i + j] = r;
        }
    }

    Point top_left = rectangles[12].getTopLeft();
    Point bottom_right = rectangles[13].getBottomRight();

    top_left.setY(top_left.getY() - 0.1f);
    bottom_right.setY(bottom_right.getY() - 0.1f);

    Rectangle r(top_left, bottom_right, s[16], grey);

    rectangles[16] = r;

    for(int i = 17; i<19; i++)
    {
        Point top_left = rectangles[i-3].getTopLeft();
        Point bottom_right = rectangles[i-3].getBottomRight();

        top_left.setY(top_left.getY() - 0.1f);
        bottom_right.setY(bottom_right.getY() - 0.1f);

        Rectangle r(top_left, bottom_right, s[i], grey);

        if(i == 18)
        {
            r.setColour(orange);
        }

        rectangles[i] = r;
    }

}

void Calculator::display()
{
    glLoadIdentity();

    glTranslatef(translate_x,translate_y,translate_z);
    glScalef(scale_x,scale_y,scale_z);
    glRotatef(angle,axis_x,axis_y,axis_z);



    for(int i = 0; i<19; i++)
    {
        Rectangle r = rectangles[i];

        Point top_left = r.getTopLeft();
        Point bottom_right = r.getBottomRight();

        Colour c = r.getColour();

        glf rect_h = 0.1f,rect_w = 0.2f;

        if(i == 16)
        {
            rect_w = 0.4f;
        }

        glPushMatrix();

        glTranslatef(top_left.getX() + rect_w/2, top_left.getY() - rect_h/2, 0.0f);

        glBegin(GL_QUADS);

        glColor4f(c.getR(), c.getG(), c.getB(), 1.0f);
        glVertex3f(-rect_w/2, rect_h/2, 0.0f);
        glVertex3f(rect_w/2, rect_h/2, 0.0f);
        glVertex3f(rect_w/2, -rect_h/2, 0.0f);
        glVertex3f(-rect_w/2, -rect_h/2, 0.0f);

        glEnd();

        glBegin(GL_LINES);

        glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
        
        glVertex3f(-rect_w/2, rect_h/2, 0.0f);
        glVertex3f(rect_w/2, rect_h/2, 0.0f);

        glVertex3f(rect_w/2, rect_h/2, 0.0f);
        glVertex3f(rect_w/2, -rect_h/2, 0.0f);

        glVertex3f(rect_w/2, -rect_h/2, 0.0f);
        glVertex3f(-rect_w/2, -rect_h/2, 0.0f);

        glVertex3f(-rect_w/2, -rect_h/2, 0.0f);
        glVertex3f(-rect_w/2, rect_h/2, 0.0f);

        glEnd();

        glPopMatrix();
        if(rectangles[i].getHover() == 1)
        {
            if(rectangles[i].getHoverAngle() < 45.0f)
            {
                glPushMatrix();


                glTranslatef(top_left.getX() + rect_w/2, top_left.getY() - rect_h/2, 0.0f);
                glRotatef(rectangles[i].getHoverAngle(), 0, 0, 1);
                glScalef(0.8f,0.8f,0.8f);

                glBegin(GL_LINES);

                glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
                glVertex3f(-rect_w/2, rect_h/2, 0.0f);
                glVertex3f(rect_w/2, rect_h/2, 0.0f);

                glVertex3f(rect_w/2, rect_h/2, 0.0f);
                glVertex3f(rect_w/2, -rect_h/2, 0.0f);

                glVertex3f(rect_w/2, -rect_h/2, 0.0f);
                glVertex3f(-rect_w/2, -rect_h/2, 0.0f);

                glVertex3f(-rect_w/2, -rect_h/2, 0.0f);
                glVertex3f(-rect_w/2, rect_h/2, 0.0f);

                glEnd();

                glPopMatrix();
                rectangles[i].setHoverAngle(rectangles[i].getHoverAngle() + 0.05f);
            }
            else
            {
                rectangles[i].setHover(0);
                rectangles[i].setHoverAngle(-45.0f);
            }
        }
    }


}

int Calculator::check(Rectangle r, double cursor_x, double cursor_y)
{
    if(r.getTopLeft().getX() <= cursor_x && cursor_x <= r.getBottomRight().getX() && r.getBottomRight().getY() <= cursor_y && cursor_y <= r.getTopLeft().getY())
    {
        return 1;
    }
    return 0;
}

void Calculator::printText(double cursor_x, double cursor_y)
{
    for(int i = 0; i<19; i++)
    {
        if(check(rectangles[i],cursor_x,cursor_y))
        {
            cout << rectangles[i].getText() << endl;
            rectangles[i].setHover(1);
            rectangles[i].setHoverAngle(-45.0);
        }
    }
}

void Calculator::clickButton(double cursor_x, double cursor_y)
{
    for(int i = 0; i<19; i++)
    {
        if(check(rectangles[i],cursor_x,cursor_y))
        {
            rectangles[i].setClicked(1);
            rectangles[i].setClickedX(cursor_x);
            rectangles[i].setClickedY(cursor_y);
        }
    }
}

void Calculator::unclickButton(double cursor_x, double cursor_y)
{
    for(int i = 0; i<19; i++)
    {
        if(rectangles[i].getClicked() == 1)
        {
            rectangles[i].setClicked(0);
        }
    }
}

void Calculator::Drag(double cursor_x, double cursor_y)
{
    for(int i = 0; i<19; i++)
    {
        if(rectangles[i].getClicked() == 1)
        {
            double change_x = cursor_x - rectangles[i].getClickedX();
            double change_y = cursor_y - rectangles[i].getClickedY();

            Point top_left = rectangles[i].getTopLeft();
            Point bottom_right = rectangles[i].getBottomRight();

            top_left.setX(top_left.getX() + change_x);
            top_left.setY(top_left.getY() + change_y);
            bottom_right.setX(bottom_right.getX() + change_x);
            bottom_right.setY(bottom_right.getY() + change_y);

            rectangles[i].setTopLeft(top_left);
            rectangles[i].setBottomRight(bottom_right);

            rectangles[i].setClickedX(cursor_x);
            rectangles[i].setClickedY(cursor_y);
        }
    }
}
