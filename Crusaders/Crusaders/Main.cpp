#include "BeatmapManager.hpp"
#include "Simulation.hpp"
#include "Storyboard.hpp"
#include <string>
#include <iostream>
#include <time.h>

void main(int argc, char* argv[]) {
	//srand(time(NULL));

	Sprite* bg = new Sprite("dot.png");
	bg->ScaleVector(0, 100000, Vector2::ScreenSize, Vector2::ScreenSize);
	bg->Color(0, 100000, Color(0), Color(0));

	Simulation* simulation = new Simulation();
	std::string beatmapPath = argv[argc - 1];
	BeatmapManager BMM = BeatmapManager(simulation, beatmapPath);
	simulation->beatmapManager = &BMM;
	simulation->Run();

	int songNameIndex = beatmapPath.find_last_of('[');
	std::string songNamePath = beatmapPath.substr(0, songNameIndex - 1);
	std::string storyboardPath = songNamePath + ".osb";
	Storyboard::Instance()->Write(storyboardPath);

	//std::cin.get();
}