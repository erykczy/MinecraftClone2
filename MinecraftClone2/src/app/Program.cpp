#include "Program.h"
#include "src/app/Constants.h"
#include "src/app/Debug.h"
#include "src/app/scene/GameScene.h"
#include "src/app/Input.h"
#include "src/app/Time.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Program::Program()
	: window{ Constants::defaultWindowWidth, Constants::defaultWindowHeight, Constants::windowTitle }
{
	initializeOpenGl();
	Input::initialize(window);
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
		Time::onFrameStart();
		activeScene->render();

		window.swapBuffers();
		Input::onFrameEnd();
		window.pollEvents();
	}
}