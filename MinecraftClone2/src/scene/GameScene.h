#pragma once
#include "src/scene/Scene.h"
#include "src/Debug.h"
#include <glad/glad.h>

class GameScene final : public Scene {
public:
	GameScene() {
		Debug::logger << "Game Scene created!" << Debug::endDebug;
	}

	void render() {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
};