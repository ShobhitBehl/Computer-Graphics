#include "../include/Controller.h"

using namespace std;

Controller::Controller(){};

Controller::Controller(View &v, Scene &s){
    scene = s;
    view = v;
}

void Controller::handleKeys(GLFWwindow* window, int key, int code, int action, int mode){
	if(key == GLFW_KEY_D and action == GLFW_PRESS){
		scene.translateLightPos(1);
	}
	else if(key == GLFW_KEY_A and action == GLFW_PRESS){
		scene.translateLightPos(-1);
	}
	else if(key == GLFW_KEY_W and action == GLFW_PRESS){
		scene.translateLightPos(2);
	}
	else if(key == GLFW_KEY_S and action == GLFW_PRESS){
		scene.translateLightPos(-2);
	}
	else if(key == GLFW_KEY_E and action == GLFW_PRESS){
		scene.translateLightPos(-3);
	}
	else if(key == GLFW_KEY_Q and action == GLFW_PRESS){
		scene.translateLightPos(3);
	}
	else if(key == GLFW_KEY_MINUS and action == GLFW_PRESS){
		scene.scale(-1);
	}
	else if(key == GLFW_KEY_EQUAL and action == GLFW_PRESS){
		scene.scale(1);
	}
	else if(key == GLFW_KEY_1 and action == GLFW_PRESS){
		scene.changeLight(0);
	}
	else if(key == GLFW_KEY_2 and action == GLFW_PRESS){
		scene.changeLight(1);
	}
	else if(key == GLFW_KEY_3 and action == GLFW_PRESS){
		scene.changeLight(2);
	}
	else if(key == GLFW_KEY_4 and action == GLFW_PRESS){
		scene.changeLight(3);
	}	
}

void Controller::handleClick(GLFWwindow* window, int button, int action, int mods){
    double cursor_x, cursor_y, cursor_z;
    glfwGetCursorPos(window, &cursor_x, &cursor_y);

	float win_x, win_y, win_z;
    win_x = cursor_x;
    win_y = 1000 - cursor_y;

	glReadPixels(int(win_x), int(win_y), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &win_z);
	
	win_x = win_x/500 - 1;
	win_y = win_y/500 - 1;
	win_z = 2*win_z - 1;
	
	glm::vec3 pos = glm::vec3(win_x, win_y, win_z);

	if(button == GLFW_MOUSE_BUTTON_LEFT and action == GLFW_PRESS){
		scene.setSelected(1, pos);
	}
	else if(button == GLFW_MOUSE_BUTTON_RIGHT and action == GLFW_PRESS){
		scene.setSelected(2, pos);
	}
	else if(action == GLFW_RELEASE){
		scene.setSelected(0,pos);
	}
}

void Controller::handleDrag(GLFWwindow* window, double cursor_x, double cursor_y){
	float win_x, win_y, win_z;
    win_x = cursor_x;
    win_y = 1000 - cursor_y;

	glReadPixels(int(win_x), int(win_y), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &win_z);
	
	win_x = win_x/500 - 1;
	win_y = win_y/500 - 1;
	win_z = 2*win_z - 1;
	
    glm::vec3 pos = glm::vec3(win_x, win_y, win_z);
    	
	scene.drag(pos);
}

void func1(GLFWwindow* window, int key, int code, int action, int mode){
    static_cast<Controller*>(glfwGetWindowUserPointer(window))->handleKeys(window, key, code, action, mode);
}

void func2(GLFWwindow* window, int button, int action, int mods){
    static_cast<Controller*>(glfwGetWindowUserPointer(window))->handleClick(window, button, action, mods);
}

void func3(GLFWwindow* window, double cursor_x, double cursor_y){
    static_cast<Controller*>(glfwGetWindowUserPointer(window))->handleDrag(window, cursor_x, cursor_y);
}

void Controller::display(){
    GLFWwindow* mainWindow;
    mainWindow = view.create_window();
	
	Shader shader("shaders/vert_shader", "shaders/frag_shader");
	shader.createShader();

	Texture texture1;
	texture1.create("./textures/Chessboard.png");
	texture1.bind(0);

	// scene.addModel("./data/beethoven.ply");
	// scene.addModel("./data/mug.ply");
	scene.addModel("./data/sphere.ply");
	// scene.addModel("./data/cube.ply");

	scene.setTexture(0, 0);
    
    Controller* controller = this;

    while(!glfwWindowShouldClose(mainWindow))
	{
        glfwPollEvents();

        glfwSetWindowUserPointer(mainWindow, controller);
        
		glfwSetKeyCallback(mainWindow, func1);
		glfwSetMouseButtonCallback(mainWindow, func2);
        glfwSetCursorPosCallback(mainWindow, func3);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		scene.display(shader.getshaderID());

		glfwSwapBuffers(mainWindow);
	}
}

