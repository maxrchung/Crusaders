#pragma once

#include "Vector3.hpp"

class ObjectLine {
public:
	ObjectLine(Vector3* start, Vector3* end);
	Vector3* start;
	Vector3* end;
};