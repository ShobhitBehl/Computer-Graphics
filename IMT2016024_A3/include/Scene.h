#include "../include/Model.h"

using namespace std;

class Scene{
private:
	Model models[500];
	int num_models;
	glm::vec3 lightPos;
	GLuint lightVBO, lightVAO;

public:
	Scene();
	void setSelected(int t, glm::vec3 pos);
	void scale(int t);
	void setTexture(const string &path, int index);
	void translateLightPos(int mode);
	void drag(glm::vec3 pos);
	void addModel(string filename);
	void display(GLuint shaderId);
	void changeLight(int index);
};
