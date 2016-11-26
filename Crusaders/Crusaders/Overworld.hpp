#pragma once

#include "Face.hpp"
#include "ObjectPoints.hpp"

class ObjectPoints;

class Overworld {
public:
	Overworld(Simulation* simulation);

	Simulation* simulation;
	ObjectPoints* objectPoints;
	float scale = 100.0f;
};