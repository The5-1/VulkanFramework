#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GL/glfw3.h>

class Window
{
private:
	const int WIDTH = 800;
	const int HEIGHT = 600;
	GLFWwindow* window;

	VkSurfaceKHR surface;

public:
	Window();
	~Window();
	void initWindow();
	bool shouldClose();
	void createSurface(const VkInstance & instance);
	void destroySurface(const VkInstance & instance);
};

