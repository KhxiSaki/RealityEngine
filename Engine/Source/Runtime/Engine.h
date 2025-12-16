#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

// Forward declarations
class VulkanContext;
class TriangleRenderer;
class ImGuiLayer;
class EditorUI;

class Engine
{
public:
	Engine();
	virtual ~Engine();

	void PreInitialization();
	void Initialization();
	void Run(double DeltaTime);
	void PreInitializeInput();
	void InitializeInput();
	void PostInitializeInput();
	void PreUpdate();
	void Update(double DeltaTime);
	void PostUpdate();
	void PreRender();
	void Render();
	void PostRender();

	bool ShouldClose() const;

private:
	GLFWwindow* window = nullptr;
	VulkanContext* vulkanContext = nullptr;
	TriangleRenderer* triangleRenderer = nullptr;
	ImGuiLayer* imguiLayer = nullptr;
	EditorUI* editorUI = nullptr;
	bool bInitialized = false;
};
