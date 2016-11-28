#pragma once

class Simulation;

#include "BeatmapObject.hpp"

class Note : public BeatmapObject
{
public:
	Note(Simulation* simulation, int startTime);
	void Update();
};