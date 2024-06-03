#pragma once
#include "src/app/scene/Scene.h"
#include "src/app/util/Debug.h"
#include "src/app/util/Input.h"
#include "src/app/util/Time.h"
#include "src/rendering/Model.h"
#include "src/rendering/Material.h"
#include "src/rendering/ClientCamera.h"
#include "src/event/IWindowEventListener.h"
#include "src/world/World.h"
#include "src/world/gen/WorldGenerator.h"
#include "src/world/def/Blocks.h"
#include "src/world/def/BlockDef.h"
#include "src/rendering/ChunkModel.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class GameScene final : public Scene, private IWindowEventListener {
public:
	World world{};
	std::unique_ptr<ChunkModel> chunkModel{};
	Material testMaterial{ "src/shaders/vertex.glsl", "src/shaders/fragment.glsl" };
	Model testModel{};
	ClientCamera camera{};
	Chunk* chunk{};

	GameScene() {
		Debug::logger << "Game Scene created!" << Debug::endDebug;
		/*Mesh mesh{
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
		testModel.setMaterial(&testMaterial);*/

		Window::s_activeWindow->addListener(this);
		Input::setCursorVisible(false);

		chunk = &world.overworld.addChunk(glm::ivec2{ 0, 0 });
		WorldGenerator::generateChunk(*chunk);

		chunkModel = std::make_unique<ChunkModel>(*chunk, testMaterial);
	}

	void render() {
		glClearColor(0.72f, 0.82f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float speed{ 5.0f };
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

		// TODO: this is debug
		static float s_next = 0.0f;
		if (Time::getTime() > s_next) {
			s_next += 0.1f;
			for (int y = 0; y < 1; ++y) {
				chunk->setBlock(glm::vec3(10, 11 + y, 10), Blocks::all[1]->getDefaultBlockState());
			}
			for (int y = 0; y < 1; ++y) {
				chunk->setBlock(glm::vec3(10, 11 + y, 10), Blocks::all[0]->getDefaultBlockState());
			}
		}

		camera.render(*chunkModel);
	}

private:
	void onWindowSizeChanged(Window& window) override {
		camera.setAspectRatio(window.getAspectRatio());
	}
};