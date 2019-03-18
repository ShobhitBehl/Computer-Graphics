#include "View.h"
#include "Scene.h"

using namespace std;

class Controller{
public:
    View view;
    Scene scene;
    Controller();
    Controller(View &v, Scene &s);
    void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
    void handleClick(GLFWwindow* window, int button, int action, int mods);
    void handleDrag(GLFWwindow* window, double cursor_x, double cursor_y);
    void display();
};