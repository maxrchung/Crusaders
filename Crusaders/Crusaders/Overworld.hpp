#pragma once

class ObjectPoints;
class Simulation;

class Overworld {
public:
	Overworld(Simulation* simulation);

	Simulation* simulation;
	ObjectPoints* objectPoints;
	float scale = 100.0f;
};