#include <bits/stdc++.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

class Camera{
private:
    glm::mat4 perspective;
    glm::vec3 position, forward, up;

public:
    Camera(glm::vec3 pos, float fov, float aspect, float zNear, float zFar);
    glm::mat4 getProjection();
};