#pragma once

#include "BeatmapObject.hpp"

class Spinner : public BeatmapObject
{
public:
	Spinner(int start, int end);
	int end;
};