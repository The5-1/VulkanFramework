#include "PhysicalDevice.h"



PhysicalDevice::PhysicalDevice()
{
}


PhysicalDevice::~PhysicalDevice()
{
}


void PhysicalDevice::pickPhysicalDevice(VkInstance& instance)
{
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

	if (deviceCount == 0) {
		throw std::runtime_error("failed to find GPUs with Vulkan support!");
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