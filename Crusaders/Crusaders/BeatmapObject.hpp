#pragma once
#include "Simulation.hpp"
class BeatmapObject 
{
public:
	BeatmapObject(int time, Simulation* sim);
	virtual void Update();

private:
	int startTime;
	Simulation* simulation;

};