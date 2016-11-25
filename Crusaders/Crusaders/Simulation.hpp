#pragma once

#include "ObjectPoints.hpp"
#include "SimulationState.hpp"
#include "SpawnInfoManager.hpp"
#include "Object.hpp"
#include "Overworld.hpp"
#include <deque>
#include <iostream>

#define M_PI 3.14159265359f

class SpawnInfoManager;
class ObjectPoints;
class Overworld;

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

	bool simulationRunning = true ;
	int time = 0;
	int delta = 1000;
	std::vector<ObjectPoints*> loadObjectPoints;
	std::deque<Object*> enemies;

};