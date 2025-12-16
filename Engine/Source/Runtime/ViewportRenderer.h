#pragma once

#include <vulkan/vulkan.h>
#include <glm/glm.hpp>

class VulkanContext;
class ImGuiLayer;

class ViewportRenderer
{
public:
    ViewportRenderer(VulkanContext* context);
    ~ViewportRenderer();

    bool Initialize(uint32_t width, uint32_t height);
    void Cleanup();
    void Resize(uint32_t width, uint32_t height);
    
    void BeginRenderPass(VkCommandBuffer commandBuffer);
    void EndRenderPass(VkCommandBuffer commandBuffer);
    
    // Get the texture descriptor for ImGui to display
    VkDescriptorSet GetImGuiTextureID() const { return imguiTextureID; }
    
    VkFramebuffer GetFramebuffer() const { return framebuffer; }
    VkRenderPass GetRenderPass() const { return renderPass; }
    
    uint32_t GetWidth() const { return width; }
    uint32_t GetHeight() const { return height; }

private:
    void CreateRenderPass();
    void CreateFramebuffer();
    void CreateRenderTarget();
    void CreateImGuiDescriptor();
    
    VulkanContext* vulkanContext;
    ImGuiLayer* imguiLayer = nullptr;
    
    uint32_t width = 0;
    uint32_t height = 0;
    
    VkImage colorImage = VK_NULL_HANDLE;
    VkDeviceMemory colorImageMemory = VK_NULL_HANDLE;
    VkImageView colorImageView = VK_NULL_HANDLE;
    VkSampler colorSampler = VK_NULL_HANDLE;
    
    VkRenderPass renderPass = VK_NULL_HANDLE;
    VkFramebuffer framebuffer = VK_NULL_HANDLE;
    
    VkDescriptorSet imguiTextureID = VK_NULL_HANDLE;
    
    uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    void TransitionImageLayout(VkImage image, VkFormat format, 
                              VkImageLayout oldLayout, VkImageLayout newLayout);
};
