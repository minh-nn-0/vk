#include <mvk.hpp>
#include <vector>
#include <array>
#include <cstring>

std::vector<const char*> vk::get_required_extensions()
{
	unsigned glfw_extension_count {0};
	const char** glfw_extensions;
	glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);

	std::vector<const char*> extensions {glfw_extensions, glfw_extensions + glfw_extension_count};

	if (enableValidationLayers)
		extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

	return extensions;
}

bool vk::check_validation_layer()
{
	unsigned layercount;

	vkEnumerateInstanceLayerProperties(&layercount, nullptr);
	std::vector<VkLayerProperties> available_layers(layercount);
	vkEnumerateInstanceLayerProperties(&layercount, available_layers.data());

	for (const auto& layer: vk::validation_layers)
	{
		bool layerfound = false;

		for (const auto& layerprop: available_layers)
		{
			if (layer == std::string{layerprop.layerName} == 0)
			{
				layerfound = true;
				break;
			};
		};

		if (!layerfound) return false;
	};
	return true;
};

VkInstance vk::create_instance(const std::string& appname,
								const std::string& enginename, 
								const std::array<int,3>& appversion,
								const std::array<int,3>& engineversion)
{
	auto& [a,b,c] = appversion;
	auto& [d,e,f] = engineversion;
	VkApplicationInfo appinfo
	{	
		.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pApplicationName = appname.data(),
		.applicationVersion = VK_MAKE_VERSION(a,b,c),
		.pEngineName = enginename.data(),
		.engineVersion = VK_MAKE_VERSION(d,e,f),
		.apiVersion = VK_API_VERSION_1_3
	};

	std::vector<const char*> extensions = get_required_extensions();
	
	VkInstanceCreateInfo createinfo
	{
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pApplicationInfo = &appinfo,
		.enabledExtensionCount = static_cast<unsigned>(extensions.size()),
		.ppEnabledExtensionNames = extensions.data(),
	};
	
	if (enableValidationLayers)
	{
		if (!check_validation_layer())
			throw std::runtime_error("validation layer requested but not available");
		createinfo.enabledLayerCount = validation_layers.size();
		createinfo.ppEnabledLayerNames = validation_layers.data();
	}
	else createinfo.enabledLayerCount = 0;
	

	VkInstance rs_vkinstance;
	if (vkCreateInstance(&createinfo, nullptr, &rs_vkinstance) != VK_SUCCESS)
		throw std::runtime_error("failed to create vulkan instance");

	unsigned extensions_count = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensions_count, nullptr);
	std::vector<VkExtensionProperties> extensions_props {extensions_count};

	vkEnumerateInstanceExtensionProperties(nullptr, &extensions_count, extensions_props.data());
	
	std::cout << "available extensions " << extensions_count<< "\n";
	for (const auto& extension: extensions_props)
		std::cout << '\t' << extension.extensionName << '\n';

	return rs_vkinstance;
};


vk::app::app(const std::string& wname, int width, int height)
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	
	_window = glfwCreateWindow(width, height, wname.c_str(), nullptr, nullptr);
	
	_vkinstance = create_instance();
};

vk::app::~app()
{
	vkDestroyInstance(_vkinstance, nullptr);
	glfwDestroyWindow(_window);
	glfwTerminate();
};

void vk::app::main_loop()
{
	while (!glfwWindowShouldClose(_window))
	{
		glfwPollEvents();
	};
};

void vk::app::run()
{
	app::main_loop();
};
