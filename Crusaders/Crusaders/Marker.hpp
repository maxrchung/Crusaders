#pragma once

class ObjectPoints;
class Simulation;

#include "Vector3.hpp"

class Marker {
public:
	Marker();
	Marker(Vector3 position, int time, bool onBeat);
	void setObjectPoints(Simulation* simulation);

	float radius;
	int time;
	Vector3 position;
	// For visual purposes, denotes whether the marker is on beat or off beat
	bool onBeat;
	ObjectPoints* objectPoints;
	Simulation* simulation;
};
