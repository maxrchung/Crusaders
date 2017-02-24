#pragma once

class InheritedTimingPoint;

#include <vector>

class TimingPoint {
public:
	TimingPoint(int offset, float mspb, int meter);
	int offset;
	float mspb;
	int meter;
	std::vector<InheritedTimingPoint*> inheritedTimingPoints;
};