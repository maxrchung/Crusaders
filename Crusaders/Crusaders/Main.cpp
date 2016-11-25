#include "Simulation.hpp"
#include "Storyboard.hpp"
#include <string>
#include <iostream>

std::string createPath(int argc, char* argv[])
{
	std::string completepath = "";
	std::string typedPath = argv[argc - 1];

	for (int i = 1; i < argc; ++i)
	{
		completepath += argv[i];
	}

	if (typedPath[typedPath.length() - 1] == '\\' )
	{
		completepath += ("Quarks - Crusaders in Virtuality (Brenn52).osb");
	}
	else
	{
		completepath += ("\\Quarks - Crusaders in Virtuality (Brenn52).osb");
	}
	return completepath;
	
}

void main(int argc, char* argv[]) {
	Sprite* bg = new Sprite("dot.png");
	bg->ScaleVector(0, 100000, Vector2::ScreenSize, Vector2::ScreenSize);
	bg->Color(0, 100000, Color(0), Color(0));

	Simulation* simulation = new Simulation;
	simulation->Run();

	std::string completepath = createPath(argc, argv);
	Storyboard::Instance()->Write(completepath);

	//one argument: the path, with the .osu file after the last slash
	//Storyboard.write("processed path")
}