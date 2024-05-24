#pragma once
#include <glm/vec2.hpp>
#include <stdexcept>
#include <vector>

class Window;
struct GLFWwindow;

namespace Input {
	void initialize(Window& window);

	bool isKeyPressed(int key);
	bool isKeyDown(int key);
	bool isKeyReleased(int key);
	bool isMouseButtonPressed(int button);
	bool isMouseButtonDown(int button);
	bool isMouseButtonReleased(int button);
	glm::vec2 getMousePos();
	glm::vec2 getMousePosDelta();

	void setCursorVisible(bool value);

	void onFrameEnd();

	void onKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
	void onMouseButtonEvent(GLFWwindow* window, int button, int action, int mods);
	void onMousePosEvent(GLFWwindow* window, double posX, double posY);
};