#pragma once

#include "Vector3.hpp"
#include <vector>

// Please be mindful to initialize faces in clockwise direction when they are facing you
class Face {
public:
	Face(std::vector<Vector3> points);
	Face(Vector3 first, Vector3 second, Vector3 third, Vector3 fourth);
	std::vector<Vector3> points;
};