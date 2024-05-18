#include "src/Program.h"
#include "src/Constants.h"
#include "src/Debug.h"
#include "src/scene/GameScene.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Program::Program()
	: window{ Constants::defaultWindowWidth, Constants::defaultWindowHeight, Constants::windowTitle }
{
	initializeOpenGl();
	activeScene = std::make_unique<GameScene>();
}

void Program::initializeOpenGl() {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		Debug::logger << "Failed to initialize GLAD" << Debug::endFatalError;
	}
	glEnable(GL_DEPTH_TEST);
}

void Program::startProgramLoop() {
	while (!window.isClosed()) {
		activeScene->render();

		window.swapBuffers();
		window.pollEvents();
	}
}