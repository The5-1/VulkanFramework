#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GL/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <map>
#include "optional.h"
#include "ValidationLayersManager.h"

struct QueueFamilyIndices {
	tl::optional<uint32_t> graphicsFamily;

	bool isComplete() {
		return graphicsFamily.has_value();
	}
};

class VulkanEngine
{
private:
	VkInstance instance;
	ValidationLayersManager* layersManager = nullptr;

	VkDevice device;	//Logical device
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE; //Logical device
	VkQueue graphicsQueue;	//Logical device
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

	void pickPhysicalDevice();

	int rateDeviceSuitability(VkPhysicalDevice device);

	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

	bool isDeviceSuitable(VkPhysicalDevice device);

	void createLogicalDevice();

private:

};

