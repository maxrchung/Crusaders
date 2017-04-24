#include "Beatmap.hpp"
#include "Path.hpp"
#include "TimingPoint.hpp"
#include <queue>

// 1 unit per millisecond
Path::Path(Beatmap* beatmap, Settings* settings) {
	std::vector<TimingPoint*> timingPoints = beatmap->timingPoints;

	int start;
	if (timingPoints.empty()) {
		throw "TimingPoints section cannot be empty.";
	}
	// Special case to handle start < the first timingPoint
	else if (beatmap->songStart.ms < timingPoints.front()->offset) {
		float marker = timingPoints.front()->offset;
		while (marker > beatmap->songStart.ms) {
			marker -= timingPoints.front()->mspb;
		}
		start = marker;
	}
	else {
		// Loop backwards until we find the timingPoint that is right before the start
		for (int i = timingPoints.size() - 1; i >= 0; --i) {
			// Once we've found the timing point, loop upwards to find the closest marker
			if (timingPoints[i]->offset <= beatmap->songStart.ms) {
				// Use float because we might add by some funkeh values
				float marker = timingPoints[i]->offset;
				// Keeps track of the most recent onBeat marker
				float onBeatMarker = marker;
				while (marker < beatmap->songStart.ms) {
					if (isOnBeat(timingPoints[i], marker)) {
						onBeatMarker = marker;
					}
					marker += timingPoints[i]->mspb;
				}
				// Need to go one less
				//start = marker - timingPoints[i]->mspb;
				start = onBeatMarker;
				break;
			}
		}
	}

	// Pops off timing point when we pass it
	std::queue<TimingPoint*> tpq;
	for (auto timingPoint : timingPoints) {
		tpq.push(timingPoint);
	}

	TimingPoint* front = tpq.front();
	// Pop first so the next one will always be the next available
	tpq.pop();

	while (start < beatmap->songEnd.ms) {
		while (!tpq.empty() && start > tpq.front()->offset) {
			front = tpq.front();
			// Set the start only if we haven't set any markers yet
			if (!markers.empty()) {
				start = front->offset;
			}
			tpq.pop();
		}

		bool onBeat = isOnBeat(front, start);
		if (onBeat) {
			Marker* marker = new Marker(Vector3(0, 0, start), start, true);
			markers.push_back(marker);
		}
		else {
			Marker* marker = new Marker(Vector3(0, 0, start), start, false);
			markers.push_back(marker);
		}

		start += front->mspb;
	}
	// Add at least one marker after end
	Marker* marker = new Marker(Vector3(0, 0, start), start, false);
	markers.push_back(marker);
}

bool Path::isOnBeat(TimingPoint* timingPoint, float time) {
	float diff = time - timingPoint->offset;
	int beatCounter = round(diff / timingPoint->mspb);
	bool onBeat = beatCounter % timingPoint->meter == 0;
	return onBeat;
}