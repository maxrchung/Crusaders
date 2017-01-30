#include "Slider.hpp"

Slider::Slider(int x, int y, int startTime, std::vector<std::tuple<int, int>> transitionPoints)
	: x(x), y(y), transitionPoints(transitionPoints), BeatmapObject(startTime, false)
{
	//std::cout << "Slider Initialized" << std::endl;
}

void Slider::Update()
{

}

