#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GL/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstring>
#include <cstdlib>

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
	std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

	return VK_FALSE;
}

class ValidationLayersManager
{
public:
	const std::vector<const char*> validationLayers = { "VK_LAYER_LUNARG_standard_validation" };
	VkDebugUtilsMessengerEXT callback;

public:
	ValidationLayersManager();
	~ValidationLayersManager();
	VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkDebugUtilsMessengerEXT * pCallback);
	void setupDebugCallback(VkInstance instance);
	void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT callback, const VkAllocationCallbacks * pAllocator);
};

