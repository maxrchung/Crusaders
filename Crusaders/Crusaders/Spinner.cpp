#include "Spinner.hpp"
#include <iostream>

Spinner::Spinner(Simulation* sim, int startTime, int endTime)
	: BeatmapObject(sim, startTime, false), endTime(endTime)
{
	//std::cout << "Spinner Initialized" << std::endl;
}

void Spinner::Update()
{
}