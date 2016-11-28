#pragma once
#include "BeatmapObject.hpp"
#include <tuple>
#include <vector>
#include <iostream>

class Slider : public BeatmapObject
{
public:
	Slider(Simulation* simulation, int x, int y, int startTime, std::vector<std::tuple<int, int>> transitionPoints);
	void Update() override;
private:
	int x;
	int y;
	std::vector<std::tuple<int, int>> transitionPoints;

};