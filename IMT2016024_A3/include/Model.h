#include "../include/Shader.h"
#include "../include/Parser.h"

using namespace std;

class Model{
private:
	GLuint VAO, VBO, IBO;
	glm::mat4 translation, rotation, scale;
	int num_vertices,num_indices,selected, on;
	float min_x, max_x, min_y, max_y, min_z, max_z;
	glm::vec3 selectPos;
	vector <Vertex> vertices;
	vector <GLuint> indices;

public:
	Model();
	Model(const Model &m);
	void setSelected(int t, glm::vec3 pos);
	void setTranslation(glm::mat4 mat);
	void setRotation(glm::mat4 mat);
	void setScale(glm::mat4 mat);
	void scaleModel(int t);
	void changeLight();
	void drag(glm::vec3 pos);
	void calcNormals();
	void splat();
	void construct(string filename);
	void display(GLuint shaderId, int mode);
};
