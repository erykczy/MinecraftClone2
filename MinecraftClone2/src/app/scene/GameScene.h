#pragma once
#include "src/app/scene/Scene.h"
#include "src/app/Debug.h"
#include "src/app/Input.h"
#include "src/app/Time.h"
#include "src/rendering/Model.h"
#include "src/rendering/Material.h"
#include "src/rendering/ClientCamera.h"
#include "src/event/IWindowEventListener.h"
#include "src/world/World.h"
#include "src/world/WorldGenerator.h"
#include "src/world/Blocks.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class GameScene final : public Scene, public IWindowEventListener {
public:
	World world{};
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
		Input::setCursorVisible(false);

		auto& chunk{ world.overworld.addChunk(glm::ivec2{ 0, 0 }) };
		WorldGenerator::generateChunk(chunk);
	}

	void render() {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float speed{ 1.5f };
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
		glm::vec2 mouseDelta{ Input::getMousePosDelta() };
		float rotationSpeed{ 1.5f };
		camera.yaw -= rotationSpeed * Time::getDeltaTime() * mouseDelta.x;
		camera.pitch -= rotationSpeed * Time::getDeltaTime() * mouseDelta.y;


		testModel.setPosition(glm::vec3{ 0, 0, 5 });
		camera.renderModel(testModel);
	}

	void onWindowSizeChanged(Window& window) override {
		Debug::logger << "Window size changed!" << Debug::endDebug;
		camera.setAspectRatio(window.getAspectRatio());
	}
};