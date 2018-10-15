#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GL/glfw3.h>




class Window
{
private:
	GLFWwindow* window;
	const int WIDTH = 800;
	const int HEIGHT = 600;
public:
	Window();
	~Window();
	void initWindow();
	bool shouldClose();
};

