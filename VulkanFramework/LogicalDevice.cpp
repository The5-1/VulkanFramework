#include "LogicalDevice.h"



LogicalDevice::LogicalDevice()
{
}


LogicalDevice::~LogicalDevice()
{
}


//void LogicalDevice::createLogicalDevice() {
//	QueueFamilyIndices indices = findQueueFamilies(physicalDevice);
//
//	VkDeviceQueueCreateInfo queueCreateInfo = {};
//	queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
//	queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
//	queueCreateInfo.queueCount = 1;
//
//	float queuePriority = 1.0f;
//	queueCreateInfo.pQueuePriorities = &queuePriority;
//
//	VkPhysicalDeviceFeatures deviceFeatures = {};
//
//	VkDeviceCreateInfo createInfo = {};
//	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
//
//	createInfo.pQueueCreateInfos = &queueCreateInfo;
//	createInfo.queueCreateInfoCount = 1;
//
//	createInfo.pEnabledFeatures = &deviceFeatures;
//
//	createInfo.enabledExtensionCount = 0;
//
//	if (enableValidationLayers) {
//		createInfo.enabledLayerCount = static_cast<uint32_t>(layersManager->validationLayers.size());
//		createInfo.ppEnabledLayerNames = layersManager->validationLayers.data();
//	}
//	else {
//		createInfo.enabledLayerCount = 0;
//	}
//
//	if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) {
//		throw std::runtime_error("failed to create logical device!");
//	}
//
//	vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
//}
