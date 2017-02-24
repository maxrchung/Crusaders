#pragma once

class Beatmap;
class Settings;

#include "Marker.hpp"
#include "Vector3.hpp"
#include <vector>

class Path {
public:
	Path(Beatmap* beatmap, Settings* settings);
	std::vector<Marker> markers;
};