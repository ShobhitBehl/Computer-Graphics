#include "../include/Scene.h"

using namespace std;

Scene::Scene(){
    lightPos.x = 0;
    lightPos.y = 0;
    lightPos.z = -1.0;
    num_models = 0;
};

void Scene::setSelected(int t, glm::vec3 pos){
    for(int i = 0; i<num_models; i++)
    {
        models[i].setSelected(t, pos);
    }
}

void Scene::scale(int t){
    for(int i = 0; i<num_models; i++)
    {
        models[i].scaleModel(t);
    }
}

void Scene::translateLightPos(int mode){
    if(mode == 1){
        lightPos.x += 0.1;
    }
    else if(mode == -1){
        lightPos.x -= 0.1;
    }
    else if(mode == 2){
        lightPos.y += 0.1;
    }
    else if(mode == -2){
        lightPos.y -= 0.1;
    }
    else if(mode == 3){
        lightPos.z += 0.1;
    }
    else if(mode == -3){
        lightPos.z -= 0.1;
    }

    lightPos.x = min(lightPos.x, 1.0f);
    lightPos.y = min(lightPos.y, 1.0f);
    lightPos.z = min(lightPos.z, 1.0f);
    lightPos.x = max(lightPos.x, -1.0f);
    lightPos.y = max(lightPos.y, -1.0f);
    lightPos.z = max(lightPos.z, -1.0f);
}

void Scene::drag(glm::vec3 pos){
    for(int i = 0; i<num_models; i++)
    {
        models[i].drag(pos);
    }
}

void Scene::addModel(string filename){
    Model m;
    m.construct(filename);
    models[num_models] = m;
    num_models++;
}

void Scene::display(GLuint shaderId){
    glUseProgram(shaderId);

    GLuint uniformlightPos = glGetUniformLocation(shaderId, "lightPos");
    glUniform3fv(uniformlightPos, 1, glm::value_ptr(lightPos));

    glm::vec3 source = glm::vec3(1.0f, 1.0f, 1.0f);

    GLuint uniformsource = glGetUniformLocation(shaderId, "source");
    glUniform3fv(uniformsource, 1, glm::value_ptr(source));

    glm::mat4 model = glm::mat4(1.0);
    
    GLuint uniformModel = glGetUniformLocation(shaderId, "model"); 
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

    vector <float> light_source = {
        lightPos.x, lightPos.y, lightPos.z,
        lightPos.x + 0.03f, lightPos.y, lightPos.z,
        lightPos.x + 0.015f, lightPos.y + 0.03f, lightPos.z
    };

    glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

    glGenBuffers(1, &lightVBO);
    glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
    glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float), &light_source[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
 
    glDrawArrays(GL_TRIANGLES, 0, 9);

    for(int i = 0; i<num_models; i++){
        models[i].display(shaderId, 2);
    }

    glUseProgram(0);
}
