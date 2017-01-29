#pragma once
#define M_PI 3.14159265359f

class SpawnInfoManager;
class ObjectPoints;
class Overworld;
class Camera;
class Character;
class Enemy;
class BeatmapManager;
class Bullet;

#include "SimulationState.hpp"
#include <iostream>
#include <list>
#include <vector>

class Simulation {
public:
	Simulation();
	void Run();
	void Update();
	// Separated this out from Update function to differentiate deletion
	void UpdateDelete();
	// Allows an object to load its objectPoints into the simulation
	void DrawLoad(ObjectPoints* objectPoints);
	// Responsible for calling Draw for each object it keeps track of
	void Draw();
	// Draws all loaded objects and clears list
	void DrawRender();

	SimulationState state;
	Character* character;
	Camera* camera;
	BeatmapManager* beatmapManager;

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
};