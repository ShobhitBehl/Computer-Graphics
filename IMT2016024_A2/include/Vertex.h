#include <bits/stdc++.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

class Vertex{
private:
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;

public:
	Vertex();
	Vertex(glm::vec3 pos);
	Vertex(const Vertex &v);
	glm::vec3 getPosition();
	glm::vec3 getColor();
	glm::vec3 getNormal();
	void setPosition(glm::vec3 vec);
	void setColor(glm::vec3 vec);
	void setNormal(glm::vec3 vec);
};
