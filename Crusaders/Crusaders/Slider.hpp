#pragma once

#include "BeatmapObject.hpp"
#include "Bezier.hpp"
#include "Vector2.hpp"
#include <tuple>
#include <vector>

class Slider : public BeatmapObject {
public:
	Slider(int start, std::vector<Vector2> transitions, int repeat, float pixelLength);
	int end;
	int repeat;
	float pixelLength;
	std::vector<Vector2> transitions;
	Bezier bezier;
};