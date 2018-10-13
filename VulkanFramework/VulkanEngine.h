#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GL/glfw3.h>

#include "ValidationLayersManager.h"

class VulkanEngine
{
private:
	VkInstance m_instance;
	ValidationLayersManager* m_validationLayersManager = nullptr;

#ifdef NDEBUG
	const bool m_enableValidationLayers = false;
#else
	const bool m_enableValidationLayers = true;
#endif

public:
	VulkanEngine();
	~VulkanEngine();
	std::vector<const char*> getRequiredExtensions();
	void createInstance();
};

