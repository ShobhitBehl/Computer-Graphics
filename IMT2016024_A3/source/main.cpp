#include "../include/Controller.h"

int main(){
	View view(1000,1000);
	Scene scene;
	Controller controller(view, scene);
	controller.display();
}