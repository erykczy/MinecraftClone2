#include "Window.h"

#include "src/app/Constants.h"
#include "src/app/Debug.h"
#include <GLFW/glfw3.h>

Window* Window::s_activeWindow{};

Window::Window(int width, int height, std::string_view title) {
    if (s_activeWindow) {
        Debug::logger << "Only 1 window can be instantiated!" << Debug::endFatalError;
    }
    s_activeWindow = this;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, Constants::openGlVersionMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, Constants::openGlVersionMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    m_glfwWindow = glfwCreateWindow(width, height, title.data(), NULL, NULL);
    if (m_glfwWindow == NULL)
    {
        Debug::logger << "Failed to create GLFW window" << Debug::endFatalError;
    }
    glfwMakeContextCurrent(m_glfwWindow);
    glfwSetFramebufferSizeCallback(m_glfwWindow, Window::onWindowSizeChanged);
    glfwSetInputMode(m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    m_width = width;
    m_height = height;
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
    Window::s_activeWindow->m_width = width;
    Window::s_activeWindow->m_height = height;
    Window::s_activeWindow->notifyListeners([](IWindowEventListener* l) { l->onWindowSizeChanged(*Window::s_activeWindow); });
}