#pragma once

class BeatmapObject;
class Path;

#include "BeatmapObject.hpp"
#include <fstream>
#include <string>
#include <tuple>
#include <vector>

class BeatmapManager {
public:
	BeatmapManager(std::string& filepath);
	void Process();
	Path* GeneratePath();

private:
	std::ifstream inputFile;
	void readFile(std::string& filepath);
	std::string clearChars(std::string& line, char clearby);

	std::vector<std::string> seperateLine(std::string& line, char clearby);
	std::vector<BeatmapObject*> mapObjects;

	void createMapObject(std::vector<std::string>& objectVector);

	std::vector<std::tuple<int, int>> getSliderTransitions(std::string transits);
};