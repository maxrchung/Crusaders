#include "Spinner.hpp"
#include <iostream>

Spinner::Spinner(int startTime, int endTime)
	: BeatmapObject(startTime, false), endTime(endTime)
{
	//std::cout << "Spinner Initialized" << std::endl;
}

void Spinner::Update()
{
}