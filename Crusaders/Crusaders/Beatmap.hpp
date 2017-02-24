#pragma once

class InheritedTimingPoint;
class Note;
class Slider;
class Spinner;
class TimingPoint;

#include "Time.hpp"
#include <fstream>
#include <string>
#include <tuple>
#include <vector>

class Beatmap {
public:
	Beatmap(std::string& filePath);
	std::vector<Note> notes;
	std::vector<Slider> sliders;
	std::vector<Spinner> spinners;
	std::vector<TimingPoint*> timingPoints;
	std::vector<InheritedTimingPoint*> inheritedTimingPoints;

	float hpDrainRate;
	float circleSize;
	float overallDifficulty;
	float approachRate;
	float sliderMultiplier;
	float sliderTickRate;
	Time songEnd;
	Time songStart;

private:
	void read(std::string& filePath);
	std::vector<std::string> separate(std::string& line, char toReplace, char replaceWith);
	void processHitObject(std::string& line);
	void processTimingPoint(std::string& line);
	void processDifficulty(std::string& line);

	// Sets inherited timing points to non-inherited ones
	void resolveTimingPoints();
	// Sets the end time of sliders
	void calculateSliderEnds();
	// Sets the start and end of the song based on first and last notes
	void findSongStartEnd();
	// Gets a TimingPoint corresponding to an offset
	TimingPoint* getTimingPoint(int offset);
	// Gets an InheritedTimingPoint corresponding to an offset
	InheritedTimingPoint* getInheritedTimingPoint(TimingPoint* timingPoint, int offset);
};