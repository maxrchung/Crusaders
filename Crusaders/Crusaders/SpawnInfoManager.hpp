#pragma once

class Simulation;

#include "SpawnInfo.hpp"
#include <list>

class SpawnInfoManager {
public:
	SpawnInfoManager();
	SpawnInfoManager(Simulation* simulation);
	void Process();

	std::list<SpawnInfo> spawnInfos;

	Simulation* simulation;
};