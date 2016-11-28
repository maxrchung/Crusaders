#include "Note.hpp"
#include "BeatmapObject.hpp"
#include <iostream>
#include "Simulation.hpp"

Note::Note(int time, Simulation* sim)
{
	simulation = sim;
	startTime = time;
	finished = false;
	//std::cout << "Note Initialized" << std::endl;
}
void Note::shoot()
{
	simulation->character->shoot();
}

void Note::Update()
{
	//is updating properly
	if (simulation->time > startTime && !finished)
	{
		shoot();
		std::cout << "bullet update shot" << std::endl;
		finished = true;
	}
}