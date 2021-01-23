#pragma once
#include "Scene.h"

class MyScene : public Scene{
private:
    GLuint m_ShaderProgram;
    GLuint m_VertexShader;
    GLuint m_FragmentShader;
    GLfloat* m_Vertices;
    GLuint m_VAO;
    GLuint m_VBO;

public:
    MyScene();
    ~MyScene();
    void update() override;
};

