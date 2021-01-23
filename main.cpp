#include <iostream>
#include "MyScene.h"
//Classe Window.h
#include "Window.h"
//Para utilizar o ponteiro unico
#include <memory>

int main()
{
	//Inicializar classe window.h
	Window w(800, 600, "OpenGL Tutorial");

	//Passar cena para janela utilizando ponteiro unico (Uma janela pode ter varias cenas)
	w.setScene(std::unique_ptr<Scene>(new MyScene()));

	while (!w.shouldClose()) {
		w.update();
	}
}

