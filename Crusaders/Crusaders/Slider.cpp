#include "Slider.hpp"

Slider::Slider(int start, int repeat, std::vector<Vector2> transitions)
	: BeatmapObject(start), repeat(repeat), transitions(transitions) {
}