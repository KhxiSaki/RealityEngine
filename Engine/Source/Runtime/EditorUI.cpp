#include "EditorUI.h"
#include "ImGuiLayer.h"
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

    // This is where we would render the scene to a texture and display it
    // For now, we'll just show a placeholder
    ImGui::Text("Viewport: %.0fx%.0f", viewportPanelSize.x, viewportPanelSize.y);
    ImGui::Text("Scene rendering here");

    // Draw colored rectangle to indicate viewport area
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImVec2 canvas_pos = ImGui::GetCursorScreenPos();
    ImVec2 canvas_size = ImGui::GetContentRegionAvail();
    
    if (canvas_size.x > 0 && canvas_size.y > 0)
    {
        draw_list->AddRectFilled(
            canvas_pos,
            ImVec2(canvas_pos.x + canvas_size.x, canvas_pos.y + canvas_size.y),
            IM_COL32(20, 20, 20, 255)
        );

        // Draw center crosshair
        float centerX = canvas_pos.x + canvas_size.x * 0.5f;
        float centerY = canvas_pos.y + canvas_size.y * 0.5f;
        
        draw_list->AddLine(
            ImVec2(centerX - 10, centerY),
            ImVec2(centerX + 10, centerY),
            IM_COL32(100, 100, 100, 255),
            1.0f
        );
        
        draw_list->AddLine(
            ImVec2(centerX, centerY - 10),
            ImVec2(centerX, centerY + 10),
            IM_COL32(100, 100, 100, 255),
            1.0f
        );
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
    ImGui::Text("  Hovered: %s", viewportHovered ? "Yes" : "No");
    ImGui::Text("  Focused: %s", viewportFocused ? "Yes" : "No");

    ImGui::End();
}
