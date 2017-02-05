#pragma once

#include "BeatmapObject.hpp"
#include "Vector2.hpp"
#include <tuple>
#include <vector>

class Slider : public BeatmapObject
{
public:
	Slider(int start, int repeat, std::vector<Vector2> transitions);
private:
	int repeat;
	std::vector<Vector2> transitions;
};