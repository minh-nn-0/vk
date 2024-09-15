#ifndef M_VKAPP_H
#define M_VKAPP_H

#include <vector>
#include <array>
#include <iostream>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>


namespace vk
{

	const std::vector<const char*> validation_layers {"VK_LAYER_KHRONOS_validation"};
#ifdef NDEBUG
constexpr bool enableValidationLayers = false;
#else
constexpr bool enableValidationLayers = true;
#endif
	


	bool check_validation_layer();
	std::vector<const char*> get_required_extensions();
	
	VkInstance create_instance(const std::string& appname = "vk",
								const std::string& enginename = "mg",
								const std::array<int,3>& appversion = {1,0,0}, 
								const std::array<int,3>& engineversion = {1,0,0});

	VkResult create_debugmessenger(VkInstance, VkDebugUtilsMessengerCreateInfoEXT*, 
												VkAllocationCallbacks*, VkDebugUtilsMessengerEXT*);

	inline VKAPI_ATTR VkBool32 VKAPI_CALL debug_Callback( VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
														VkDebugUtilsMessageTypeFlagsEXT messageType,
														const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
														void* pUserData)
	{
		if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) 
		{
			// Message is important enough to show
		}

		std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
		return VK_FALSE;
	}



	struct app
	{
		app(const std::string&, int width, int height);
		~app();

		void main_loop();
		void run();

	private:
		GLFWwindow* 				_window;
		VkInstance 					_vkinstance;
		VkPhysicalDevice 			_pdevice;
		VkDevice 		 			_ldevice;
		VkDebugUtilsMessengerEXT 	_debugmessenger;
	};


};


#endif
