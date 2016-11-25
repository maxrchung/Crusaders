#pragma once

#include "ObjectType.hpp"
#include "Time.hpp"
#include "Vector3.hpp"

class SpawnInfo {
public:
	SpawnInfo(Time spawn, ObjectType type, Vector3 location);
	Time spawn;
	ObjectType type; // probably should change this to type
	Vector3 location;
};
