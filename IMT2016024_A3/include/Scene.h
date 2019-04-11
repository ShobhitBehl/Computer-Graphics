#include "../include/Model.h"

using namespace std;

class Scene{
private:
	vector <Model> models;
	vector <glm::vec3> lightPos;
	vector <int> on;
	GLuint lightVBO, lightVAO;
	int modelnum;

public:
	Scene();
	void setSelected(int t, glm::vec3 pos);
	void scale(int t);
	void changeTexture();
	void drag(glm::vec3 pos);
	void addModel(string filename, float x, float y, float sc);
	void addChildToModel(int index, string filename, float x, float y, float sc);
	void display(GLuint shaderId, glm::mat4 projection);
	void changeLight(int index);
	void changeMapping();
	void addLight(float x, float y, float z);
};
