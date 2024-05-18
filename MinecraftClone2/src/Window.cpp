#include "src/Window.h"

#include "src/Constants.h"
#include "src/Debug.h"
#include <GLFW/glfw3.h>

Window* Window::activeWindow{};

Window::Window(int screenWidth, int screenHeight, std::string_view title) {
    if (activeWindow) {
        Debug::logger << "Only 1 window can be instantiated!" << Debug::endFatalError;
    }
    activeWindow = this;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, Constants::openGlVersionMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, Constants::openGlVersionMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    m_glfwWindow = glfwCreateWindow(screenWidth, screenHeight, title.data(), NULL, NULL);
    if (m_glfwWindow == NULL)
    {
        Debug::logger << "Failed to create GLFW window" << Debug::endFatalError;
    }
    glfwMakeContextCurrent(m_glfwWindow);
    glfwSetFramebufferSizeCallback(m_glfwWindow, Window::onWindowSizeChanged);
    glfwSetInputMode(m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Window::~Window() {
    glfwTerminate();
}

void Window::swapBuffers()
{
    glfwSwapBuffers(m_glfwWindow);
}

void Window::pollEvents()
{
    glfwPollEvents();
    if (glfwWindowShouldClose(m_glfwWindow)) {
        close();
    }
}

void Window::close()
{
    glfwSetWindowShouldClose(m_glfwWindow, true);
    m_closed = true;
}

void Window::onWindowSizeChanged(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}