#pragma once

#include "BeatmapObject.hpp"

class Note : public BeatmapObject
{
public:
	Note(int startTime);
	void Update();
};