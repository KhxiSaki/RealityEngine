#include "Runtime/Engine.h"
#include "VulkanContext.h"
#include "TriangleRenderer.h"
#include "ViewportRenderer.h"
#include <iostream>
#include "EditorUI.h"
#include "ImGuiLayer.h"

Engine::Engine()
{
}

Engine::~Engine()
{
	if (editorUI)
	{
		delete editorUI;
		editorUI = nullptr;
	}

	if (viewportRenderer)
	{
		delete viewportRenderer;
		viewportRenderer = nullptr;
	}

	if (imguiLayer)
	{
		delete imguiLayer;
		imguiLayer = nullptr;
	}

	if (triangleRenderer)
	{
		delete triangleRenderer;
		triangleRenderer = nullptr;
	}

	if (vulkanContext)
	{
		delete vulkanContext;
		vulkanContext = nullptr;
	}

	if (window)
	{
		glfwDestroyWindow(window);
		window = nullptr;
	}

	glfwTerminate();
}

void Engine::PreInitialization()
{
	if (bInitialized)
		return;

	// Initialize GLFW
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW!" << std::endl;
		return;
	}

	// Tell GLFW not to create an OpenGL context
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	// Get the primary monitor
	GLFWmonitor* primary_monitor = glfwGetPrimaryMonitor();
	if (!primary_monitor)
	{
		return;
	}

	// Get the current video mode (contains width, height, refresh rate, etc.)
	const GLFWvidmode* mode = glfwGetVideoMode(primary_monitor);
	if (!mode)
	{
		return;
	}

	// Create window
	window = glfwCreateWindow(mode->width,
		mode->height,
		"RealityEngine",
		primary_monitor,
		nullptr);
	if (!window)
	{
		std::cerr << "Failed to create GLFW window!" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);
	std::cout << "Window created successfully!" << std::endl;
}

void Engine::Initialization()
{
	if (bInitialized)
		return;

	// Initialize Vulkan
	vulkanContext = new VulkanContext();
	if (!vulkanContext->Initialize(window))
	{
		std::cerr << "Failed to initialize Vulkan!" << std::endl;
		return;
	}

	// Initialize ImGui FIRST (before viewport renderer, since it needs ImGui's descriptor pool)
	imguiLayer = new ImGuiLayer();
	if (!imguiLayer->Initialize(window, vulkanContext))
	{
		std::cerr << "Failed to initialize ImGui!" << std::endl;
		return;
	}

	// Initialize viewport renderer (for rendering scene to texture)
	viewportRenderer = new ViewportRenderer(vulkanContext);
	if (!viewportRenderer->Initialize(1280, 720))
	{
		std::cerr << "Failed to initialize viewport renderer!" << std::endl;
		return;
	}

	// Initialize triangle renderer
	triangleRenderer = new TriangleRenderer(vulkanContext);
	if (!triangleRenderer->Initialize())
	{
		std::cerr << "Failed to initialize triangle renderer!" << std::endl;
		return;
	}

	// Connect components - IMPORTANT: This must happen AFTER both are initialized
	triangleRenderer->SetImGuiLayer(imguiLayer);
	triangleRenderer->SetViewportRenderer(viewportRenderer);  // This now creates the viewport pipeline

	// Initialize Editor UI
	editorUI = new EditorUI();
	editorUI->Initialize(imguiLayer, window);
	editorUI->SetViewportRenderer(viewportRenderer);

	bInitialized = true;
	std::cout << "Engine initialized successfully!" << std::endl;
}

void Engine::Run(double DeltaTime)
{
	if (!bInitialized)
		return;

	PreInitializeInput();
	PreUpdate();
	PreRender();

	InitializeInput();
	Update(DeltaTime);
	Render();

	PostInitializeInput();
	PostUpdate();
	PostRender();
}

void Engine::PreInitializeInput()
{
	glfwPollEvents();
}

void Engine::InitializeInput()
{
}

void Engine::PostInitializeInput()
{
}

void Engine::PreUpdate()
{
}

void Engine::Update(double DeltaTime)
{
	if (editorUI)
	{
		editorUI->Update(DeltaTime);
	}
}

void Engine::PostUpdate()
{
}

void Engine::PreRender()
{
}

void Engine::Render()
{
	if (triangleRenderer && imguiLayer && editorUI)
	{
		// Start ImGui frame
		imguiLayer->BeginFrame();

		// Render editor UI (includes viewport)
		editorUI->Render();

		// End ImGui frame
		imguiLayer->EndFrame();

		// Draw the frame (renders scene to viewport, then ImGui to swap chain)
		triangleRenderer->DrawFrame();
	}
}

void Engine::PostRender()
{
	glfwSwapBuffers(window);
}

bool Engine::ShouldClose() const
{
	return window ? glfwWindowShouldClose(window) : true;
}