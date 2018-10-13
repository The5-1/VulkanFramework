#include "VulkanEngine2.h"



VulkanEngine2::VulkanEngine2()
{
	createInstance();

	validationsLayersManager = new ValidationLayersManager2();
	validationsLayersManager->setupDebugCallback(this->instance);
}


VulkanEngine2::~VulkanEngine2()
{
	if (validationsLayersManager->enableValidationLayers) {
		validationsLayersManager->DestroyDebugUtilsMessengerEXT(instance, validationsLayersManager->callback, nullptr);
	}

	vkDestroyInstance(instance, nullptr);
}

void VulkanEngine2::createInstance() {
	if (validationsLayersManager->enableValidationLayers && !validationsLayersManager->checkValidationLayerSupport()) {
		throw std::runtime_error("validation layers requested, but not available!");
	}

	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Hello Triangle";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "No Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	auto extensions = getRequiredExtensions();
	createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
	createInfo.ppEnabledExtensionNames = extensions.data();

	if (validationsLayersManager->enableValidationLayers) {
		createInfo.enabledLayerCount = validationsLayersManager->validationLayers.size();
		createInfo.ppEnabledLayerNames = validationsLayersManager->validationLayers.data();
	}
	else {
		createInfo.enabledLayerCount = 0;
	}

	if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
		throw std::runtime_error("failed to create instance!");
	}
}

std::vector<const char*> VulkanEngine2::getRequiredExtensions() {
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

	if (enableValidationLayers) {
		extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}

	return extensions;
}