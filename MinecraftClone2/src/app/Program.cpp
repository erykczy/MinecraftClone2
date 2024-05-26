#include "Program.h"
#include "src/app/Constants.h"
#include "src/app/util/Debug.h"
#include "src/app/scene/GameScene.h"
#include "src/app/util/Input.h"
#include "src/app/util/Time.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <libraries/stb_image.h>

Program::Program()
	: window{ Constants::defaultWindowWidth, Constants::defaultWindowHeight, Constants::windowTitle }
{
	// initialize libraries
	initializeLibraries();

	// initialize opengl
	initializeOpenGl();

	// initialize input
	Input::initialize(window);

	// initialize block palette
	Blocks::initialize();

	// initialize scene TODO GameScene probably shouldn't be first scene
	activeScene = std::make_unique<GameScene>();
}

Program::~Program() {
	Blocks::destroy();
}

void Program::initializeOpenGl() {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		Debug::logger << "Failed to initialize GLAD" << Debug::endFatalError;
	}
	glEnable(GL_DEPTH_TEST);
}

void Program::initializeLibraries()
{
	stbi_set_flip_vertically_on_load(true);
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