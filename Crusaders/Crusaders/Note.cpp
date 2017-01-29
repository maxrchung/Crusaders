#include "Bullet.hpp"
#include "Camera.hpp"
#include "Note.hpp"
#include "ObjectPoints.hpp"
#include "Simulation.hpp"
#include <iostream>


Note::Note(Simulation* simulation, int startTime) 
	: BeatmapObject(simulation, startTime, false) {
	//std::cout << "Note Initialized" << std::endl;
}

void Note::Update()
{
	//is updating properly
	if (simulation->time > startTime && !finished)
	{
		//simulation->bullets.push_back(new Bullet(simulation, simulation->character->gun->center, simulation->character->camera->direction));
		finished = true;
	}
}