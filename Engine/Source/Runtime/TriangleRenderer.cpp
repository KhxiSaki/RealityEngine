#include "TriangleRenderer.h"
#include <iostream>
#include <stdexcept>
#include <cstring>

// Vertex Shader SPIR-V - Manually corrected to fix duplicate ID issue
static const uint32_t vertShaderCode[] = {
    0x07230203, 0x00010000, 0x0008000a, 0x0000002d, 0x00000000, 0x00020011, 0x00000001, 0x0006000b,
    0x00000001, 0x4c534c47, 0x6474732e, 0x3035342e, 0x00000000, 0x0003000e, 0x00000000, 0x00000001,
    0x0009000f, 0x00000000, 0x00000004, 0x6e69616d, 0x00000000, 0x0000000b, 0x0000000f, 0x00000024,
    0x00000028, 0x00030003, 0x00000002, 0x000001c2, 0x00040005, 0x00000004, 0x6e69616d, 0x00000000,
    0x00060005, 0x00000009, 0x505f6c67, 0x65567265, 0x78657472, 0x00000000, 0x00060006, 0x00000009,
    0x00000000, 0x505f6c67, 0x7469736f, 0x006e6f69, 0x00070006, 0x00000009, 0x00000001, 0x505f6c67,
    0x746e696f, 0x657a6953, 0x00000000, 0x00070006, 0x00000009, 0x00000002, 0x435f6c67, 0x4470696c,
    0x61747369, 0x0065636e, 0x00070006, 0x00000009, 0x00000003, 0x435f6c67, 0x446c6c75, 0x61747369,
    0x0065636e, 0x00030005, 0x0000000b, 0x00000000, 0x00050005, 0x0000000f, 0x6f506e69, 0x69746973,
    0x00006e6f, 0x00050005, 0x00000024, 0x67617266, 0x6f6c6f43, 0x00000072, 0x00040005, 0x00000028,
    0x6f436e69, 0x00726f6c, 0x00050048, 0x00000009, 0x00000000, 0x0000000b, 0x00000000, 0x00050048,
    0x00000009, 0x00000001, 0x0000000b, 0x00000001, 0x00050048, 0x00000009, 0x00000002, 0x0000000b,
    0x00000003, 0x00050048, 0x00000009, 0x00000003, 0x0000000b, 0x00000004, 0x00030047, 0x00000009,
    0x00000002, 0x00040047, 0x0000000f, 0x0000001e, 0x00000000, 0x00040047, 0x00000024, 0x0000001e,
    0x00000000, 0x00040047, 0x00000028, 0x0000001e, 0x00000001, 0x00020013, 0x00000002, 0x00030021,
    0x00000003, 0x00000002, 0x00030016, 0x00000006, 0x00000020, 0x00040017, 0x00000007, 0x00000006,
    0x00000004, 0x00040015, 0x00000008, 0x00000020, 0x00000000, 0x0004002b, 0x00000008, 0x0000000a,
    0x00000001, 0x0004001c, 0x0000000c, 0x00000006, 0x0000000a, 0x0006001e, 0x00000009, 0x00000007,
    0x00000006, 0x0000000c, 0x0000000c, 0x00040020, 0x0000000d, 0x00000003, 0x00000009, 0x0004003b,
    0x0000000d, 0x0000000b, 0x00000003, 0x00040015, 0x0000000e, 0x00000020, 0x00000001, 0x0004002b,
    0x0000000e, 0x00000010, 0x00000000, 0x00040017, 0x00000011, 0x00000006, 0x00000002, 0x00040020,
    0x00000012, 0x00000001, 0x00000011, 0x0004003b, 0x00000012, 0x0000000f, 0x00000001, 0x0004002b,
    0x00000006, 0x00000015, 0x00000000, 0x0004002b, 0x00000006, 0x00000016, 0x3f800000, 0x00040020,
    0x0000001a, 0x00000003, 0x00000007, 0x00040017, 0x00000022, 0x00000006, 0x00000003, 0x00040020,
    0x00000023, 0x00000003, 0x00000022, 0x0004003b, 0x00000023, 0x00000024, 0x00000003, 0x00040020,
    0x00000025, 0x00000001, 0x00000022, 0x0004003b, 0x00000025, 0x00000028, 0x00000001, 0x00050036,
    0x00000002, 0x00000004, 0x00000000, 0x00000003, 0x000200f8, 0x00000005, 0x0004003d, 0x00000011,
    0x00000013, 0x0000000f, 0x00050051, 0x00000006, 0x00000014, 0x00000013, 0x00000000, 0x00050051,
    0x00000006, 0x00000017, 0x00000013, 0x00000001, 0x00070050, 0x00000007, 0x00000018, 0x00000014,
    0x00000017, 0x00000015, 0x00000016, 0x00050041, 0x0000001a, 0x0000001b, 0x0000000b, 0x00000010,
    0x0003003e, 0x0000001b, 0x00000018, 0x0004003d, 0x00000022, 0x00000029, 0x00000028, 0x0003003e,
    0x00000024, 0x00000029, 0x000100fd, 0x00010038
};

// Fragment Shader SPIR-V
static const uint32_t fragShaderCode[] = {
    0x07230203, 0x00010000, 0x0008000a, 0x00000013, 0x00000000, 0x00020011, 0x00000001, 0x0006000b,
    0x00000001, 0x4c534c47, 0x6474732e, 0x3035342e, 0x00000000, 0x0003000e, 0x00000000, 0x00000001,
    0x0007000f, 0x00000004, 0x00000004, 0x6e69616d, 0x00000000, 0x00000009, 0x0000000d, 0x00030010,
    0x00000004, 0x00000007, 0x00030003, 0x00000002, 0x000001c2, 0x00040005, 0x00000004, 0x6e69616d,
    0x00000000, 0x00050005, 0x00000009, 0x4374756f, 0x726f6c6f, 0x00000072, 0x00050005, 0x0000000d,
    0x67617266, 0x6f6c6f43, 0x00000072, 0x00040047, 0x00000009, 0x0000001e, 0x00000000, 0x00040047,
    0x0000000d, 0x0000001e, 0x00000000, 0x00020013, 0x00000002, 0x00030021, 0x00000003, 0x00000002,
    0x00030016, 0x00000006, 0x00000020, 0x00040017, 0x00000007, 0x00000006, 0x00000004, 0x00040020,
    0x00000008, 0x00000003, 0x00000007, 0x0004003b, 0x00000008, 0x00000009, 0x00000003, 0x00040017,
    0x0000000b, 0x00000006, 0x00000003, 0x00040020, 0x0000000c, 0x00000001, 0x0000000b, 0x0004003b,
    0x0000000c, 0x0000000d, 0x00000001, 0x0004002b, 0x00000006, 0x00000011, 0x3f800000, 0x00050036,
    0x00000002, 0x00000004, 0x00000000, 0x00000003, 0x000200f8, 0x00000005, 0x0004003d, 0x0000000b,
    0x0000000e, 0x0000000d, 0x00050051, 0x00000006, 0x0000000f, 0x0000000e, 0x00000000, 0x00050051,
    0x00000006, 0x00000010, 0x0000000e, 0x00000001, 0x00050051, 0x00000006, 0x00000012, 0x0000000e,
    0x00000002, 0x00070050, 0x00000007, 0x00000013, 0x0000000f, 0x00000010, 0x00000012, 0x00000011,
    0x0003003e, 0x00000009, 0x00000013, 0x000100fd, 0x00010038
};

TriangleRenderer::TriangleRenderer(VulkanContext* context)
    : vulkanContext(context)
{
}

TriangleRenderer::~TriangleRenderer()
{
    Cleanup();
}

bool TriangleRenderer::Initialize()
{
    try
    {
        CreateVertexBuffer();
        CreateGraphicsPipeline();
        CreateCommandBuffers();
        CreateSyncObjects();
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Triangle renderer initialization failed: " << e.what() << std::endl;
        return false;
    }
}

void TriangleRenderer::Cleanup()
{
    VkDevice device = vulkanContext->GetDevice();

    if (device != VK_NULL_HANDLE)
    {
        vkDeviceWaitIdle(device);

        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
        {
            if (imageAvailableSemaphores[i] != VK_NULL_HANDLE)
            {
                vkDestroySemaphore(device, imageAvailableSemaphores[i], nullptr);
            }
            if (renderFinishedSemaphores[i] != VK_NULL_HANDLE)
            {
                vkDestroySemaphore(device, renderFinishedSemaphores[i], nullptr);
            }
            if (inFlightFences[i] != VK_NULL_HANDLE)
            {
                vkDestroyFence(device, inFlightFences[i], nullptr);
            }
        }

        if (graphicsPipeline != VK_NULL_HANDLE)
        {
            vkDestroyPipeline(device, graphicsPipeline, nullptr);
            graphicsPipeline = VK_NULL_HANDLE;
        }

        if (pipelineLayout != VK_NULL_HANDLE)
        {
            vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
            pipelineLayout = VK_NULL_HANDLE;
        }

        if (vertexBuffer != VK_NULL_HANDLE)
        {
            vkDestroyBuffer(device, vertexBuffer, nullptr);
            vertexBuffer = VK_NULL_HANDLE;
        }

        if (vertexBufferMemory != VK_NULL_HANDLE)
        {
            vkFreeMemory(device, vertexBufferMemory, nullptr);
            vertexBufferMemory = VK_NULL_HANDLE;
        }
    }
}

void TriangleRenderer::CreateGraphicsPipeline()
{
    // Convert uint32_t arrays to char vectors for CreateShaderModule
    std::vector<char> vertShaderBytes(sizeof(vertShaderCode));
    std::memcpy(vertShaderBytes.data(), vertShaderCode, sizeof(vertShaderCode));

    std::vector<char> fragShaderBytes(sizeof(fragShaderCode));
    std::memcpy(fragShaderBytes.data(), fragShaderCode, sizeof(fragShaderCode));

    VkShaderModule vertShaderModule = CreateShaderModule(vertShaderBytes);
    VkShaderModule fragShaderModule = CreateShaderModule(fragShaderBytes);

    VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
    vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
    vertShaderStageInfo.module = vertShaderModule;
    vertShaderStageInfo.pName = "main";

    VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
    fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    fragShaderStageInfo.module = fragShaderModule;
    fragShaderStageInfo.pName = "main";

    VkPipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };

    // Vertex input
    auto bindingDescription = Vertex::GetBindingDescription();
    auto attributeDescriptions = Vertex::GetAttributeDescriptions();

    VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
    vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInputInfo.vertexBindingDescriptionCount = 1;
    vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
    vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
    vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

    // Input assembly
    VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
    inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    inputAssembly.primitiveRestartEnable = VK_FALSE;

    // Viewport and scissor
    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = static_cast<float>(vulkanContext->GetSwapChainExtent().width);
    viewport.height = static_cast<float>(vulkanContext->GetSwapChainExtent().height);
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    VkRect2D scissor{};
    scissor.offset = { 0, 0 };
    scissor.extent = vulkanContext->GetSwapChainExtent();

    VkPipelineViewportStateCreateInfo viewportState{};
    viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportState.viewportCount = 1;
    viewportState.pViewports = &viewport;
    viewportState.scissorCount = 1;
    viewportState.pScissors = &scissor;

    // Rasterizer
    VkPipelineRasterizationStateCreateInfo rasterizer{};
    rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer.depthClampEnable = VK_FALSE;
    rasterizer.rasterizerDiscardEnable = VK_FALSE;
    rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
    rasterizer.lineWidth = 1.0f;
    rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
    rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
    rasterizer.depthBiasEnable = VK_FALSE;

    // Multisampling
    VkPipelineMultisampleStateCreateInfo multisampling{};
    multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampling.sampleShadingEnable = VK_FALSE;
    multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

    // Color blending
    VkPipelineColorBlendAttachmentState colorBlendAttachment{};
    colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    colorBlendAttachment.blendEnable = VK_FALSE;

    VkPipelineColorBlendStateCreateInfo colorBlending{};
    colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlending.logicOpEnable = VK_FALSE;
    colorBlending.attachmentCount = 1;
    colorBlending.pAttachments = &colorBlendAttachment;

    // Pipeline layout
    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;

    if (vkCreatePipelineLayout(vulkanContext->GetDevice(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create pipeline layout!");
    }

    // Graphics pipeline
    VkGraphicsPipelineCreateInfo pipelineInfo{};
    pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineInfo.stageCount = 2;
    pipelineInfo.pStages = shaderStages;
    pipelineInfo.pVertexInputState = &vertexInputInfo;
    pipelineInfo.pInputAssemblyState = &inputAssembly;
    pipelineInfo.pViewportState = &viewportState;
    pipelineInfo.pRasterizationState = &rasterizer;
    pipelineInfo.pMultisampleState = &multisampling;
    pipelineInfo.pColorBlendState = &colorBlending;
    pipelineInfo.layout = pipelineLayout;
    pipelineInfo.renderPass = vulkanContext->GetRenderPass();
    pipelineInfo.subpass = 0;

    if (vkCreateGraphicsPipelines(vulkanContext->GetDevice(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create graphics pipeline!");
    }

    vkDestroyShaderModule(vulkanContext->GetDevice(), fragShaderModule, nullptr);
    vkDestroyShaderModule(vulkanContext->GetDevice(), vertShaderModule, nullptr);

    std::cout << "Graphics pipeline created successfully!" << std::endl;
}

void TriangleRenderer::CreateVertexBuffer()
{
    VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();

    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = bufferSize;
    bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(vulkanContext->GetDevice(), &bufferInfo, nullptr, &vertexBuffer) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create vertex buffer!");
    }

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(vulkanContext->GetDevice(), vertexBuffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = FindMemoryType(memRequirements.memoryTypeBits,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

    if (vkAllocateMemory(vulkanContext->GetDevice(), &allocInfo, nullptr, &vertexBufferMemory) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to allocate vertex buffer memory!");
    }

    vkBindBufferMemory(vulkanContext->GetDevice(), vertexBuffer, vertexBufferMemory, 0);

    // Copy vertex data
    void* data;
    vkMapMemory(vulkanContext->GetDevice(), vertexBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, vertices.data(), (size_t)bufferSize);
    vkUnmapMemory(vulkanContext->GetDevice(), vertexBufferMemory);
}

void TriangleRenderer::CreateCommandBuffers()
{
    commandBuffers.resize(MAX_FRAMES_IN_FLIGHT);

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = vulkanContext->GetCommandPool();
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = (uint32_t)commandBuffers.size();

    if (vkAllocateCommandBuffers(vulkanContext->GetDevice(), &allocInfo, commandBuffers.data()) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to allocate command buffers!");
    }
}

void TriangleRenderer::CreateSyncObjects()
{
    imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
    renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
    inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);

    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
    {
        if (vkCreateSemaphore(vulkanContext->GetDevice(), &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]) != VK_SUCCESS ||
            vkCreateSemaphore(vulkanContext->GetDevice(), &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]) != VK_SUCCESS ||
            vkCreateFence(vulkanContext->GetDevice(), &fenceInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create synchronization objects!");
        }
    }
}

void TriangleRenderer::RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex)
{
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to begin recording command buffer!");
    }

    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = vulkanContext->GetRenderPass();
    renderPassInfo.framebuffer = vulkanContext->GetSwapChainFramebuffers()[imageIndex];
    renderPassInfo.renderArea.offset = { 0, 0 };
    renderPassInfo.renderArea.extent = vulkanContext->GetSwapChainExtent();

    VkClearValue clearColor = { {{0.0f, 0.0f, 0.0f, 1.0f}} };
    renderPassInfo.clearValueCount = 1;
    renderPassInfo.pClearValues = &clearColor;

    vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);

    VkBuffer vertexBuffers[] = { vertexBuffer };
    VkDeviceSize offsets[] = { 0 };
    vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);

    vkCmdDraw(commandBuffer, static_cast<uint32_t>(vertices.size()), 1, 0, 0);

    vkCmdEndRenderPass(commandBuffer);

    if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to record command buffer!");
    }
}

void TriangleRenderer::DrawFrame()
{
    vkWaitForFences(vulkanContext->GetDevice(), 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);

    uint32_t imageIndex;
    VkResult result = vkAcquireNextImageKHR(vulkanContext->GetDevice(), vulkanContext->GetSwapChain(),
        UINT64_MAX, imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);

    if (result == VK_ERROR_OUT_OF_DATE_KHR)
    {
        // Handle window resize - for now just return
        return;
    }
    else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
    {
        throw std::runtime_error("Failed to acquire swap chain image!");
    }

    vkResetFences(vulkanContext->GetDevice(), 1, &inFlightFences[currentFrame]);

    vkResetCommandBuffer(commandBuffers[currentFrame], 0);
    RecordCommandBuffer(commandBuffers[currentFrame], imageIndex);

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = { imageAvailableSemaphores[currentFrame] };
    VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffers[currentFrame];

    VkSemaphore signalSemaphores[] = { renderFinishedSemaphores[currentFrame] };
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    if (vkQueueSubmit(vulkanContext->GetGraphicsQueue(), 1, &submitInfo, inFlightFences[currentFrame]) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to submit draw command buffer!");
    }

    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    VkSwapchainKHR swapChains[] = { vulkanContext->GetSwapChain() };
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;
    presentInfo.pImageIndices = &imageIndex;

    result = vkQueuePresentKHR(vulkanContext->GetPresentQueue(), &presentInfo);

    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR)
    {
        // Handle window resize
    }
    else if (result != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to present swap chain image!");
    }

    currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}

VkShaderModule TriangleRenderer::CreateShaderModule(const std::vector<char>& code)
{
    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = code.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

    VkShaderModule shaderModule;
    if (vkCreateShaderModule(vulkanContext->GetDevice(), &createInfo, nullptr, &shaderModule) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create shader module!");
    }

    return shaderModule;
}

uint32_t TriangleRenderer::FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties)
{
    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(vulkanContext->GetPhysicalDevice(), &memProperties);

    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
    {
        if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
        {
            return i;
        }
    }

    throw std::runtime_error("Failed to find suitable memory type!");
}
