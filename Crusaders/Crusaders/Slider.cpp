#include "Slider.hpp"

Slider::Slider(int start, std::vector<Vector2> transitions, int repeat, float pixelLength)
	: BeatmapObject(start), transitions(transitions), repeat(repeat), pixelLength(pixelLength), bezier(transitions) {
}