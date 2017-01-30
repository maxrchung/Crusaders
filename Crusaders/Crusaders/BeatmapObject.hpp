#pragma once

class BeatmapObject {
public:
	BeatmapObject(int startTime, bool finished);
	virtual void Update() = 0;
	int startTime;
	bool finished;
};