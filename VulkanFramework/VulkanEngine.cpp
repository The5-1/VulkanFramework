#include "VulkanEngine.h"



VulkanEngine::VulkanEngine()
{	
	if (m_enableValidationLayers) {
		std::cout << "Validationlayer active" << std::endl;
	}
	else {
		std::cout << "Validationlayer inactive" << std::endl;
	}

	this->createInstance();

	if (m_enableValidationLayers) {
		m_validationLayersManager->setupDebugCallback(m_instance);
	}
}


VulkanEngine::~VulkanEngine()
{
	if (m_enableValidationLayers) {
		m_validationLayersManager->DestroyDebugUtilsMessengerEXT(m_instance, nullptr);
	}

	vkDestroyInstance(m_instance, nullptr);
}

std::vector<const char*> VulkanEngine::getRequiredExtensions() {
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

	if (m_enableValidationLayers) {
		extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}

	return extensions;
}

void VulkanEngine::createInstance() {
	if (m_enableValidationLayers) {
		m_validationLayersManager = new ValidationLayersManager();
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

	if (m_enableValidationLayers) {
		createInfo.enabledLayerCount = m_validationLayersManager->getNumValidatioLayers();
		createInfo.ppEnabledLayerNames = m_validationLayersManager->getDataValidationLayers();
	}
	else {
		createInfo.enabledLayerCount = 0;
	}

	if (vkCreateInstance(&createInfo, nullptr, &m_instance) != VK_SUCCESS) {
		throw std::runtime_error("failed to create instance!");
	}
}