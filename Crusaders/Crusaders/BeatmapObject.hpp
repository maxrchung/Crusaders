#pragma once

#include "Simulation.hpp"

class BeatmapObject 
{
public:
	BeatmapObject(Simulation* simulation, int startTime, bool finished);
	virtual void Update() = 0;
	Simulation* simulation;
	int startTime;
	bool finished;
};