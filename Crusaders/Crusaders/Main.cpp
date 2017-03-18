#include "Beatmap.hpp"
#include "Path.hpp"
#include "Settings.hpp"
#include "Simulation.hpp"
#include "Storyboard.hpp"
#include <string>
#include <iostream>
#include <time.h>

void main(int argc, char* argv[]) {
	srand(time(NULL));

	Settings* settings = new Settings();

	Sprite* bg = new Sprite("dot.png");
	bg->ScaleVector(0, 100000, Vector2::ScreenSize, Vector2::ScreenSize);
	bg->Color(0, 100000, Color(0), Color(0));

	std::string beatmapPath = argv[argc - 1];
	Beatmap* beatmap = new Beatmap(beatmapPath);
	
	Path* path = new Path(beatmap, settings);

	Simulation* simulation = new Simulation(path);
	simulation->Run();

	int songNameIndex = beatmapPath.find_last_of('[');
	std::string songNamePath = beatmapPath.substr(0, songNameIndex - 1);
	std::string storyboardPath = songNamePath + ".osb";
	Storyboard::Instance()->Write(storyboardPath);
}