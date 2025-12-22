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
    void initVulkan() {

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
        glfwDestroyWindow(window);

        glfwTerminate();
    }

private:
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