#pragma once

#include "SimulationState.hpp"
#include "SpawnInfoManager.hpp"

class SpawnInfoManager;

class Simulation {
public:
	Simulation();
	void Run();
	void Update();
	void Draw();

	SpawnInfoManager* spawnInfoManager;
	Overworld* world;

	bool simulationRunning = true;
	int time = 0;
	int timePerFrame = 1000;

	SimulationState state;
};