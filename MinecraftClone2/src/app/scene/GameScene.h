#pragma once
#include "src/app/scene/Scene.h"
#include "src/app/Debug.h"
#include "src/rendering/Model.h"
#include "src/rendering/Material.h"
#include "src/rendering/ClientCamera.h"
#include "src/event/IWindowEventListener.h"
#include <glad/glad.h>

class GameScene final : public Scene, public IWindowEventListener {
public:
	Material testMaterial{ "src/shaders/vertex.glsl", "src/shaders/fragment.glsl" };
	Model testModel{};
	ClientCamera camera{};

	GameScene() {
		Debug::logger << "Game Scene created!" << Debug::endDebug;
		Mesh mesh{
			{
				-0.5f, -0.5f, 0.0f,
				0.5f, -0.5f, 0.0f,
				0.5f, 0.5f, 0.0f,
				-0.5f, 0.5f, 0.0f
			},
			{
				0, 2, 1,
				0, 3, 2
			}
		};
		testModel.setMesh(mesh);
		testModel.setMaterial(&testMaterial);

		Window::s_activeWindow->addListener(this);
	}

	void render() {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.position.z -= 0.04f;

		testModel.setPosition(glm::vec3{ 0, 0, 5 });
		camera.renderModel(testModel);
	}

	void onWindowSizeChanged(Window& window) override {
		Debug::logger << "Window size changed!" << Debug::endDebug;
		camera.setAspectRatio(window.getAspectRatio());
	}
};