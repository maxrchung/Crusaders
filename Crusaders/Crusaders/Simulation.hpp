#pragma once
#define M_PI 3.14159265359f

class SpawnInfoManager;
class ObjectPoints;
class Camera;
class Path;

#include "Marker.hpp"
#include "SimulationState.hpp"
#include <iostream>
#include <list>
#include <deque>
#include <queue>
#include <vector>

class Simulation {
public:
	Simulation(Path* path);
	void Run();
	void Update();
	// Allows an object to load its objectPoints into the simulation
	void DrawLoad(ObjectPoints* objectPoints);
	// Responsible for calling Draw for each object it keeps track of
	void Draw();
	// Draws all loaded objects and clears list
	void DrawRender();

	SimulationState state;
	Camera* camera;

	bool simulationRunning;
	int time;
	int timeEnd;
	int delta;
	// Need for correct calculation independent of framerate
	float dps;
	// In every frame, loadObjectPoints will be loaded by classes
	// Then, Simulation will draw the objects
	// Once Simulation finishes drawing, it clears this data structure for the next frame
	std::vector<ObjectPoints*> loadObjectPoints;
	Path* path;

	std::queue<Marker> remainingMarkers;
	std::deque<Marker> currentMarkers;
	float markerDistance;

private:
	// Fills currentMarkers by comparing the distance between remainingMarkers
	// with the camera position
	void fillCurrentMarkers();
};