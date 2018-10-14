#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GL/glfw3.h>
#include <iostream>
#include <vector>
#include "optional.h"

struct QueueFamilyIndices {
	tl::optional<uint32_t> graphicsFamily;

	bool isComplete() {
		return graphicsFamily.has_value();
	}
};

class PhysicalDevice
{
private:
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

public:
	PhysicalDevice();
	~PhysicalDevice();
	void pickPhysicalDevice(VkInstance & instance);
	int rateDeviceSuitability(VkPhysicalDevice device);
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
	bool isDeviceSuitable(VkPhysicalDevice device);
};

