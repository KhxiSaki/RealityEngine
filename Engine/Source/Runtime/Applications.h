#pragma once
class Applications
{
public:
	Applications();
	virtual ~Applications();

	void Run();

protected:
	bool bIsApplicationRunning = true;
	double lastFrame;
};

