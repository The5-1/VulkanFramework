#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GL/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstring>
#include <cstdlib>

#include "ValidationLayersManager2.h"

class VulkanEngine2
{
private:

VkInstance instance;
ValidationLayersManager2* validationsLayersManager = nullptr;

#ifdef NDEBUG
	const bool enableValidationLayers = false;
#else
	const bool enableValidationLayers = true;
#endif

public:
	VulkanEngine2();
	~VulkanEngine2();
	void createInstance();
	std::vector<const char*> getRequiredExtensions();
};

