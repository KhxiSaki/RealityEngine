#include "Runtime/Engine.h"
#include "VulkanContext.h"
#include "TriangleRenderer.h"
#include <iostream>

Engine::Engine()
{
}

Engine::~Engine()
{
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

	// Initialize triangle renderer
	triangleRenderer = new TriangleRenderer(vulkanContext);
	if (!triangleRenderer->Initialize())
	{
		std::cerr << "Failed to initialize triangle renderer!" << std::endl;
		return;
	}

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
}

void Engine::PostUpdate()
{
}

void Engine::PreRender()
{
	glfwSwapBuffers(window);
}

void Engine::Render()
{
	if (triangleRenderer)
	{
		triangleRenderer->DrawFrame();
	}
}

void Engine::PostRender()
{
}

bool Engine::ShouldClose() const
{
	return window ? glfwWindowShouldClose(window) : true;
}
