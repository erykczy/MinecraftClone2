#pragma once
#include "src/Window.h"

class Program final {
public:
	Window window;

	Program();

	void startProgramLoop();

private:
	void initializeOpenGl();

};