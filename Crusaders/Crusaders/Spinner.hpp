#pragma once
#include "BeatmapObject.hpp"

class Spinner : public BeatmapObject
{
	public:
		Spinner(Simulation* sim, int startTime, int endTime);
		void Update();

	private:
		int endTime;

};