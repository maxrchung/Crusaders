#include "Camera.hpp"
#include "Note.hpp"
#include "ObjectPoints.hpp"
#include <iostream>

Note::Note(int startTime) 
	: BeatmapObject(startTime, false) {
	//std::cout << "Note Initialized" << std::endl;
}

void Note::Update()
{
	////is updating properly
	//if (simulation->time > startTime && !finished)
	//{
	//	//simulation->bullets.push_back(new Bullet(simulation, simulation->character->gun->center, simulation->character->camera->direction));
	//	finished = true;
	//}
}