#include "Window.h"
#include <stdexcept>


Window::Window()
{
	initWindow();
}


Window::~Window()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Window::initWindow() {
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr); //(Width, height, title, specifiy monitor, OpenGL only)
}

bool Window::shouldClose() {
	return glfwWindowShouldClose(window);
}

void Window::createSurface(VkInstance & instance)
{
	if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
		throw std::runtime_error("failed to create window surface!");
	}
}
