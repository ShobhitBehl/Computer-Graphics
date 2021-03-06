#include "../include/Model.h"

using namespace std;

class Scene{
private:
	vector <Model> models;
	vector <glm::vec3> lightPos;
	vector <int> on;
	vector <float> lightTriangles;
	GLuint lightVBO, lightVAO;
	float speed;
	int modelnum;

public:
	Scene();
	void setSelected(int t, glm::vec3 pos);
	void scale(int t);
	void changeTexture();
	void drag(glm::vec3 pos);
	void addModel(string filename, float x, float y, float sc);
	void addChildToModel(int index, string filename, float x, float y, float sc);
	void display(GLuint shaderId);
	void changeLight(int index);
	void changeMapping();
	void addLight(int index, glm::vec3 pos);
	void update();
	void setMotion(int index, int m);
	void setRotate();
	void changeSpeed(float num);
};
