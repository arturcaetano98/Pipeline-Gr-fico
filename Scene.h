#pragma once
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32s.lib")

#include "GL/glew.h"
#include "GLFW/glfw3.h"

class Scene {
public:
	virtual ~Scene() {}
	//Não especifica um corpo por esse metodo
	virtual void update() = 0;
};