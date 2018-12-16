#include "PhysicalDevice.h"



PhysicalDevice::PhysicalDevice()
{
}


PhysicalDevice::~PhysicalDevice()
{
	vkDestroyDevice(device, nullptr);
}


void PhysicalDevice::pickPhysicalDevice(VkInstance& instance)
{
	uint32_t deviceCount = 0;
	auto err = vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
	if (err) {
		printf("Error trying to find GPUs!\n");
	}


	if (deviceCount == 0) {
		throw std::runtime_error("Failed to find GPUs!");
	}

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

	for (const auto& device : devices) {
		if (isDeviceSuitable(device)) {
			physicalDevice = device;
			break;
		}
	}

	if (physicalDevice == VK_NULL_HANDLE) {
		throw std::runtime_error("failed to find a suitable GPU!");
	}

	//VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

	//uint32_t deviceCount = 0;
	//vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

	//if (deviceCount == 0) {
	//	throw std::runtime_error("failed to find GPUs with Vulkan support!");
	//}

	//std::vector<VkPhysicalDevice> devices(deviceCount);
	//vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

	//// Use an ordered map to automatically sort candidates by increasing score
	//std::multimap<int, VkPhysicalDevice> candidates;

	//for (const auto& device : devices) {
	//	int score = rateDeviceSuitability(device);
	//		candidates.insert(std::make_pair(score, device));
	//}

	//// Check if the best candidate is suitable at all
	//if (candidates.rbegin()->first > 0) {
	//	physicalDevice = candidates.rbegin()->second;
	//}
	//else {
	//	throw std::runtime_error("failed to find a suitable GPU!");
	//}
}


int PhysicalDevice::rateDeviceSuitability(VkPhysicalDevice device) {
	VkPhysicalDeviceProperties deviceProperties;
	VkPhysicalDeviceFeatures deviceFeatures;
	vkGetPhysicalDeviceProperties(device, &deviceProperties);
	vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

	int score = 0;

	// Discrete GPUs have a significant performance advantage
	if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
		score += 1000;
	}

	// Maximum possible size of textures affects graphics quality
	score += deviceProperties.limits.maxImageDimension2D;

	// Application can't function without geometry shaders
	if (!deviceFeatures.geometryShader) {
		return 0;
	}

	return score;
}

QueueFamilyIndices PhysicalDevice::findQueueFamilies(VkPhysicalDevice device) {
	QueueFamilyIndices indices;

	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

	int i = 0;
	for (const auto& queueFamily : queueFamilies) {
		if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			indices.graphicsFamily = i;
		}

		if (indices.isComplete()) {
			break;
		}

		i++;
	}

	return indices;
}

bool PhysicalDevice::isDeviceSuitable(VkPhysicalDevice device) {
	QueueFamilyIndices indices = findQueueFamilies(device);

	return indices.isComplete();
}

void PhysicalDevice::createLogicalDevice(ValidationLayersManager* layersManager) {
	QueueFamilyIndices indices = findQueueFamilies(physicalDevice);

	VkDeviceQueueCreateInfo queueCreateInfo = {};
	queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
	queueCreateInfo.queueCount = 1;

	float queuePriority = 1.0f;
	queueCreateInfo.pQueuePriorities = &queuePriority;

	VkPhysicalDeviceFeatures deviceFeatures = {};

	VkDeviceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

	createInfo.pQueueCreateInfos = &queueCreateInfo;
	createInfo.queueCreateInfoCount = 1;

	createInfo.pEnabledFeatures = &deviceFeatures;

	createInfo.enabledExtensionCount = 0;

	if (enableValidationLayers) {
		createInfo.enabledLayerCount = static_cast<uint32_t>(layersManager->validationLayers.size());
		createInfo.ppEnabledLayerNames = layersManager->validationLayers.data();
	}
	else {
		createInfo.enabledLayerCount = 0;
	}

	if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) {
		throw std::runtime_error("failed to create logical device!");
	}

	vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
}