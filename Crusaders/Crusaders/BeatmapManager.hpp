#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include "BeatmapObject.hpp"
#include <tuple>
class BeatmapObject;

class BeatmapManager
{
public:
	BeatmapManager(std::string& filepath, Simulation* sim);
	void Process();

private:
	std::ifstream inputFile;
	void readFile(std::string& filepath);
	std::string clearChars(std::string& line, char clearby);

	std::vector<std::string> seperateLine(std::string& line, char clearby);
	std::vector<BeatmapObject*> mapObjects;

	void createMapObject(std::vector<std::string>& objectVector);

	std::vector<std::tuple<int, int>> getSliderTransitions(std::string transits);
	Simulation* simulation;

};