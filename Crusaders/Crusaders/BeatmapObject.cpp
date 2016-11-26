#include "BeatmapObject.hpp"
#include "Simulation.hpp"

BeatmapObject::BeatmapObject(int time, Simulation* sim)
	: startTime{time}, simulation{sim}
{
}

void BeatmapObject::Update()
{
}

