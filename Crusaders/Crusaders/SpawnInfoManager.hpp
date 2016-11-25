#pragma once

#include "Simulation.hpp"
#include "SimulationState.hpp"
#include "SpawnInfo.hpp"
#include <list>

class Simulation;

class SpawnInfoManager {
public:
	SpawnInfoManager(Simulation* simulation);
	void Process(int time);

	std::list<SpawnInfo> spawnInfos = std::list<SpawnInfo>({
		SpawnInfo(Time("00:00:000"), ObjectType::Basic, Vector3::Zero),
		SpawnInfo(Time("00:01:000"), ObjectType::Basic, Vector3::Zero),
		SpawnInfo(Time("00:02:000"), ObjectType::Basic, Vector3::Zero)
	});

	Simulation* simulation;
};