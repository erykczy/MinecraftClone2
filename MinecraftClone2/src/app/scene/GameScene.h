#pragma once
#include "src/app/scene/Scene.h"
#include "src/app/util/Debug.h"
#include "src/app/util/Input.h"
#include "src/app/util/Time.h"
#include "src/rendering/Model.h"
#include "src/rendering/Material.h"
#include "src/rendering/ClientCamera.h"
#include "src/rendering/ChunkModel.h"
#include "src/rendering/LevelModel.h"
#include "src/world/World.h"
#include "src/world/gen/BasicLevelGenerator.h"
#include "src/world/def/Blocks.h"
#include "src/world/def/BlockDef.h"
#include "src/event/IWindowEventListener.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class GameScene final : public Scene, private IWindowEventListener {
public:
	BasicLevelGenerator overworldGenerator{};
	World world{ &overworldGenerator };
	Material chunkMaterial{ "src/shaders/vertex.glsl", "src/shaders/fragment.glsl" };
	ClientCamera camera{};
	std::unique_ptr<LevelModel> levelModel{};

	GameScene() {
		Debug::logger << "Game Scene created!" << Debug::endDebug;

		Window::s_activeWindow->addListener(this);
		Input::setCursorVisible(false);

		levelModel = std::make_unique<LevelModel>(world.overworld, chunkMaterial);

		constexpr int levelWidth{ 5 };
		for (int x = 0; x < levelWidth; ++x) {
			for (int z = 0; z < levelWidth; ++z) {
				world.overworld.addChunk(glm::ivec2{ x, z });
			}
		}
	}

	void render() {
		glClearColor(0.72f, 0.82f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float speed{ 5.0f };
		if (Input::isKeyDown(GLFW_KEY_ESCAPE))
			Window::s_activeWindow->close();
		if (Input::isKeyDown(GLFW_KEY_LEFT_SHIFT))
			speed *= 2.0f;
		if(Input::isKeyDown(GLFW_KEY_W))
			camera.position += speed * Time::getDeltaTime() * camera.getForward();
		if (Input::isKeyDown(GLFW_KEY_S))
			camera.position -= speed * Time::getDeltaTime() * camera.getForward();
		if (Input::isKeyDown(GLFW_KEY_D))
			camera.position += speed * Time::getDeltaTime() * camera.getRight();
		if (Input::isKeyDown(GLFW_KEY_A))
			camera.position -= speed * Time::getDeltaTime() * camera.getRight();
		if (Input::isKeyDown(GLFW_KEY_SPACE))
			camera.position += speed * Time::getDeltaTime() * camera.getUp();
		if (Input::isKeyDown(GLFW_KEY_LEFT_CONTROL))
			camera.position -= speed * Time::getDeltaTime() * camera.getUp();
		if (Input::isKeyDown(GLFW_KEY_G)) {
			Debug::setWireframeRendering(true);
		}
		else {
			Debug::setWireframeRendering(false);
		}
		glm::vec2 mouseDelta{ Input::getMousePosDelta() };
		float rotationSpeed{ 0.05f };
		camera.yaw -= rotationSpeed * mouseDelta.x;
		camera.pitch -= rotationSpeed * mouseDelta.y;

		camera.render(*levelModel);
	}

private:
	void onWindowSizeChanged(Window& window) override {
		camera.setAspectRatio(window.getAspectRatio());
	}
};