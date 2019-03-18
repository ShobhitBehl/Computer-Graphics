#include <bits/stdc++.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../include/Calculator.h"

#define glf GLfloat

#define lli long long int

using namespace std;

Calculator calc;

void handleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
    if (key == GLFW_KEY_EQUAL && action == GLFW_PRESS)
	{
		calc.setScaleX(calc.getScaleX() + 0.05);
        calc.setScaleY(calc.getScaleY() + 0.05);
        calc.setScaleZ(calc.getScaleZ() + 0.05);
	}

	if (key == GLFW_KEY_MINUS && action == GLFW_PRESS)
	{
        calc.setScaleX(calc.getScaleX() - 0.05);
        calc.setScaleY(calc.getScaleY() - 0.05);
        calc.setScaleZ(calc.getScaleZ() - 0.05);
	}

    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
	{
        calc.setTranslateX(calc.getTranslateX() - 0.05);
	}

	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
	{
		calc.setTranslateX(calc.getTranslateX() + 0.05);
	}

	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		calc.setTranslateY(calc.getTranslateY() + 0.05);
	}

	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		calc.setTranslateY(calc.getTranslateY() - 0.05);
	}

    if(key == GLFW_KEY_A && action == GLFW_PRESS)
    {
        calc.setAngle(calc.getAngle() + 5.0);
    }

    if(key == GLFW_KEY_D && action == GLFW_PRESS)
    {
        calc.setAngle(calc.getAngle() - 5.0);
    }
}

void handleClick(GLFWwindow* window, int button, int action, int mods)
{
    double cursor_x,cursor_y,cursor_z;
    double pos_x,pos_y,pos_z;
    glfwGetCursorPos(window, &cursor_x, &cursor_y);

    double model[16];
    glGetDoublev(GL_MODELVIEW_MATRIX, model);

    double proj[16];
    glGetDoublev(GL_PROJECTION_MATRIX, proj);

    int view[4];
    glGetIntegerv(GL_VIEWPORT, view);

    double win_x,win_y,win_z;
    win_x = cursor_x;
    win_y = view[3] - cursor_y;

    glReadPixels(int(win_x), int(win_y), 1, 1, GL_DEPTH_COMPONENT, GL_DOUBLE, &win_z);

    gluUnProject(win_x, win_y, win_z, model, proj, view, &pos_x, &pos_y, &pos_z);

    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        calc.printText(pos_x, pos_y);
    }

    if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        calc.clickButton(pos_x, pos_y);
    }

    if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
    {
        calc.unclickButton(pos_x, pos_y);
    }
}

void handleDrag(GLFWwindow* window, double cursor_x, double cursor_y)
{
    double cursor_z;
    double pos_x,pos_y,pos_z;
    double model[16];
    glGetDoublev(GL_MODELVIEW_MATRIX, model);

    double proj[16];
    glGetDoublev(GL_PROJECTION_MATRIX, proj);

    int view[4];
    glGetIntegerv(GL_VIEWPORT, view);

    double win_x,win_y,win_z;
    win_x = cursor_x;
    win_y = view[3] - cursor_y;

    glReadPixels(int(win_x), int(win_y), 1, 1, GL_DEPTH_COMPONENT, GL_DOUBLE, &win_z);

    gluUnProject(win_x, win_y, win_z, model, proj, view, &pos_x, &pos_y, &pos_z);

    calc.Drag(pos_x,pos_y);
}

int main()
{
    GLint height = 800,width = 600;

    if(!glfwInit())
    {
        glfwTerminate();
        return 0;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    GLFWwindow *mainWindow = glfwCreateWindow(width,height,"Calculator",NULL,NULL);

    if(!mainWindow)
    {
        glfwTerminate();
        return 0;
    }

    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

    glfwMakeContextCurrent(mainWindow);

    glewExperimental = GL_TRUE;

    if(glewInit() != GLEW_OK)
    {
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 0;
    }

    glViewport(0, 0, bufferWidth, bufferHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);

    calc.construct();

    while(!glfwWindowShouldClose(mainWindow))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();
        glfwSetKeyCallback(mainWindow, handleKeys);
        glfwSetMouseButtonCallback(mainWindow, handleClick);
        glfwSetCursorPosCallback(mainWindow, handleDrag);

        calc.display();

        glfwSwapBuffers(mainWindow);
    }
}
