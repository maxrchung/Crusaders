#pragma once
#include "BeatmapObject.hpp"

class Spinner : public BeatmapObject
{
	public:
		Spinner(int startTime, int endTime, Simulation* sim);
		void Update();

	private:
		int endTime;

};