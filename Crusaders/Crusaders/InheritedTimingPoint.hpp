#pragma once

class InheritedTimingPoint {
public:
	InheritedTimingPoint(int offset, float mspb);
	int offset;
	float mspb;
	float sliderMultiplier;
};
