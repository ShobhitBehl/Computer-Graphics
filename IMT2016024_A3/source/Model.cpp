#include "../include/Model.h"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

#define PI 3.141592654


Model::Model(int mn){
    selected = 0;
    textureID = 0;
    mappingID = 0;
    modelnum = mn;
    translation = glm::mat4(1.0);
    rotation = glm::mat4(1.0);
    scale = glm::scale(glm::mat4(1.0), glm::vec3(0.3f, 0.3f, 0.3f));
    motion = 0;
    period = 0;
    rot = 0;
};

Model::Model(float x, float y, int mn, float sc){
    selected = 0;
    textureID = 0;
    mappingID = 0;
    modelnum = mn;
    translation = glm::translate(glm::mat4(1.0), glm::vec3(x, y, 0.0));
    rotation = glm::mat4(1.0);
    scale = glm::scale(glm::mat4(1.0), glm::vec3(sc, sc, sc));
    revolution = glm::mat4(1.0);
    motion = 0;
    period = 0;
    rot = 0;
}

Model::Model(const Model &m){
    VAO = m.VAO;
    VBO = m.VBO;
    IBO = m.IBO;
    translation = m.translation;
    rotation = m.rotation;
    scale = m.scale;
    num_vertices = m.num_vertices;
    num_indices = m.num_indices;
    selected = m.selected;
    min_x = m.min_x;
    min_y = m.min_y;
    min_z = m.min_z;
    max_x = m.max_x;
    max_y = m.max_y;
    max_z = m.max_z;
    selectPos = m.selectPos;
    vertices = m.vertices;
    indices = m.indices;
    mappingID = m.mappingID;
    textureID = m.textureID;
    modelnum = m.modelnum;
    children = m.children;
    revolution = m.revolution;
    motion = m.motion;
    period = m.period;
    rot = m.rot;
}

void Model::changeTexture(){
    if(selected == 1){
        textureID = (textureID + 1)%4;
    }
    for(int i = 0; i<children.size(); i++){
        children[i]->changeTexture();
    }
}

void Model::setTranslation(glm::mat4 mat){
    translation = mat;
}

void Model::setRotation(glm::mat4 mat){
    rotation = mat;
}

void Model::setScale(glm::mat4 mat){
    scale = mat;
}

void Model::setRotate(){
    if(selected == 1){
        rot = !rot;
    }
    for(int i = 0; i<children.size(); i++)
    {
        children[i]->setRotate();
    }
}

void Model::setSelected(int t, glm::vec3 pos, glm::mat4 worldMatrix){

    if(t == 0){
        selected = 0;
    }
    else{
        glm::mat4 model = revolution*worldMatrix*translation*rotation*scale;
        
        glm::mat4 inv = glm::inverse(model);

        glm::vec4 orig_pos = glm::vec4(inv*glm::vec4(pos,1.0));

        if(min_x - 0.01 <= orig_pos.x and max_x + 0.01 >= orig_pos.x and min_y - 0.01 <= orig_pos.y and max_y + 0.01 >= orig_pos.y and min_z - 0.01 <= orig_pos.z and max_z + 0.01 >= orig_pos.z){
            selected = t;
            selectPos = pos;
        }
    }
    for(int i = 0; i<children.size(); i++)
    {
        children[i]->setSelected(t, pos, worldMatrix*translation*scale);
    }
}

void Model::scaleModel(int t){
    if(selected){
        if(t == 1){
            scale = glm::scale(scale, glm::vec3(1.1f, 1.1f, 1.1f));
        }
        else{
            scale = glm::scale(scale, glm::vec3(0.9f, 0.9f, 0.9f));
        }
    }
    for(int i = 0; i<children.size(); i++)
    {
        children[i]->scaleModel(t);
    }
}

void Model::planarTexture(){
    for(int i = 0; i<num_vertices; i++){
        glm::vec2 tex;
        glm::vec3 pos = vertices[i].getPosition();
        tex.x = (pos.x - min_x) / (max_x - min_x);
        tex.y = (pos.y - min_y) / (max_y - min_y);
        vertices[i].setTexture(tex);
    }
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, num_vertices*sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
}

void Model::cylindricalTexture(){
    for(int i = 0; i<num_vertices; i++){
        glm::vec2 tex;
        glm::vec3 pos = vertices[i].getPosition();
        tex.x = (PI + atan2(pos.z, pos.x))  / (2*PI);
        tex.y = (pos.y - min_y) / (max_y - min_y);
        vertices[i].setTexture(tex);
    }
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, num_vertices*sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
}

void Model::sphericalTexture(){
    float radius = -1;
    for(int i = 0; i<num_vertices; i++)
    {
        glm::vec3 pos = vertices[i].getPosition();
        float tempr = sqrt(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z );
        if(tempr > radius)
        {
            radius = tempr;
        }
    }

    for(int i = 0; i<num_vertices; i++){
        glm::vec2 tex;
        glm::vec3 pos = vertices[i].getPosition();

        tex.y = (asin(pos.y / radius) + PI/2) / PI;
        
        if(pos.x < 0){
            tex.x = acos(pos.z / (radius * sin(PI * tex.y))) / (2*PI);
        }
        else{
            tex.x = (2*PI - acos(pos.z / (radius * sin(PI * tex.y)))) / (2*PI);
        }
        vertices[i].setTexture(tex);
    }
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, num_vertices*sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
}

void Model::changeMapping(){
    if(selected == 1){
        mappingID = (mappingID + 1)%3;
        if(mappingID == 0){
            planarTexture();
        }
        else if(mappingID == 1){
            cylindricalTexture();
        }
        else if(mappingID == 2){
            sphericalTexture();
        }
    }
    for(int i = 0; i<children.size(); i++)
    {
        children[i]->changeMapping();
    }
}

void Model::drag(glm::vec3 pos){
    if(selected == 1){
        glm::vec3 diff = pos - selectPos;
        translation = glm::translate(translation, glm::vec3(diff.x, diff.y, 0.0f));
    }
    else if(selected == 2){

        glm::vec3 orig_pos = pos;
        glm::vec3 orig_selectPos = selectPos;

        float d = sqrt(orig_pos.x * orig_pos.x + orig_pos.y * orig_pos.y);
        glm::vec3 p1;
        p1.x = orig_pos.x;
        p1.y = orig_pos.y;
        p1.z = cos((3.14159f/2.0f) * (d < 1.0 ? d : 1.0f));

        d = sqrt(orig_selectPos.x * orig_selectPos.x + orig_selectPos.y * orig_selectPos.y);
        glm::vec3 p2;
        p2.x = orig_selectPos.x;
        p2.y = orig_selectPos.y;
        p2.z = cos((3.14159f/2.0f) * (d < 1.0 ? d : 1.0f));

        float angle = 45.0f*sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y) + (p2.z - p1.z)*(p2.z - p1.z));
        glm::vec3 n = glm::cross(p1,p2);

        if(n.x == 0 and n.y == 0 and n.z == 0)
        {
            return;
        }

        glm::quat q = glm::angleAxis(glm::radians(angle),glm::normalize(n));
        rotation = glm::mat4_cast(q)*rotation;
    }
    selectPos = pos;
    for(int i = 0; i<children.size(); i++)
    {
        children[i]->drag(pos);
    }
}

void Model::calcNormals(){

    float num_normals[num_vertices];

    memset(num_normals, 0, sizeof(num_normals));

    for(int i = 0; i < num_indices; i++){
        int i1 = indices[3*i];
        int i2 = indices[3*i + 1];
        int i3 = indices[3*i + 2];

        glm::vec3 pos1 = vertices[i1].getPosition();
        glm::vec3 pos2 = vertices[i2].getPosition();
        glm::vec3 pos3 = vertices[i3].getPosition();

        glm::vec3 normal = glm::normalize(glm::cross(pos2 - pos1, pos3 - pos1));

        vertices[i1].setNormal( vertices[i1].getNormal() + normal );
        vertices[i2].setNormal( vertices[i2].getNormal() + normal );
        vertices[i3].setNormal( vertices[i3].getNormal() + normal );

        num_normals[i1]++;
        num_normals[i2]++;
        num_normals[i3]++;
    }

    for(int i = 0; i < num_vertices; i++){
        vertices[i].setNormal((vertices[i].getNormal() / num_normals[i]));
    }
}

void Model::splat(){
    vector <Vertex> splat_vertices(num_indices*21);
    vector <GLuint> splat_indices(num_indices*60);
    float circle_vertices[] = {
        0.0, 0.0, 0.0,
        1.0, 0.0, 0.0,
        0.951, 0.309, 0.0,
        0.809, 0.587, 0.0,
        0.587, 0.809, 0.0,
        0.309, 0.951, 0.0,
        0.0, 1.0, 0.0,
        -0.309, 0.951, 0.0,
        -0.587, 0.809, 0.0,
        -0.809, 0.587, 0.0,
        -0.951, 0.309, 0.0,
        -1.0, 0.0, 0.0,
        -0.951, -0.309, 0.0,
        -0.809, -0.587, 0.0,
        -0.587, -0.809, 0.0,
        -0.309, -0.951, 0.0,
        0.0, -1.0, 0.0,
        0.309, -0.951, 0.0,
        0.587, -0.809, 0.0,
        0.809, -0.587, 0.,
        0.951, -0.309, 0.0
    };
    GLuint circle_indices[] = {
        0, 1, 2,
        0, 2, 3,
        0, 3, 4,
        0, 4, 5,
        0, 5, 6,
        0, 6, 7,
        0, 7, 8, 
        0, 8, 9,
        0, 9, 10,
        0, 10, 11,
        0, 11, 12,
        0, 12, 13,
        0, 13, 14,
        0, 14, 15,
        0, 15, 16,
        0, 16, 17,
        0, 17, 18,
        0, 18, 19,
        0, 19, 20,
        0, 20, 1
    };

    for(int i = 0; i<num_indices; i++){
        int i1 = indices[3*i];
        int i2 = indices[3*i + 1];
        int i3 = indices[3*i + 2];

        glm::vec3 pos1 = vertices[i1].getPosition();
        glm::vec3 pos2 = vertices[i2].getPosition();
        glm::vec3 pos3 = vertices[i3].getPosition();

        glm::vec3 normal = glm::normalize(glm::cross(pos2 - pos1, pos3 - pos1));

        glm::vec3 axis = glm::cross(normal, glm::vec3(0.0f, 0.0f, -1.0f));

        float angle = acos(glm::dot(normal, glm::vec3(0.0f, 0.0f, -1.0f)));

        glm::vec3 side1 = pos2 - pos1;
        glm::vec3 side2 = pos3 - pos2;
        glm::vec3 side3 = pos3 - pos1;

        float len1 = sqrt(side1.x * side1.x + side1.y * side1.y + side1.z * side1.z);
        float len2 = sqrt(side2.x * side2.x + side2.y * side2.y + side2.z * side2.z);
        float len3 = sqrt(side3.x * side3.x + side3.y * side3.y + side3.z * side3.z);

        glm::vec3 incenter;
        incenter.x = (len1*pos3.x + len2*pos1.x + len3*pos2.x)/(len1 + len2 + len3);
        incenter.y = (len1*pos3.y + len2*pos1.y + len3*pos2.y)/(len1 + len2 + len3);
        incenter.z = (len1*pos3.z + len2*pos1.z + len3*pos2.z)/(len1 + len2 + len3);

        float s = (len1 + len2 + len3)/2;

        float area = sqrt(s * (s - len1)  *(s - len2) * (s - len3));

        float inradius = (area)/(s);

        glm::mat4 translateCircle(1.0);
        glm::mat4 scaleCircle(1.0);
        glm::mat4 rotateCircle(1.0);

        translateCircle = glm::translate(translateCircle, incenter);
        scaleCircle = glm::scale(scaleCircle, glm::vec3(inradius, inradius, inradius));
        if(axis.x != 0 or axis.y != 0 or axis.z != 0){
            rotateCircle = glm::rotate(rotateCircle, -angle, glm::normalize(axis));
        }

        for(int j = 0; j<21; j++){
            glm::vec3 pos = glm::vec3(circle_vertices[3*j], circle_vertices[3*j + 1], circle_vertices[3*j + 2]);
            pos = glm::vec3(translateCircle * rotateCircle * scaleCircle * glm::vec4(pos, 1.0f));
            Vertex v;
            v.setPosition(pos);
            v.setNormal(normal);
            splat_vertices[i*21 + j] = v;  
        }

        for(int j = 0; j<60; j++)
        {
            splat_indices[i*60 + j] = i*21 + circle_indices[j];
        }
    }
    indices = splat_indices;
    vertices = splat_vertices;
    
    num_vertices = num_indices*21;
    num_indices = num_indices*20;

}

void Model::construct(string filename){
    Parser p;
    p.readPly(filename);
    vertices = p.getVertices();
    indices = p.getIndices();

    num_vertices = p.getNumVertices();
    num_indices = p.getNumIndices();

    max_x = p.getMaxX();
    max_y = p.getMaxY();
    max_z = p.getMaxZ();
    min_x = p.getMinX();
    min_y = p.getMinY();
    min_z = p.getMinZ();

    float mid_x = (min_x + max_x) / 2;
    float mid_y = (min_y + max_y) / 2;
    float mid_z = (min_z + max_z) / 2;

    min_x -= mid_x;
    min_y -= mid_y;
    min_z -= mid_z;
    max_x -= mid_x;
    max_y -= mid_y;
    max_z -= mid_z;

    calcNormals();

    int mode = 1;

    if(!mode){
        splat();
    }

    glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3*sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6*sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3*num_indices*sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Model::addChild(Model* m, int index)
{
    if(index == modelnum){
        children.push_back(m);
    }
    for(int i = 0; i<children.size(); i++){
        children[i]->addChild(m, index);
    }
}

void Model::display(GLuint shaderID, int mode, glm::mat4 worldMatrix){

    if(!mode){
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    }

    glm::mat4 model = glm::mat4(1.0);
    model = revolution*worldMatrix*translation*rotation*scale;
    
    GLuint uniformModel = glGetUniformLocation(shaderID, "model");
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

    GLuint uniformTexture = glGetUniformLocation(shaderID, "textureID");
    glUniform1i(uniformTexture, textureID);

    GLuint uniformSource = glGetUniformLocation(shaderID, "source");
    glUniform1i(uniformSource, 0);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 3*num_indices, GL_UNSIGNED_INT , nullptr);
    glBindVertexArray(0);

    for(int i = 0; i<children.size(); i++){
        children[i]->display(shaderID, mode, worldMatrix*translation*scale);
    }
}

void Model::update(int timer, glm::vec3 parent_center, glm::mat4 worldMatrix){
    glm::mat4 model = revolution*worldMatrix*translation*rotation*scale;
    
    glm::vec3 center = glm::vec3(model*glm::vec4(0.0, 0.0, 0.0, 1.0));

    if(motion == 1){
        translation = glm::translate(translation, glm::vec3(0.0, 0.025, 0.0));
        period++;
        if(period == 20){
            period = 0;
            motion = -1;
        }
    }
    else if(motion == -1){
        translation = glm::translate(translation, glm::vec3(0.0, -0.025, 0.0));
        period++;
        if(period == 20){
            period = 0;
            motion = 1;
        }
    }
    else if(motion == 2){
        revolution = glm::rotate(revolution, 0.03f, glm::vec3(0.0, 1.0, 0.0));
    }
    else if(motion == 3){
        glm::vec3 towards = parent_center - center;
        towards = glm::normalize(towards) / 50.0f;
        translation = glm::translate(translation, towards);
    }

    if(rot)
    {
        rotation = glm::rotate(rotation, 0.05f, glm::vec3(0.0, 1.0, 0.0));
    }

    for(int i = 0; i<children.size(); i++){
        children[i]->update(timer, center ,worldMatrix*translation*scale);
    }
}

void Model::setMotion(int index, int m){
    if(index == modelnum)
    {
        motion = m;
    }
    for(int i = 0; i<children.size(); i++){
        children[i]->setMotion(index, m);
    }
}