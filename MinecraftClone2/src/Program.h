#pragma once
#include "src/Window.h"
#include "src/scene/Scene.h"

#include <memory>

class Program final {
public:
	Window window;
	std::unique_ptr<Scene> activeScene{};

	Program();

	void startProgramLoop();

private:
	void initializeOpenGl();

};