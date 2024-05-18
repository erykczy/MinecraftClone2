#pragma once

#include <string_view>

struct GLFWwindow;

class Window final {
public:
	Window(int screenWidth, int screenHeight, std::string_view title);
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	~Window();

	void swapBuffers();
	void pollEvents();
	void close();
	bool isClosed() const { return m_closed; }

	static void onWindowSizeChanged(GLFWwindow* window, int width, int height);

private:
	static Window* activeWindow;
	GLFWwindow* m_glfwWindow{};
	bool m_closed{ false };

};