#pragma once

#include "ObjectPoints.hpp"
#include "SimulationState.hpp"
#include "SpawnInfoManager.hpp"

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

	bool simulationRunning = true;
	int time = 0;
	int delta = 1000;

	std::vector<ObjectPoints*> loadObjectPoints;

};