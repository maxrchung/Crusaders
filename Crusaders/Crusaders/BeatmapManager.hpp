#pragma once

class BeatmapObject;
class Path;

#include "BeatmapObject.hpp"
#include "TimingPoint.hpp"
#include <fstream>
#include <string>
#include <tuple>
#include <vector>

class BeatmapManager {
public:
	BeatmapManager(std::string& filePath);
	Path* GeneratePath();

private:
	void read(std::string& filePath);

	std::vector<std::string> separate(std::string& line, char toReplace, char replaceWith = ' ');
	void processHitObject(std::vector<std::string>& separated);
	void processTimingPoint(std::vector<std::string>& separated);

	std::vector<BeatmapObject*> hitObjects;
	std::vector<TimingPoint> timingPoints;

};