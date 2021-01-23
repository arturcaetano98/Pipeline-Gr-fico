#include <iostream>
#include "Window.h"
#include "MyScene.h"

Window::Window(int width, int height, const char* title) {

	m_ShouldClose = true;

	//Inicializar biblioteca GLFW
	//Retorna GLTrue ou GLFalse caso algo de errado
	if (!glfwInit()) {
		std::cerr << "Erro inicializando GLFW" << std::endl;
		return;
	}

	//Definição dos atributos do contexto OpenGL
	// Usar OpenGL 3.2
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

	// Não usar modo de compatibilidade
	glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GL_FALSE);

	//Callback de Erro
	glfwSetErrorCallback(Window::errorCallback);

	//Iniciar janela
	m_Window = glfwCreateWindow(width, height, title, NULL, NULL);

	//Checagem janela
	if (!m_Window) {
		std::cerr << "Erro criando janela!" << std::endl;
		return;
	}

	//torna o contexto atual
	glfwMakeContextCurrent(m_Window);

	//Inicializa o GLEW e realiza checagem
	//glewExperimental = GL_TRUE;
	GLenum glewInitErr = glewInit();
	
	if (glewInitErr != GLEW_OK) {
		std::cerr << "Erro inicializando GLEW: " << glewGetErrorString(glewInitErr) << std::endl;
		return;
	}
	
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	std::cout << "Renderizador: " << renderer << std::endl;
	std::cout << "Versao do OpenGL Suportada: " << version << std::endl;

	m_ShouldClose = false;
}

void Window::update(){
	//Desenhar algo
	glfwPollEvents();

	//Checar se a cena valida
	if (m_Scene) {
		m_Scene->update();
	}

	glfwSwapBuffers(m_Window);

	if (m_ShouldClose == false){
		m_ShouldClose = (glfwWindowShouldClose(m_Window) == GL_TRUE);
	}
}

Window::~Window(){
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

void Window::errorCallback(int error, const char* description){
	std::cerr << "Erro" << error << ":" << description << std::endl;
}
