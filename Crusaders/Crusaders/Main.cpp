#include "Simulation.hpp"
#include "Storyboard.hpp"
#include <string>
#include <iostream>
#include "BeatmapManager.hpp"
#include <tuple>

std::vector<std::string> createPath(int argc, char* argv[])
{
	std::string completepath = "";
	std::string typedPath = argv[argc - 1];
	std::vector<std::string> twoPaths;

	for (int i = 1; i < argc; ++i)
	{
		completepath += argv[i]; //fix the deletion of spaces at argv[argc-1] index
	}

	if (typedPath[typedPath.length() - 1] == '\\' )
	{
		twoPaths.push_back(completepath + "Quarks - Crusaders in Virtuality (Brenn52).osb");
		twoPaths.push_back(completepath + "Quarks - Crusaders In Virtuality (Brenn52) [Easy].osu");
	}
	else
	{
		twoPaths.push_back(completepath + "\\Quarks - Crusaders in Virtuality (Brenn52).osb");
		twoPaths.push_back(completepath + "\\Quarks - Crusaders In Virtuality (Brenn52) [Easy].osu");
	}
	std::cout << twoPaths[1] << std::endl;
	return twoPaths;
	
}

void main(int argc, char* argv[]) {
	Sprite* bg = new Sprite("dot.png");
	bg->ScaleVector(0, 100000, Vector2::ScreenSize, Vector2::ScreenSize);
	bg->Color(0, 100000, Color(0), Color(0));

	std::vector<std::string> completepaths = createPath(argc, argv);

	std::string s = std::string(completepaths[1]);

	Simulation* simulation = new Simulation();
	BeatmapManager BMM = BeatmapManager(s, simulation);
	simulation->beatmapManager = &BMM;
	simulation->Run();

	Storyboard::Instance()->Write(completepaths[0]);

	//std::cin.get();
}