#pragma once
#include <vector>
#include <cstring>
#include <iostream>

#define GLFW_INCLUDE_VULKAN
#include <GL/glfw3.h>

/*ToDo:
-Make this a friend of whichever class has "VkInstance instance" as member

*/
class ValidationLayersManager
{
	friend class VulkanEngine;

private:
	/*ToDo: Read from a config.json
	Possilbe layers can be found at https://vulkan.lunarg.com/doc/view/1.0.13.0/windows/layers.html
	VK_LAYER_LUNARG_standard_validation combines the following layers:
	VK_LAYER_GOOGLE_threading
	VK_LAYER_LUNARG_parameter_validation
	VK_LAYER_LUNARG_device_limits
	VK_LAYER_LUNARG_object_tracker
	VK_LAYER_LUNARG_image
	VK_LAYER_LUNARG_core_validation
	VK_LAYER_LUNARG_swapchain
	VK_LAYER_GOOGLE_unique_objects
	Not included:
	VK_LAYER_LUNARG_api_dump
	*/
	const std::vector<const char*> m_validationLayers = {
		"VK_LAYER_LUNARG_standard_validation"
	};

	VkDebugUtilsMessengerEXT m_callback;
public:
	ValidationLayersManager();
	~ValidationLayersManager();

	bool checkValidationLayerSupport();

	VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkDebugUtilsMessengerEXT * pCallback);

	void setupDebugCallback(VkInstance& instance);

	void DestroyDebugUtilsMessengerEXT(VkInstance& instance, const VkAllocationCallbacks * pAllocator);

	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
		std::cerr << "Validation layer: " << pCallbackData->pMessage << std::endl;

		return VK_FALSE;
	}

	uint32_t getNumValidatioLayers() {
		return static_cast<uint32_t>(m_validationLayers.size());
	}

	const char* const* getDataValidationLayers() {
		return m_validationLayers.data();
	}
};

