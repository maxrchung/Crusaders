#pragma once

#include "ObjectPoints.hpp"
#include "SimulationState.hpp"
#include "SpawnInfoManager.hpp"
#include "Overworld.hpp"

class SpawnInfoManager;
class ObjectPoints;

class Simulation {
public:
	Simulation();
	void Run();
	void Update();
	void Draw();
	void LoadDraw(ObjectPoints* objectPoints);

	SpawnInfoManager* spawnInfoManager;
	SimulationState state = SimulationState::Level1;
	Overworld* world;

	bool simulationRunning = true;
	int time = 0;
	int timePerFrame = 1000;
	std::vector<ObjectPoints*> loadObjectPoints;

};