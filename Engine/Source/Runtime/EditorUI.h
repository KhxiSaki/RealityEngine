#pragma once

#include <GLFW/glfw3.h>
#include <string>

class ImGuiLayer;

class EditorUI
{
public:
    EditorUI();
    ~EditorUI();

    void Initialize(ImGuiLayer* imguiLayer, GLFWwindow* window);
    void Update(double deltaTime);
    void Render();

    bool IsViewportHovered() const { return viewportHovered; }
    bool IsViewportFocused() const { return viewportFocused; }

private:
    void RenderMainMenuBar();
    void RenderDockSpace();
    void RenderViewport();
    void RenderStats(double deltaTime);

    ImGuiLayer* imguiLayer = nullptr;
    GLFWwindow* window = nullptr;
    
    bool viewportHovered = false;
    bool viewportFocused = false;
    
    // Stats
    double fps = 0.0;
    double frameTime = 0.0;
};
