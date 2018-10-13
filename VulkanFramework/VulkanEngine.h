#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GL/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstring>
#include <cstdlib>

#include "ValidationLayersManager.h"


class VulkanEngine
{
private:
	VkInstance instance;
	ValidationLayersManager* layersManager = nullptr;

#ifdef NDEBUG
	const bool enableValidationLayers = false;
#else
	const bool enableValidationLayers = true;
#endif

public:
	VulkanEngine();
	~VulkanEngine();

	void createInstance();
	std::vector<const char*> getRequiredExtensions();
	bool checkValidationLayerSupport();
};

