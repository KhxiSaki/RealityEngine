#include "EditorUI.h"
#include "ImGuiLayer.h"
#include "ViewportRenderer.h"
#include <imgui.h>
#include <iostream>

EditorUI::EditorUI()
{
}

EditorUI::~EditorUI()
{
}

void EditorUI::Initialize(ImGuiLayer* layer, GLFWwindow* win)
{
    imguiLayer = layer;
    window = win;
    std::cout << "Editor UI initialized!" << std::endl;
}

void EditorUI::Update(double deltaTime)
{
    frameTime = deltaTime * 1000.0; // Convert to milliseconds
    fps = deltaTime > 0.0 ? 1.0 / deltaTime : 0.0;
}

void EditorUI::Render()
{
    RenderDockSpace();
    RenderMainMenuBar();
    RenderViewport();
    RenderStats(frameTime);
}

void EditorUI::RenderMainMenuBar()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New Scene", "Ctrl+N")) {}
            if (ImGui::MenuItem("Open Scene", "Ctrl+O")) {}
            if (ImGui::MenuItem("Save Scene", "Ctrl+S")) {}
            ImGui::Separator();
            if (ImGui::MenuItem("Exit", "Alt+F4"))
            {
                glfwSetWindowShouldClose(window, GLFW_TRUE);
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", "Ctrl+Z")) {}
            if (ImGui::MenuItem("Redo", "Ctrl+Y")) {}
            ImGui::Separator();
            if (ImGui::MenuItem("Preferences")) {}
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("View"))
        {
            if (ImGui::MenuItem("Reset Layout")) {}
            ImGui::Separator();
            if (ImGui::MenuItem("Statistics")) {}
            if (ImGui::MenuItem("Console")) {}
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Help"))
        {
            if (ImGui::MenuItem("Documentation")) {}
            if (ImGui::MenuItem("About RealityEngine")) {}
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}

void EditorUI::RenderDockSpace()
{
    static bool opt_fullscreen = true;
    static bool opt_padding = false;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }

    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    if (!opt_padding)
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

    ImGui::Begin("DockSpace", nullptr, window_flags);

    if (!opt_padding)
        ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // Submit the DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    ImGui::End();
}

void EditorUI::RenderViewport()
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::Begin("Viewport");

    viewportHovered = ImGui::IsWindowHovered();
    viewportFocused = ImGui::IsWindowFocused();

    ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
    viewportSize = glm::vec2(viewportPanelSize.x, viewportPanelSize.y);

    // Handle viewport resize
    if (viewportRenderer && viewportSize.x > 0 && viewportSize.y > 0)
    {
        uint32_t width = static_cast<uint32_t>(viewportSize.x);
        uint32_t height = static_cast<uint32_t>(viewportSize.y);
        
        if (width != viewportRenderer->GetWidth() || height != viewportRenderer->GetHeight())
        {
            viewportRenderer->Resize(width, height);
        }
        
        // Display the rendered texture
        VkDescriptorSet textureID = viewportRenderer->GetImGuiTextureID();
        if (textureID)
        {
            ImGui::Image(textureID, viewportPanelSize);
        }
    }
    else
    {
        // Fallback: show placeholder if no viewport renderer
        ImGui::Text("Viewport: %.0fx%.0f", viewportSize.x, viewportSize.y);
        ImGui::Text("Waiting for viewport renderer...");
    }

    ImGui::End();
    ImGui::PopStyleVar();
}

void EditorUI::RenderStats(double deltaTime)
{
    ImGui::Begin("Statistics");

    ImGui::Text("RealityEngine Editor");
    ImGui::Separator();
    
    ImGui::Text("Performance:");
    ImGui::Text("  FPS: %.1f", fps);
    ImGui::Text("  Frame Time: %.3f ms", frameTime);
    
    ImGui::Separator();
    ImGui::Text("Renderer:");
    ImGui::Text("  API: Vulkan 1.3");
    ImGui::Text("  Triangles: 1");
    
    ImGui::Separator();
    ImGui::Text("Viewport:");
    ImGui::Text("  Size: %.0fx%.0f", viewportSize.x, viewportSize.y);
    ImGui::Text("  Hovered: %s", viewportHovered ? "Yes" : "No");
    ImGui::Text("  Focused: %s", viewportFocused ? "Yes" : "No");

    ImGui::End();
}
