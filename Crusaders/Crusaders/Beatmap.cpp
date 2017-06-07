#include "Beatmap.hpp"
#include "BeatmapReadSection.hpp"
#include "InheritedTimingPoint.hpp"
#include "Note.hpp"
#include "Spinner.hpp"
#include "Path.hpp"
#include "Slider.hpp"
#include "TimingPoint.hpp"
#include "Vector2.hpp"
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>

Beatmap::Beatmap(std::string& filePath) {
	read(filePath);
	resolveTimingPoints();
	calculateSliderEnds();
	findSongStartEnd();
}

void Beatmap::read(std::string& filePath) {
	std::ifstream input;
	input.open(filePath);

	BeatmapReadSection::Section section = BeatmapReadSection::None;
	for (std::string line; std::getline(input, line); )
	{
		// Ignore comments
		if (line.substr(0, 2) == "//") {
			continue;
		}
		// Skip if empty
		else if (line.empty()) {
			continue;
		}

		// Denote which section we are in
		if (line[0] == '[') {
			if (line == "[General]") {
				section = BeatmapReadSection::General;
			}
			else if (line == "[Editor]") {
				section = BeatmapReadSection::Editor;
			}
			else if (line == "[Metadata]") {
				section = BeatmapReadSection::Metadata;
			}
			else if (line == "[Difficulty]") {
				section = BeatmapReadSection::Difficulty;
			}
			else if (line == "[Events]") {
				section = BeatmapReadSection::Events;
			}
			else if (line == "[TimingPoints]") {
				section = BeatmapReadSection::TimingPoints;
			}
			else if (line == "[HitObjects]") {
				section = BeatmapReadSection::HitObjects;
			}

			// Skip if we changed sections
			continue;
		}
		
		// Parse line based on section
		switch (section) {
			case BeatmapReadSection::Difficulty: {
				processDifficulty(line);
				break;
			}
			case BeatmapReadSection::TimingPoints: {
				processTimingPoint(line);
				break;
			}
			case BeatmapReadSection::HitObjects: {
				processHitObject(line);
				break;
			}
		}
	}
	input.close();
}

std::vector<std::string> Beatmap::separate(std::string& line, char toReplace, char replaceWith) {
	std::string replaced = std::string(line);
	for (int i = 0; i < line.length(); ++i) {
		if (line[i] == toReplace) {
			replaced[i] = replaceWith;
		}
	}

	std::vector<std::string> separated;
	std::stringstream stream = std::stringstream(replaced);

	std::string counter;
	while (stream >> counter) {
		separated.push_back(counter);
	}

	return separated;
}

void Beatmap::processHitObject(std::string& line) {
	std::vector<std::string> separated = separate(line, ',', ' ');

	int posX = std::stoi(separated[0]);
	int posY = std::stoi(separated[1]);
	Vector2 position(posX, posY);
	int start = std::stoi(separated[2]);

	int type = std::stoi(separated[3]);
	if (type & 1) {
		Note note(start);
		notes.push_back(note);
	}
	else if (type & 2) {
		// Start position as first transition point
		std::vector<Vector2> transitions({ position });

		std::string info = separated[5];
		std::vector<std::string> pairs = separate(info, '|', ' ');

		// Get the slider type from the front, we most likely don't need to use this
		std::string sliderType = pairs.front();

		// Skip front and get transition points
		for (int i = 1; i < pairs.size(); ++i) {
			std::vector<std::string> point = separate(pairs[i], ':', ' ');
			int pointX = std::stoi(point[0]);
			int pointY = std::stoi(point[1]);
			transitions.push_back(Vector2(pointX, pointY));
		}

		int repeat = std::stoi(separated[6]);
		float pixelLength = std::stof(separated[7]);

		Slider slider(start, transitions, repeat, pixelLength);
		sliders.push_back(slider);

		std::vector<Vector2> points;
		for (int i = 0; i <= 10; i++) {
			points.push_back(slider.bezier.findPosition(i / 10.0f));
		}
	}
	else if (type & 8) {
		int end = std::stoi(separated[5]);

		Spinner spinner(start, end);
		spinners.push_back(spinner);
	}
}

void Beatmap::processTimingPoint(std::string& line) {
	std::vector<std::string> separated = separate(line, ',', ' ');

	int offset = std::stoi(separated[0]);
	float mspb = std::stof(separated[1]);
	int meter = std::stoi(separated[2]);
	bool inherited = std::stoi(separated[6]);

	// For some reason it's 1 to indicate not inherited and 1 to represent inherited
	if (inherited) {
		TimingPoint* timingPoint = new TimingPoint(offset, mspb, meter);
		timingPoints.push_back(timingPoint);
	}
	else {
		InheritedTimingPoint* inheritedTimingPoint = new InheritedTimingPoint(offset, mspb);
		inheritedTimingPoints.push_back(inheritedTimingPoint);
	}
}

void Beatmap::processDifficulty(std::string& line) {
	std::vector<std::string> separated = separate(line, ':', ' ');

	std::string identifier = separated[0];
	float value = std::stof(separated[1]);

	if (identifier == "HPDrainRate") {
		hpDrainRate = value;
	}
	else if (identifier == "CircleSize") {
		circleSize = value;
	}
	else if (identifier == "OverallDifficulty") {
		overallDifficulty = value;
	}
	else if (identifier == "ApproachRate") {
		approachRate = value;
	}
	else if (identifier == "SliderMultiplier") {
		sliderMultiplier = value;
	}
	else if (identifier == "SliderTickRate") {
		sliderTickRate = value;
	}
}

void Beatmap::resolveTimingPoints() {
	// Setup a stack that takes in inheritedTimingPoints
	// We're going to loop backwards to insert inherited timing points into timing points
	// The reason we loop backwards is because this way we won't skip over timingPoints
	std::stack<InheritedTimingPoint*> inheritedStack;
	for (auto inheritedTimingPoint : inheritedTimingPoints) {
		inheritedStack.push(inheritedTimingPoint);
	}

	for (int i = timingPoints.size() - 1; i >= 0; --i) {
		// We make another stack here to reflip our values
		std::stack<InheritedTimingPoint*> toAdd;
		while (!inheritedStack.empty() && inheritedStack.top()->offset > timingPoints[i]->offset) {
			toAdd.push(inheritedStack.top());
			inheritedStack.pop();
		}

		while (!toAdd.empty()) {
			timingPoints[i]->inheritedTimingPoints.push_back(toAdd.top());
			toAdd.pop();
		}
	}
}

void Beatmap::calculateSliderEnds() {
	for (auto& slider : sliders) {
		TimingPoint* timingPoint = getTimingPoint(slider.start);
		// If timingPoint doesn't exist, use the first point
		if (!timingPoint) {
			timingPoint = timingPoints.front();
		}

		InheritedTimingPoint* inheritedTimingPoint = getInheritedTimingPoint(timingPoint, slider.start);
		// It's possible that the inherited timing point doesn't exist
		float totalMultiplier;
		if (inheritedTimingPoint) {
			totalMultiplier = sliderMultiplier * inheritedTimingPoint->sliderMultiplier;
		}
		else {
			totalMultiplier = sliderMultiplier;
		}
		// Break up into quarter beats
		float beats = slider.pixelLength / totalMultiplier / 100.0f;
		// Multiply to find total length
		float length = beats * timingPoint->mspb;
		int end = slider.start + length;
		slider.end = end;
	}
}

TimingPoint* Beatmap::getTimingPoint(int offset) {
	TimingPoint* tp = NULL;
	for (auto timingPoint : timingPoints) {
		if (timingPoint->offset < offset) {
			tp = timingPoint;
		}
		else {
			break;
		}
	}
	return tp;
}

InheritedTimingPoint* Beatmap::getInheritedTimingPoint(TimingPoint* timingPoint, int offset) {
	InheritedTimingPoint* itp = NULL;
	for (auto inheritedTimingPoint : timingPoint->inheritedTimingPoints) {
		if (inheritedTimingPoint->offset < offset) {
			itp = inheritedTimingPoint;
		}
		else {
			break;
		}
	}
	return itp;
}

void Beatmap::findSongStartEnd() {
	int sliderStart = INT32_MAX;
	int sliderEnd = INT32_MIN;
	if (!sliders.empty()) {
		sliderStart = sliders.front().start;
		sliderEnd = sliders.back().end;
	}

	int noteStart = INT32_MAX;
	int noteEnd = INT32_MIN;
	if (!notes.empty()) {
		noteStart = notes.front().start;
		noteEnd = notes.back().start;
	}
	
	int spinnerStart = INT32_MAX;
	int spinnerEnd = INT32_MIN;
	if (!spinners.empty()) {
		spinnerStart = spinners.front().start;
		spinnerEnd = spinners.back().end;
	}

	if (sliderStart == INT32_MAX && noteStart == INT32_MAX && spinnerStart == INT32_MAX) {
		throw "No HitObjects found.";
	}

	int min = INT32_MAX;
	if (sliderStart < min) {
		min = sliderStart;
	}
	if (noteStart < min) {
		min = noteStart;
	}
	if (spinnerStart < min) {
		min = spinnerStart;
	}

	int max = INT32_MIN;
	if (sliderEnd > max) {
		max = sliderEnd;
	}
	if (noteEnd > max) {
		max = noteEnd;
	}
	if (spinnerEnd > max) {
		max = spinnerEnd;
	}

	songStart = min;
	songEnd = max;
}