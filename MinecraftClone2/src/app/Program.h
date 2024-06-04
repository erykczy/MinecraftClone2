#pragma once
#include "src/app/Window.h"
#include "src/app/scene/Scene.h"

#include <memory>

class Program final {
public:
	Window window;
	std::unique_ptr<Scene> activeScene{};

	Program();
	~Program();

	void startProgramLoop();

private:
	void initializeOpenGl();
	void initializeLibraries();

};