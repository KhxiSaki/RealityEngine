#include "Applications.h"
#include <chrono>
#include <thread>
#include "Engine.h"

Applications::Applications()
	:lastFrame(0.0)
{
}

Applications::~Applications()
{
}

void Applications::Run()
{
	// Delta time calculation
	auto Time = []() {
		return static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch()).count()) / 1000.0;
	};

	Engine engine;
	
	// Initialize engine once before loop
	engine.PreInitialization();
	engine.Initialization();

	while (bIsApplicationRunning && !engine.ShouldClose())
	{
		double currentTime = Time();
		double deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;
		
		if (deltaTime > 0.0) 
		{
			engine.Run(deltaTime);
		}

		// Cap the frame rate to 60 FPS
		if (deltaTime < (1000.0 / 60.0) / 1000.0) 
		{
			std::this_thread::sleep_for(std::chrono::microseconds(
				static_cast<long long>((1000.0 / 60.0 - deltaTime * 1000.0) * 1000.0)));
		}
	}
}
