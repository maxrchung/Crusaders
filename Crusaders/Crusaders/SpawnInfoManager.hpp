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

	std::list<SpawnInfo> spawnInfos = std::list<SpawnInfo>({
		SpawnInfo(Time("00:00:000"), ObjectType::Basic, Vector3(0, 0, -200)),
		SpawnInfo(Time("00:05:000"), ObjectType::Basic, Vector3::Zero),
		SpawnInfo(Time("00:07:000"), ObjectType::Basic, Vector3(1, 0, -100))
	});

	Simulation* simulation;
};