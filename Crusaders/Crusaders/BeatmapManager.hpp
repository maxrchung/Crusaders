#pragma once

class BeatmapManager
{
public:
	BeatmapManager(std::string filepath);

private:
	std::ifstream inputFile;
	void readFile(std::string filepath);
	//vector of beatmapobject here
};