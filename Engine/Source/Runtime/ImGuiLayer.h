#pragma once

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

class VulkanContext;

class ImGuiLayer
{
public:
    ImGuiLayer();
    ~ImGuiLayer();

    bool Initialize(GLFWwindow* window, VulkanContext* context);
    void Cleanup();

    void BeginFrame();
    void EndFrame();
    void Render(VkCommandBuffer commandBuffer);

    bool WantCaptureMouse() const;
    bool WantCaptureKeyboard() const;

private:
    void SetupImGuiStyle();
    void CreateDescriptorPool();

    VulkanContext* vulkanContext = nullptr;
    VkDescriptorPool descriptorPool = VK_NULL_HANDLE;
    bool initialized = false;
};
