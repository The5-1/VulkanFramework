#define GLFW_INCLUDE_VULKAN
#include <GL/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstring>
#include <cstdlib>
#include "VulkanEngine.h"
#include "Window.h"

class HelloTriangleApplication {
public:
	void run() {
		initWindow();
		initVulkan();
		mainLoop();
		cleanup();
	}

private:
	Window* window = nullptr;
	VulkanEngine* engine = nullptr;

	void initWindow() {
		window = new Window();
	}

	void initVulkan() {
		engine = new VulkanEngine();
	}

	void mainLoop() {
		while (!window->shouldClose()) {
			glfwPollEvents();
		}
	}

	void cleanup() {
		delete engine;
		delete window;
	}
};

int main() {
	HelloTriangleApplication app;

	try {
		app.run();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
