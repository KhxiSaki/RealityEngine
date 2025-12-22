#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

class HelloTriangleApplication {
public:
    void run() {
        initwindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    void CreateVulkanInstance()
    {
        // Application info- information about the application
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "Reality Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        // Find the extension count required for vulkan
        uint32_t GLFWVulkanExtensionCount = 0;
        const char** GLFWVulkanExtensions;

        GLFWVulkanExtensions = glfwGetRequiredInstanceExtensions(&GLFWVulkanExtensionCount);

        createInfo.enabledExtensionCount = GLFWVulkanExtensionCount;
        createInfo.ppEnabledExtensionNames = GLFWVulkanExtensions;//determine the global validation layers to enable.
        createInfo.enabledLayerCount = 0; // no vulkan extension is enabled from the extensions as of now

        VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("Failed to create application info and instance!");
        }
        /**
         * https://vulkan-tutorial.com/en/Drawing_a_triangle/Setup/Instance
         * As you'll see, the general pattern that object creation function parameters in Vulkan follow is:
         * Pointer to struct with creation info
         * Pointer to custom allocator callbacks, always nullptr in this tutorial
         * Pointer to the variable that stores the handle to the new object
         */

        /**
         * 1. Create app info
         * 2. Create instance info
         * 3. search and specify the extension required
         * 4. Create instance
         */
    }

    void initVulkan() {
        CreateVulkanInstance();
    }

    void initwindow()
    {
        //Initialize GLFW
        glfwInit();

        // Tell GLFW to not intiialize with OpenGL way
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        //disable window resizable
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        //Create window
        window = glfwCreateWindow(WindowWidth, WindowHeight, "Vulkan", nullptr, nullptr);
    }
    void mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

    void cleanup() {
        vkDestroyInstance(instance, nullptr);

        glfwDestroyWindow(window);

        glfwTerminate();
    }

private:
    // Vulkan Instance object - the connection between your application and the Vulkan library and creating it involves specifying some details about your application to the driver.
    VkInstance instance; 
	GLFWwindow* window;
    const uint32_t WindowWidth = 800;
    const uint32_t WindowHeight = 600;
};

int main() {
    HelloTriangleApplication app;

    try {
        app.run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}