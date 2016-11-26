#pragma once

#include "Simulation.hpp"
#include "SimulationState.hpp"
#include "SpawnInfo.hpp"
#include <list>

class Simulation;

class SpawnInfoManager {
public:
	SpawnInfoManager();
	SpawnInfoManager(Simulation* simulation);
	void Process(int time);

	std::list<SpawnInfo> spawnInfos;

	Simulation* simulation;
};