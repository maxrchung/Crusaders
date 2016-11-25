#pragma once

#include "ObjectPoints.hpp"
#include "SimulationState.hpp"
#include "SpawnInfoManager.hpp"
#include <list>
#include "Object.hpp"
#include "Overworld.hpp"
#include "Enemy.hpp"

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

	bool simulationRunning = false;
	int time = 0;
	int delta = 1000;
	std::vector<ObjectPoints*> loadObjectPoints;
	std::list<Enemy*> enemies;

};