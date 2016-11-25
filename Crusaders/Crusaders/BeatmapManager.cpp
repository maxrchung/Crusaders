#include "BeatmapManager.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

BeatmapManager::BeatmapManager(std::string filepath)
{
	readFile(filepath);
}
BeatmapManager::readFile(std::string filepath)
{
	inputFile.open(filepath);
	std::string textline;
	std::vector<std::string> stringCounter;
		
	while (textline != "[HitObjects]")
	{
		std::getline(inputFile, textline);
	}
	while (textline != "")
	{
		std::getline(inputFile, textline);
		std::istringstream stream(textline);

	}

}