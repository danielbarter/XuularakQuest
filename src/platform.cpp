#include "platform.h"

void Platform::init_SDL() {

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(
        "XuularakQuest",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        600,
        600,
        SDL_WINDOW_VULKAN
    );

    if (window == nullptr) {
       std::string error_message = (
           std::ostringstream()
           << "Could not create window: "
           << SDL_GetError() << '\n').str();

       throw std::runtime_error(error_message);
    }
}

void Platform::cleanup_SDL() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Platform::init_vulkan() {

    VkInstanceCreateInfo instance_create_info {};
    VkResult instance_create_result = vkCreateInstance(
	&instance_create_info,
	nullptr,
	&instance);


    if ( instance_create_result != VK_SUCCESS )
	throw std::runtime_error("failed to create instance");

    unsigned int device_count = 0;

    vkEnumeratePhysicalDevices(instance, &device_count, nullptr);

    if ( device_count == 0 )
	throw std::runtime_error("failed to find GPUs with Vulkan support");

    std::vector<VkPhysicalDevice> devices(device_count);
    vkEnumeratePhysicalDevices(instance, &device_count, devices.data());

    VkPhysicalDevice physical_device = VK_NULL_HANDLE;

    for ( VkPhysicalDevice device : devices ) {
	VkPhysicalDeviceProperties device_properties;
	vkGetPhysicalDeviceProperties(device, &device_properties);
	if ( device_properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU ||
	     device_properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU )

	    physical_device = device;
    }

    if ( physical_device == VK_NULL_HANDLE )
	throw std::runtime_error("failed to choose a GPU");


    VkDeviceCreateInfo device_create_info {};

    VkResult create_device_result = vkCreateDevice(
	physical_device,
	&device_create_info,
	nullptr,
	&device);

    if ( create_device_result != VK_SUCCESS )
	throw std::runtime_error("failed to create logical device");
}

void Platform::cleanup_vulkan() {
    vkDestroyInstance(instance, nullptr);
}


void Platform::process_event_queue(Game &game) {

    SDL_Event event;
    while (SDL_PollEvent(&event)) {

       switch (event.type) {

       case SDL_KEYDOWN:
           process_keydown( event.key.keysym.sym, game );
           break;

       default:
           break;

       }
    }
}


void Platform::process_keydown(SDL_Keycode sym, Game &game) {

    switch (sym) {

    case SDLK_ESCAPE:
       game.running = false;
       break;

    default:
       break;
    }

}

Platform::Platform() {
    init_SDL();
    init_vulkan();
}

Platform::~Platform() {
    cleanup_vulkan();
    cleanup_SDL();
}
