#pragma once

#include "Vector3.hpp"
#include <vector>

class ObjectFace {
public:
	ObjectFace();
	ObjectFace(Vector3* first, Vector3* second, Vector3* third, Vector3* fourth);
	ObjectFace(std::vector<Vector3*> objectPoints);
	std::vector<Vector3*> objectPoints;
};
