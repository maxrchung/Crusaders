#include "Spinner.hpp"
#include <iostream>

Spinner::Spinner(int startTime, int endTime, Simulation* sim)
{
	this->startTime = startTime;
	this->endTime = endTime;
	simulation = sim;
	finished = false;
	//std::cout << "Spinner Initialized" << std::endl;
}

void Spinner::Update()
{
}