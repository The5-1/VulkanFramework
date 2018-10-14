#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GL/glfw3.h>

class LogicalDevice
{
public:
	LogicalDevice();
	~LogicalDevice();

	void createLogicalDevice();

private:
	VkDevice device;	
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE; 
	VkQueue graphicsQueue;	

};

