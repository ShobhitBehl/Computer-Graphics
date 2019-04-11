#include "../include/Camera.h"

using namespace std;

Camera::Camera(glm::vec3 pos, float fov, float aspect, float zNear, float zFar){
    perspective = glm::perspective(fov, aspect, zNear, zFar);
    position = pos;
    forward = glm::vec3(0.0, 0.0, 1.0);
    up = glm::vec3(0.0, 1.0, 0.0);
}

glm::mat4 Camera::getProjection(){
    return perspective * glm::lookAt(position, position + forward, up);
    // return perspective;
}
