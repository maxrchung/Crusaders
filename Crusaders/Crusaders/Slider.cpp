#include "Slider.hpp"
#include <vector>
#include <tuple>

Slider::Slider(int x, int y, int time, std::vector<std::tuple<int, int>> transpoints, Simulation* sim)
	:posX{x}, posY{y}, BeatmapObject{time, sim}, transitionPoints{transpoints}
{
	//std::cout << "Slider Initialized" << std::endl;
}

