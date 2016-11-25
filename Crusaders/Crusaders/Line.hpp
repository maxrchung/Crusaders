#pragma once

#include "Vector3.hpp"

class Line {
public:
	Line(Vector3 start, Vector3 end);
	Vector3 start, end;
};
