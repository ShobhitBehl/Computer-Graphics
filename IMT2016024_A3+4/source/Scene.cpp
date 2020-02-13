#include "../include/Scene.h"

using namespace std;

Scene::Scene(){
    modelnum = 0;
    speed = 0;
};

void Scene::setSelected(int t, glm::vec3 pos){
    for(int i = 0; i<models.size(); i++)
    {
        models[i].setSelected(t, pos, glm::mat4(1.0));
    }
}

void Scene::changeSpeed(float num)
{
    speed += num;
}

void Scene::addLight(int index, glm::vec3 pos){
    for(int i = 0; i<models.size(); i++)
    {
        models[i].addLight(index, pos);
    }
}

void Scene::changeTexture(){
    for(int i = 0; i<models.size(); i++){
        models[i].changeTexture();
    }
}

void Scene::scale(int t){
    for(int i = 0; i<models.size(); i++)
    {
        models[i].scaleModel(t);
    }
}

void Scene::changeLight(int index)
{
    for(int i = 0; i<models.size(); i++)
    {
        models[i].changeLight(index);
    }
}

void Scene::drag(glm::vec3 pos){
    for(int i = 0; i<models.size(); i++)
    {
        models[i].drag(pos);
    }
}

void Scene::changeMapping(){
    for(int i = 0; i<models.size(); i++){
        models[i].changeMapping();
    }
}

void Scene::addModel(string filename, float x, float y, float sc){
    Model m(x, y, modelnum, sc);
    m.construct(filename);
    m.planarTexture();
    models.push_back(m);
    modelnum++;
}

void Scene::addChildToModel(int index, string filename, float x, float y, float sc){
    Model *m = new Model(x, y, modelnum, sc);
    m->construct(filename);
    m->planarTexture();
    for(int i = 0; i<models.size(); i++){
        models[i].addChild(m, index);
    }
    modelnum++;
}

void Scene::display(GLuint shaderId){
    glUseProgram(shaderId);

    for(int i = 0; i<models.size(); i++){
        models[i].display(shaderId, 2, glm::mat4(1.0));
    }

    glUseProgram(0);
}

void Scene::update(){
    for(int i = 0; i<models.size(); i++){
        models[i].update(speed, glm::vec3(0.0, 0.0, 0.0), glm::mat4(1.0));
    }
}

void Scene::setMotion(int index, int m){
    for(int i = 0; i<models.size(); i++){
        models[i].setMotion(index, m);
    }
}

void Scene::setRotate(){
    for(int i = 0; i<models.size(); i++){
        models[i].setRotate();
    }
}