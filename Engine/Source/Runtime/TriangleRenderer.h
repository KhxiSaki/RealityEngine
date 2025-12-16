#pragma once

#include "VulkanContext.h"
#include <glm/glm.hpp>
#include <vector>
#include <array>

// Forward declarations
class ImGuiLayer;
class ViewportRenderer;

struct Vertex
{
    glm::vec2 pos;
    glm::vec3 color;

    static VkVertexInputBindingDescription GetBindingDescription()
    {
        VkVertexInputBindingDescription bindingDescription{};
        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(Vertex);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        return bindingDescription;
    }

    static std::array<VkVertexInputAttributeDescription, 2> GetAttributeDescriptions()
    {
        std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};

        // Position attribute
        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, pos);

        // Color attribute
        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex, color);

        return attributeDescriptions;
    }
};

class TriangleRenderer
{
public:
    TriangleRenderer(VulkanContext* context);
    ~TriangleRenderer();

    bool Initialize();
    void Cleanup();
    void DrawFrame();
    void SetImGuiLayer(ImGuiLayer* layer) { imguiLayer = layer; }
    void SetViewportRenderer(ViewportRenderer* renderer) { viewportRenderer = renderer; }

private:
    void CreateGraphicsPipeline();
    void CreateVertexBuffer();
    void CreateCommandBuffers();
    void CreateSyncObjects();
    void RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
    void RecordViewportRender(VkCommandBuffer commandBuffer);

    VkShaderModule CreateShaderModule(const std::vector<char>& code);
    uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

    VulkanContext* vulkanContext;
    ImGuiLayer* imguiLayer = nullptr;
    ViewportRenderer* viewportRenderer = nullptr;

    VkPipelineLayout pipelineLayout = VK_NULL_HANDLE;
    VkPipeline graphicsPipeline = VK_NULL_HANDLE;
    VkPipeline viewportPipeline = VK_NULL_HANDLE;

    VkBuffer vertexBuffer = VK_NULL_HANDLE;
    VkDeviceMemory vertexBufferMemory = VK_NULL_HANDLE;

    std::vector<VkCommandBuffer> commandBuffers;

    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    uint32_t currentFrame = 0;

    const int MAX_FRAMES_IN_FLIGHT = 2;

    // Triangle vertices
    const std::vector<Vertex> vertices = {
        {{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},  // Top - Red
        {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},   // Bottom Right - Green
        {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}   // Bottom Left - Blue
    };
};
