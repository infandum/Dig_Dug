#include "MiniginPCH.h"
#include "FPSComponent.h"
#include <chrono>


FPSComponent::FPSComponent()
{
}

void FPSComponent::Initialize()
{
	
}

void FPSComponent::Draw()
{
	
}

void FPSComponent::Update()
{
	auto beginFrame = std::chrono::high_resolution_clock::now();
	auto endFrame = std::chrono::high_resolution_clock::now();

	//float deltaTime = std::chrono::duration<float>(endFrame - beginFrame).count();
	//unsigned int frames = 0;

	//if (clockToMilliseconds(deltaTime) > 1000.0) { //every second
	//	frameRate = (double)frames*0.5 + frameRate * 0.5; //more stable
	//	frames = 0;
	//	deltaTime -= CLOCKS_PER_SEC;
	//	averageFrameTimeMilliseconds = 1000.0 / (frameRate == 0 ? 0.001 : frameRate);

	//	if (vsync)
	//		std::cout << "FrameTime was:" << averageFrameTimeMilliseconds << std::endl;
	//	else
	//		std::cout << "CPU time was:" << averageFrameTimeMilliseconds << std::endl;
	//}
}
