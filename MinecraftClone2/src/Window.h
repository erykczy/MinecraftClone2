#pragma once

#include "src/event/IEventSender.h"
#include "src/event/IWindowEventListener.h"
#include <string_view>

struct GLFWwindow;

class Window final : public IEventSender<IWindowEventListener> {
public:
	static Window* s_activeWindow;

	Window(int screenWidth, int screenHeight, std::string_view title);
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	~Window();

	void swapBuffers();
	void pollEvents();
	void close();
	bool isClosed() const { return m_closed; }
	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }
	float getAspectRatio() const { return static_cast<float>(m_width) / m_height; }

	static void onWindowSizeChanged(GLFWwindow* window, int width, int height);

private:
	GLFWwindow* m_glfwWindow{};
	bool m_closed{ false };
	int m_width{};
	int m_height{};

};