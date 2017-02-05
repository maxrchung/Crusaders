#include "BeatmapManager.hpp"
#include "BeatmapReadSection.hpp"
#include "Slider.hpp"
#include "Note.hpp"
#include "Spinner.hpp"
#include "Path.hpp"
#include "Vector2.hpp"
#include <iostream>
#include <sstream>

BeatmapManager::BeatmapManager(std::string& filePath) {
	read(filePath);
}

Path* BeatmapManager::GeneratePath() {
	return new Path();
}

void BeatmapManager::read(std::string& filePath) {
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

			// Skip if we changed sections
			continue;
		}

		std::vector<std::string> separated = separate(line, ', ', ' ');
		
		// Parse line based on section
		switch (section) {
			case BeatmapReadSection::HitObjects: {
				processHitObject(separated);
				break;
			}
			case BeatmapReadSection::TimingPoints: {
				processTimingPoint(separated);
			}
		}
	}
	input.close();
}

std::vector<std::string> BeatmapManager::separate(std::string& line, char toReplace, char replaceWith) {
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

void BeatmapManager::processHitObject(std::vector<std::string>& separated) {
	int posX = std::stoi(separated[0]);
	int posY = std::stoi(separated[1]);
	Vector2 position(posX, posY);
	int start = std::stoi(separated[2]);

	int type = std::stoi(separated[3]);
	if (type & 1) {
		Note* note = new Note(start);
		hitObjects.push_back(note);
	}
	else if (type & 2) {
		int repeat = std::stoi(separated[6]);
		std::vector<Vector2> transitions({ position });

		std::string info = separated[5];
		// Drop the first 2 characters because we don't need to worry about the type of slider
		info = info.substr(2);

		std::vector<std::string> pairs = separate(info, '|');
		for (auto pair : pairs) {
			std::vector<std::string> point = separate(pair, ':');
			int pointX = std::stoi(point[0]);
			int pointY = std::stoi(point[1]);
			transitions.push_back(Vector2(pointX, pointY));
		}

		Slider* slider = new Slider(start, repeat, transitions);
		hitObjects.push_back(slider);
	}
	else if (type & 8) {
		int end = std::stoi(separated[5]);

		Spinner* spinner = new Spinner(start, end);
		hitObjects.push_back(spinner);
	}
}

void BeatmapManager::processTimingPoint(std::vector<std::string>& separated) {
	int offset = std::stoi(separated[0]);
	float mspb = std::stof(separated[1]);
	int meter = std::stoi(separated[2]);

	TimingPoint timingPoint(offset, mspb, meter);
	timingPoints.push_back(timingPoint);
}
