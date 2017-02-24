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
				while (marker < beatmap->songStart.ms) {
					marker += timingPoints[i]->mspb;
				}
				// Need to go one less
				start = marker - timingPoints[i]->mspb;
				break;
			}
		}
	}

	// Pops off timing point when we pass it
	std::queue<TimingPoint*> tpq;
	for (auto timingPoint : timingPoints) {
		tpq.push(timingPoint);
	}

	TimingPoint* tp = timingPoints.front();

	while (start < beatmap->songEnd.ms) {
		while (!tpq.empty() && start > tpq.front()->offset) {
			tp = tpq.front();
			start = tp->offset;
			tpq.pop();
		}

		Marker marker(Vector3(0, 0, start), start, false);
		markers.push_back(marker);
	}
	// Add at least one marker after end
	Marker marker(Vector3(0, 0, start), start, false);
	markers.push_back(marker);
}