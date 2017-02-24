#include "Marker.hpp"

Marker::Marker(Vector3 position, int time, bool onBeat) 
	: position(position), onBeat(onBeat), time(time) {
}

Marker::Marker() {}
