#pragma once

class TimingPoint {
public:
	TimingPoint(int offset, float mspb, int meter);
	int offset;
	float mspb;
	int meter;
};