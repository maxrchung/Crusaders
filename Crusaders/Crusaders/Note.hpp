#pragma once
#include "BeatmapObject.hpp"
#include "Simulation.hpp"
class Note : public BeatmapObject
{
public:
	Note(int time, Simulation* sim);
	void shoot();
	void Update() override;
private:

};