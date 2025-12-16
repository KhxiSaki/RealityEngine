#pragma once

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <string>
#include <glm/glm.hpp>

class ImGuiLayer;
class ViewportRenderer;

class EditorUI
{
public:
    EditorUI();
    ~EditorUI();

    void Initialize(ImGuiLayer* imguiLayer, GLFWwindow* window);
    void Update(double deltaTime);
    void Render();
    
    void SetViewportRenderer(ViewportRenderer* renderer) { viewportRenderer = renderer; }

    bool IsViewportHovered() const { return viewportHovered; }
    bool IsViewportFocused() const { return viewportFocused; }
    glm::vec2 GetViewportSize() const { return viewportSize; }

private:
    void RenderMainMenuBar();
    void RenderDockSpace();
    void RenderViewport();
    void RenderStats(double deltaTime);

    ImGuiLayer* imguiLayer = nullptr;
    GLFWwindow* window = nullptr;
    ViewportRenderer* viewportRenderer = nullptr;
    
    bool viewportHovered = false;
    bool viewportFocused = false;
    glm::vec2 viewportSize = glm::vec2(0.0f, 0.0f);
    
    // Stats
    double fps = 0.0;
    double frameTime = 0.0;
};
