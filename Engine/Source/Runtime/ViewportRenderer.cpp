#include "ViewportRenderer.h"
#include "VulkanContext.h"
#include "ImGuiLayer.h"
#include <imgui.h>
#include <imgui_impl_vulkan.h>
#include <stdexcept>
#include <iostream>
#include <algorithm>

ViewportRenderer::ViewportRenderer(VulkanContext* context)
    : vulkanContext(context)
{
}

ViewportRenderer::~ViewportRenderer()
{
    Cleanup();
}

bool ViewportRenderer::Initialize(uint32_t w, uint32_t h)
{
    width = w;
    height = h;

    if (width == 0 || height == 0)
    {
        width = 1280;
        height = 720;
    }

    try
    {
        CreateRenderPass();
        CreateRenderTarget();
        CreateFramebuffer();
        CreateImGuiDescriptor();
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Viewport renderer initialization failed: " << e.what() << std::endl;
        return false;
    }
}

void ViewportRenderer::Cleanup()
{
    VkDevice device = vulkanContext->GetDevice();

    if (device != VK_NULL_HANDLE)
    {
        vkDeviceWaitIdle(device);

        // Free ImGui descriptor set BEFORE destroying the sampler/image view it references
        if (imguiTextureID != VK_NULL_HANDLE)
        {
            ImGui_ImplVulkan_RemoveTexture(imguiTextureID);
            imguiTextureID = VK_NULL_HANDLE;
        }

        if (framebuffer != VK_NULL_HANDLE)
        {
            vkDestroyFramebuffer(device, framebuffer, nullptr);
            framebuffer = VK_NULL_HANDLE;
        }

        // Destroy sampler BEFORE cleaning up
        if (colorSampler != VK_NULL_HANDLE)
        {
            vkDestroySampler(device, colorSampler, nullptr);
            colorSampler = VK_NULL_HANDLE;
        }

        if (colorImageView != VK_NULL_HANDLE)
        {
            vkDestroyImageView(device, colorImageView, nullptr);
            colorImageView = VK_NULL_HANDLE;
        }

        if (colorImage != VK_NULL_HANDLE)
        {
            vkDestroyImage(device, colorImage, nullptr);
            colorImage = VK_NULL_HANDLE;
        }

        if (colorImageMemory != VK_NULL_HANDLE)
        {
            vkFreeMemory(device, colorImageMemory, nullptr);
            colorImageMemory = VK_NULL_HANDLE;
        }

        if (renderPass != VK_NULL_HANDLE)
        {
            vkDestroyRenderPass(device, renderPass, nullptr);
            renderPass = VK_NULL_HANDLE;
        }
    }
}

void ViewportRenderer::Resize(uint32_t w, uint32_t h)
{
    if (w == 0 || h == 0 || (w == width && h == height))
        return;

    width = w;
    height = h;

    // Cleanup old resources
    VkDevice device = vulkanContext->GetDevice();
    vkDeviceWaitIdle(device);

    // Free ImGui descriptor BEFORE destroying resources
    if (imguiTextureID != VK_NULL_HANDLE)
    {
        ImGui_ImplVulkan_RemoveTexture(imguiTextureID);
        imguiTextureID = VK_NULL_HANDLE;
    }

    if (framebuffer != VK_NULL_HANDLE)
    {
        vkDestroyFramebuffer(device, framebuffer, nullptr);
        framebuffer = VK_NULL_HANDLE;
    }

    if (colorSampler != VK_NULL_HANDLE)
    {
        vkDestroySampler(device, colorSampler, nullptr);
        colorSampler = VK_NULL_HANDLE;
    }

    if (colorImageView != VK_NULL_HANDLE)
    {
        vkDestroyImageView(device, colorImageView, nullptr);
        colorImageView = VK_NULL_HANDLE;
    }

    if (colorImage != VK_NULL_HANDLE)
    {
        vkDestroyImage(device, colorImage, nullptr);
        colorImage = VK_NULL_HANDLE;
    }

    if (colorImageMemory != VK_NULL_HANDLE)
    {
        vkFreeMemory(device, colorImageMemory, nullptr);
        colorImageMemory = VK_NULL_HANDLE;
    }

    // Recreate with new size
    CreateRenderTarget();
    CreateFramebuffer();
    CreateImGuiDescriptor();
}

void ViewportRenderer::CreateRenderPass()
{
    VkAttachmentDescription colorAttachment{};
    colorAttachment.format = VK_FORMAT_R8G8B8A8_UNORM;
    colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
    colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    colorAttachment.finalLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

    VkAttachmentReference colorAttachmentRef{};
    colorAttachmentRef.attachment = 0;
    colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpass{};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &colorAttachmentRef;

    VkSubpassDependency dependency{};
    dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    dependency.dstSubpass = 0;
    dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.srcAccessMask = 0;
    dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

    VkRenderPassCreateInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.attachmentCount = 1;
    renderPassInfo.pAttachments = &colorAttachment;
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pSubpasses = &subpass;
    renderPassInfo.dependencyCount = 1;
    renderPassInfo.pDependencies = &dependency;

    if (vkCreateRenderPass(vulkanContext->GetDevice(), &renderPassInfo, nullptr, &renderPass) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create viewport render pass!");
    }
}

void ViewportRenderer::CreateRenderTarget()
{
    VkDevice device = vulkanContext->GetDevice();

    // Create image
    VkImageCreateInfo imageInfo{};
    imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    imageInfo.imageType = VK_IMAGE_TYPE_2D;
    imageInfo.extent.width = width;
    imageInfo.extent.height = height;
    imageInfo.extent.depth = 1;
    imageInfo.mipLevels = 1;
    imageInfo.arrayLayers = 1;
    imageInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
    imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
    imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    imageInfo.usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
    imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
    imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateImage(device, &imageInfo, nullptr, &colorImage) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create viewport image!");
    }

    // Allocate memory
    VkMemoryRequirements memRequirements;
    vkGetImageMemoryRequirements(device, colorImage, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = FindMemoryType(memRequirements.memoryTypeBits,
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

    if (vkAllocateMemory(device, &allocInfo, nullptr, &colorImageMemory) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to allocate viewport image memory!");
    }

    vkBindImageMemory(device, colorImage, colorImageMemory, 0);

    // Create image view
    VkImageViewCreateInfo viewInfo{};
    viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    viewInfo.image = colorImage;
    viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    viewInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
    viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    viewInfo.subresourceRange.baseMipLevel = 0;
    viewInfo.subresourceRange.levelCount = 1;
    viewInfo.subresourceRange.baseArrayLayer = 0;
    viewInfo.subresourceRange.layerCount = 1;

    if (vkCreateImageView(device, &viewInfo, nullptr, &colorImageView) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create viewport image view!");
    }

    // Create sampler
    VkSamplerCreateInfo samplerInfo{};
    samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    samplerInfo.magFilter = VK_FILTER_LINEAR;
    samplerInfo.minFilter = VK_FILTER_LINEAR;
    samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    samplerInfo.anisotropyEnable = VK_FALSE;
    samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
    samplerInfo.unnormalizedCoordinates = VK_FALSE;
    samplerInfo.compareEnable = VK_FALSE;
    samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
    samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;

    if (vkCreateSampler(device, &samplerInfo, nullptr, &colorSampler) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create viewport sampler!");
    }

    // Transition image layout
    TransitionImageLayout(colorImage, VK_FORMAT_R8G8B8A8_UNORM,
        VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
}

void ViewportRenderer::CreateFramebuffer()
{
    VkImageView attachments[] = { colorImageView };

    VkFramebufferCreateInfo framebufferInfo{};
    framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebufferInfo.renderPass = renderPass;
    framebufferInfo.attachmentCount = 1;
    framebufferInfo.pAttachments = attachments;
    framebufferInfo.width = width;
    framebufferInfo.height = height;
    framebufferInfo.layers = 1;

    if (vkCreateFramebuffer(vulkanContext->GetDevice(), &framebufferInfo, nullptr, &framebuffer) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create viewport framebuffer!");
    }
}

void ViewportRenderer::CreateImGuiDescriptor()
{
    imguiTextureID = ImGui_ImplVulkan_AddTexture(colorSampler, colorImageView,
        VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
}

void ViewportRenderer::BeginRenderPass(VkCommandBuffer commandBuffer)
{
    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = renderPass;
    renderPassInfo.framebuffer = framebuffer;
    renderPassInfo.renderArea.offset = { 0, 0 };
    renderPassInfo.renderArea.extent = { width, height };

    VkClearValue clearColor = { {{0.1f, 0.1f, 0.1f, 1.0f}} };
    renderPassInfo.clearValueCount = 1;
    renderPassInfo.pClearValues = &clearColor;

    vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

    // Set viewport and scissor
    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = static_cast<float>(width);
    viewport.height = static_cast<float>(height);
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

    VkRect2D scissor{};
    scissor.offset = { 0, 0 };
    scissor.extent = { width, height };
    vkCmdSetScissor(commandBuffer, 0, 1, &scissor);
}

void ViewportRenderer::EndRenderPass(VkCommandBuffer commandBuffer)
{
    vkCmdEndRenderPass(commandBuffer);
}

uint32_t ViewportRenderer::FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties)
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

void ViewportRenderer::TransitionImageLayout(VkImage image, VkFormat format,
    VkImageLayout oldLayout, VkImageLayout newLayout)
{
    VkCommandBuffer commandBuffer;

    // Allocate temporary command buffer
    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = vulkanContext->GetCommandPool();
    allocInfo.commandBufferCount = 1;

    vkAllocateCommandBuffers(vulkanContext->GetDevice(), &allocInfo, &commandBuffer);

    // Begin recording
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    vkBeginCommandBuffer(commandBuffer, &beginInfo);

    // Image memory barrier
    VkImageMemoryBarrier barrier{};
    barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    barrier.oldLayout = oldLayout;
    barrier.newLayout = newLayout;
    barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.image = image;
    barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    barrier.subresourceRange.baseMipLevel = 0;
    barrier.subresourceRange.levelCount = 1;
    barrier.subresourceRange.baseArrayLayer = 0;
    barrier.subresourceRange.layerCount = 1;

    VkPipelineStageFlags sourceStage;
    VkPipelineStageFlags destinationStage;

    if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL)
    {
        barrier.srcAccessMask = 0;
        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
        sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    }
    else
    {
        throw std::runtime_error("Unsupported layout transition!");
    }

    vkCmdPipelineBarrier(commandBuffer, sourceStage, destinationStage, 0, 0, nullptr, 0, nullptr, 1, &barrier);

    // End and submit
    vkEndCommandBuffer(commandBuffer);

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;

    vkQueueSubmit(vulkanContext->GetGraphicsQueue(), 1, &submitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(vulkanContext->GetGraphicsQueue());

    vkFreeCommandBuffers(vulkanContext->GetDevice(), vulkanContext->GetCommandPool(), 1, &commandBuffer);
}