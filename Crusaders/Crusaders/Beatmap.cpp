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

		// Denote which section we are in
		if (line[0] == '[') {
			if (line == "[HitObjects]") {
				section = BeatmapReadSection::HitObjects;
			}
			else if (line == "[TimingPoints]") {
				section = BeatmapReadSection::TimingPoints;
			}
			else if (line == "[Difficulty]") {
				section = BeatmapReadSection::Difficulty;
			}

			// Skip if we changed sections
			continue;
		}
		
		// Parse line based on section
		switch (section) {
			case BeatmapReadSection::HitObjects: {
				processHitObject(line);
				break;
			}
			case BeatmapReadSection::TimingPoints: {
				processTimingPoint(line);
				break;
			}
			case BeatmapReadSection::Difficulty: {
				processDifficulty(line);
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
	for (auto inheritedTimingPoint : inheritedTimingPoints) {
		for (auto timingPoint : timingPoints) {
			if (inheritedTimingPoint->offset > timingPoint->offset) {
				timingPoint->inheritedTimingPoints.push_back(inheritedTimingPoint);
			}
		}
	}
}

void Beatmap::calculateSliderEnds() {
	for (auto slider : sliders) {
		TimingPoint* timingPoint = getTimingPoint(slider.start);
		InheritedTimingPoint* inheritedTimingPoint = getInheritedTimingPoint(timingPoint, slider.start);

		float totalMultiplier = sliderMultiplier * inheritedTimingPoint->sliderMultiplier;
		float beats = slider.pixelLength / totalMultiplier;
		float length = beats * timingPoint->mspb;
		int end = slider.start + length;
		slider.end = end;
	}
}

TimingPoint* Beatmap::getTimingPoint(int offset) {
	TimingPoint* tp;
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
	InheritedTimingPoint* itp;
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

	if (sliderStart < 0 && noteStart < 0 && spinnerStart < 0) {
		throw "No HitObjects found.";
	}

	int min = INT32_MAX;
	if (sliderStart < min) {
		min = sliderStart;
	}
	else if (noteStart < min) {
		min = noteStart;
	}
	else if (spinnerStart < min) {
		min = spinnerStart;
	}

	int max = INT32_MIN;
	if (sliderEnd > max) {
		max = sliderEnd;
	}
	else if (noteEnd > max) {
		max = noteEnd;
	}
	else if (spinnerEnd > max) {
		max = spinnerEnd;
	}

	songStart = min;
	songEnd = max;
}