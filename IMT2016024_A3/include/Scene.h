#include "../include/Model.h"

using namespace std;

class Scene{
private:
	vector <Model> models;
	glm::vec3 lightPos;
	GLuint lightVBO, lightVAO;
	int modelnum;

public:
	Scene();
	void setSelected(int t, glm::vec3 pos);
	void scale(int t);
	void changeTexture();
	void translateLightPos(int mode);
	void drag(glm::vec3 pos);
	void addModel(string filename, float x, float y, float sc);
	void addChildToModel(int index, string filename, float x, float y, float sc);
	void display(GLuint shaderId);
	void changeLight(int index);
	void changeMapping();
};
