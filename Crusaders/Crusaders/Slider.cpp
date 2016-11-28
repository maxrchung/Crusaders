#include "Slider.hpp"
#include <vector>
#include <tuple>

Slider::Slider(Simulation* simulation, int x, int y, int startTime, std::vector<std::tuple<int, int>> transitionPoints)
	: x(x), y(y), transitionPoints(transitionPoints), BeatmapObject(simulation, startTime, false)
{
	//std::cout << "Slider Initialized" << std::endl;
}

void Slider::Update()
{

}

