#include "BeatmapManager.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "BeatmapObject.hpp"
#include <tuple>
#include "Slider.hpp"
#include "Note.hpp"
#include "Spinner.hpp"

BeatmapManager::BeatmapManager(Simulation* sim, std::string& filepath)
	: simulation(sim)
{
	readFile(filepath);
}

void BeatmapManager::Process()
{
	for (auto mapObject : mapObjects) {
		mapObject->Update();
	}
}

void BeatmapManager::readFile(std::string& filepath)
{
	inputFile.open(filepath);
	std::string textline;
	std::vector<std::string> stringCounter;

	bool reachedHitObjects = false;
	
	if (!inputFile.is_open())
	{
		std::cerr << "Error opening file" << std::endl;
		exit(EXIT_FAILURE);
	}

	for (std::string line; std::getline(inputFile, line); )
	{
		if (line == "[HitObjects]")
		{
			reachedHitObjects = true;
		}
		if (reachedHitObjects == true && line != "[HitObjects]")
		{
			
			stringCounter = seperateLine(line, ' ');
			createMapObject(stringCounter);	
		}

	}

	std::cout << "BeatmapManager vector size = " << mapObjects.size() << std::endl;
	inputFile.close();
}

std::vector<std::string> BeatmapManager::seperateLine(std::string& line, char clearby)
{
	std::string clearedLine = clearChars(line,',');
	std::vector<std::string> returnVect;
	std::string tempstr;
	std::stringstream tempStream = std::stringstream(clearedLine);

	while (tempStream >> tempstr)
	{
		returnVect.push_back(tempstr);
	}

	return returnVect;
}

std::string BeatmapManager::clearChars(std::string& line, char clearby)
{
	std::string resultline = std::string(line);
	for (int i = 0; i < line.length(); ++i)
	{
		if (line[i] == clearby)
		{
			resultline[i] = ' ';
		}
	}
	return resultline;
}

std::vector<std::tuple<int, int>> BeatmapManager::getSliderTransitions(std::string transits)
{
	//get the slider transitions from the index they're in. This function should convert the strings into ints using std::stoi(str).
	//#1: clear chars by '|'
	//#2 seperate the int:int transition pairs by ':'
	int indextracker = 0;
	int indextracker2 = 0;

	std::vector<std::tuple<int, int>> xyTupleVector;
	std::vector<std::string> clearedString = seperateLine(transits, '|');

	std::vector<std::string> tempStrVec;

	for (std::vector<std::string>::iterator i = clearedString.begin(); i != clearedString.end(); ++i)
	{
		//ignore the first index, which happens to be the B,P,L,C character
		if (indextracker2 != 0)
		{
			tempStrVec = seperateLine(clearChars(*i, ':'), ' ');
			xyTupleVector.push_back(std::make_tuple(std::stoi(tempStrVec[0]), std::stoi(tempStrVec[1])));
		}
		indextracker2 += 1;
	}
	return xyTupleVector;
}

void BeatmapManager::createMapObject(std::vector<std::string>& objectVector)
{
	int indexer = 0;
	int vectorLength = objectVector.size();
	bool isSlider = false;
	std::string stringer;

	//check for the 5th index of the line to see if it has B,P,L,C which indicates that 
	//it is a slider.
	if (objectVector[5][0] == 'B' || objectVector[5][0] == 'P' || objectVector[5][0] == 'L' || objectVector[5][0] == 'C')
	{
		isSlider = true;
	}

	std::cout << objectVector.size() << std::endl;
	if (vectorLength == 6 && !isSlider)
	{
		mapObjects.push_back(new Note(simulation, std::stoi(objectVector[2])));
	}
	else if (vectorLength == 7 && !isSlider)
	{
		mapObjects.push_back(new Spinner(simulation, std::stoi(objectVector[2]), std::stoi(objectVector[5])));
	}
	else if (vectorLength >= 8 && isSlider)
	{
		mapObjects.push_back(new Slider(simulation, std::stoi(objectVector[0]), std::stoi(objectVector[1]), std::stoi(objectVector[2]), getSliderTransitions(stringer)));
	}
	//3 cases: len of 5 == note, len of 7 without BPLC == spinner, len of 6 or more, with BPLC = slider.
}

