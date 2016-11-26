#include "Note.hpp"
#include <iostream>

Note::Note(int time, Simulation* sim)
	:BeatmapObject{time, sim}
{
	//std::cout << "Note Initialized" << std::endl;
}