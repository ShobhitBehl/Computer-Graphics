#include "../include/Controller.h"

int main(){
	View view(800,800);
	Scene scene;
	Controller controller(view, scene);
	controller.display();
}