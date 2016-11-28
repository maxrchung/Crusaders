#pragma once
#include "Simulation.hpp"
class BeatmapObject 
{
public:
	BeatmapObject();
	virtual void Update();
	Simulation* simulation;
	int startTime;
	bool finished;

private:



};