#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GL/glfw3.h>
#include <iostream>
#include <vector>
#include "optional.h"
#include "ValidationLayersManager.h"

struct QueueFamilyIndices {
	tl::optional<uint32_t> graphicsFamily;
	tl::optional<uint32_t> presentFamily;

	bool isComplete() {
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

class PhysicalDevice
{
public:
	//Physical Device
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

	//Logical Device
	VkDevice device;
	VkQueue graphicsQueue;

#ifdef NDEBUG
	const bool enableValidationLayers = false;
#else
	const bool enableValidationLayers = true;
#endif

public:
	PhysicalDevice();
	~PhysicalDevice();
	void pickPhysicalDevice(VkInstance & instance);
	int rateDeviceSuitability(VkPhysicalDevice device);
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
	bool isDeviceSuitable(VkPhysicalDevice device);
	void createLogicalDevice(ValidationLayersManager* layersManager);
};

