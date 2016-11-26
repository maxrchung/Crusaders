#include "Spinner.hpp"
#include <iostream>

Spinner::Spinner(int startTime, int endTime, Simulation* sim)
	:BeatmapObject{startTime, sim}, endTime{endTime}
{
	//std::cout << "Spinner Initialized" << std::endl;
}