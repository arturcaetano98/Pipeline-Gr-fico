#include "MyScene.h"
#include "Util.h"
#include <GL/glew.h>
#include <iostream>
#include <sstream>

// Checagem de compilação de shader
GLint checkShaderCompilation(GLint shader){

	GLint success = 0;
	GLchar infoLog[512];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);
		std::cerr << infoLog << std::endl;
	}
	return success;
}

// Checagem de link do programa
GLint checkProgramLink(GLint shader){
	GLint success = 0;
	GLchar infoLog[512];

	glGetShaderiv(shader, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(shader, sizeof(infoLog), NULL, infoLog);
		std::cerr << infoLog << std::endl;
	}
	return success;
}

MyScene::MyScene() {

	glClearColor(0, 0, 0, 0);

	//Fazer a cena abrir o arquivo com shader a partir do Util.h
	std::stringstream vertexSourceStream;
	std::stringstream fragmentSourceStream;

	loadFile("vertex.vs", vertexSourceStream);
	loadFile("fragment.fs", fragmentSourceStream);

	std::string vertexSource = vertexSourceStream.str();
	std::string fragmentSource = fragmentSourceStream.str();

	const char* buff;

	//Criar um shader
	m_ShaderProgram = glCreateProgram();
	
	//Vertex Shader
	buff = vertexSource.c_str();
	m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_VertexShader, 1, &buff, NULL);
	glCompileShader(m_VertexShader);
	checkShaderCompilation(m_VertexShader);
	glAttachShader(m_ShaderProgram, m_VertexShader);
	glDeleteShader(m_VertexShader);

	//Fragment Shader
	buff = fragmentSource.c_str();
	m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_FragmentShader, 1, &buff, NULL);
	glCompileShader(m_FragmentShader);
	checkShaderCompilation(m_FragmentShader);
	glAttachShader(m_ShaderProgram, m_FragmentShader);
	glDeleteShader(m_FragmentShader);

	//Linking de shader
	glLinkProgram(m_ShaderProgram);
	checkProgramLink(m_ShaderProgram);

	m_Vertices = new GLfloat[18]{
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
	};
	
	//Vertex Buffer Object
	glGenBuffers(1, &m_VBO);

	//Vertex Array Object
	//Criar um ID na GPU com o Array dos Buffers
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	//Vertices e atributos de GL_ARRAY_BUFFER
	glBufferData(GL_ARRAY_BUFFER, 18*sizeof(GLfloat), m_Vertices, GL_STATIC_DRAW);

	//Especificar a interpretação dos vertices do array = 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (GLvoid*)0);

	//Especificar a interpretação das cores do array = 1
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));

	//Habilitar os canal 0 e 1
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

MyScene::~MyScene() {
	glDeleteProgram(m_ShaderProgram);
}

void MyScene::update(){

	//Realiza limpeza de buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Enviar programa a GPU
	glUseProgram(m_ShaderProgram);

	//Utilizar os Buffers, informando-os para o OpenGL
	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	//Desassociar o VAO
	glBindVertexArray(0);
}