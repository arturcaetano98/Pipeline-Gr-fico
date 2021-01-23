#pragma once
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32s.lib")

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <memory>

class Scene;

class Window {
	//Interface Classe
public:
	Window(int width = 800, int height = 600, const char* title = "");
	void update();
	~Window();
	inline bool shouldClose() const { return m_ShouldClose; }

	//Passar cena para janela
	inline void setScene(std::unique_ptr<Scene> scene) { m_Scene = std::move(scene);}

private:
	bool m_ShouldClose;
	GLFWwindow* m_Window;

	//Ponteiro para cena na janela
	std::unique_ptr<Scene> m_Scene = nullptr;

	static void errorCallback(int error, const char* description);
};