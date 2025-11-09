#include "Runtime/Engine.h"

Engine::Engine()
{

}

Engine::~Engine()
{

}

void Engine::PreInitialization()
{

}

void Engine::Initialization()
{

}

void Engine::Run(double DeltaTime)
{
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

}

void Engine::Render()
{

}

void Engine::PostRender()
{

}
