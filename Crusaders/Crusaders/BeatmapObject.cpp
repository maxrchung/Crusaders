#include "BeatmapObject.hpp"
#include "Simulation.hpp"

BeatmapObject::BeatmapObject(Simulation* simulation, int startTime, bool finished)
	: simulation(simulation), startTime(startTime), finished(finished)
{
}