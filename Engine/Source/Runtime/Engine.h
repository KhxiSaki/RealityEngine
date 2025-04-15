#pragma once

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
};

