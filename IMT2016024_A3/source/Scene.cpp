#include "../include/Scene.h"

using namespace std;

Scene::Scene(){
    modelnum = 0;
};

void Scene::setSelected(int t, glm::vec3 pos){
    for(int i = 0; i<models.size(); i++)
    {
        models[i].setSelected(t, pos, glm::mat4(1.0));
    }
}

void Scene::addLight(float x, float y, float z){
    lightPos.push_back(glm::vec3(x, y, z));
    on.push_back(1);
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
    if(index < on.size())
        on[index] = !on[index];
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

void Scene::display(GLuint shaderId, glm::mat4 projection){
    glUseProgram(shaderId);

    
    GLuint uniformlightPos = glGetUniformLocation(shaderId, "lightPos");
    glUniform3fv(uniformlightPos, lightPos.size() , glm::value_ptr(lightPos[0]));

    GLuint uniformOn = glGetUniformLocation(shaderId, "on");
    glUniform1iv(uniformOn, 4, &on[0]);

    glm::mat4 model = glm::mat4(1.0);
    
    GLuint uniformModel = glGetUniformLocation(shaderId, "model"); 
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

    // vector <float> light_source = {
    //     lightPos.x, lightPos.y, lightPos.z,
    //     lightPos.x + 0.03f, lightPos.y, lightPos.z,
    //     lightPos.x + 0.015f, lightPos.y + 0.03f, lightPos.z
    // };

    // glGenVertexArrays(1, &lightVAO);
	// glBindVertexArray(lightVAO);

    // glGenBuffers(1, &lightVBO);
    // glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
    // glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float), &light_source[0], GL_STATIC_DRAW);

    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    // glEnableVertexAttribArray(0);
 
    // glDrawArrays(GL_TRIANGLES, 0, 9);

    for(int i = 0; i<models.size(); i++){
        // models[i].display(shaderId, 2, glm::mat4(1.0), projection);
        models[i].display(shaderId, 2, glm::mat4(1.0), glm::mat4(1.0));
        // models[i].rotate();
    }

    glUseProgram(0);
}