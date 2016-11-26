#pragma once
#include "BeatmapObject.hpp"
#include <tuple>
#include <vector>
#include <iostream>

class Slider : public BeatmapObject
{
public:
	Slider(int x, int y, int time, std::vector<std::tuple<int,int>> transpoints, Simulation* sim);

private:
	int posX;
	int posY;
	std::vector<std::tuple<int, int>> transitionPoints;

};