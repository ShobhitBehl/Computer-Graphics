#include "../include/Vertex.h"

using namespace std;

Vertex::Vertex(){};

Vertex::Vertex( glm::vec3 pos ){
    position = pos;
    normal = glm::vec3(0.0f, 0.0f, 0.0f);
}

Vertex::Vertex(const Vertex &v){
    position = v.position;
    normal = v.normal;
    color = v.color;
}

glm::vec3 Vertex::getPosition(){
    return position;
}

glm::vec3 Vertex::getNormal(){
    return normal;
}

glm::vec3 Vertex::getColor(){
    return color;
}

void Vertex::setPosition(glm::vec3 vec){
    position = vec;
}

void Vertex::setNormal(glm::vec3 vec){
    normal = vec;
}

void Vertex::setColor(glm::vec3 vec){
    color = vec;
}
