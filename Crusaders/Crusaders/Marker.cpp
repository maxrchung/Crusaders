#include "Marker.hpp"
#include "ObjectPoints.hpp"

Marker::Marker(Vector3 position, int time, bool onBeat) 
	: position(position), onBeat(onBeat), time(time), radius(20.0f) {
}

Marker::Marker() {}

void Marker::setObjectPoints(Simulation* simulation) {
	this->simulation = simulation;
	Vector3 left = position - Vector3(-radius, 0, 0);
	Vector3 right = position + Vector3(radius, 0, 0);
	Face face = Face({ left, right });
	objectPoints = new ObjectPoints(simulation, { face });
}