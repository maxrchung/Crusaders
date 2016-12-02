#include "SpawnInfoManager.hpp"
#include "Simulation.hpp"
#include "Boss.hpp"

SpawnInfoManager::SpawnInfoManager() {
}

SpawnInfoManager::SpawnInfoManager(Simulation* simulation) 
	: simulation(simulation) {

	spawnInfos = std::list<SpawnInfo>({
		SpawnInfo(Time("00:00:000"), ObjectType::Basic, Vector3(0, 0, -200)),
		SpawnInfo(Time("00:01:000"), ObjectType::Basic, Vector3(-100, 100, -200)),
		SpawnInfo(Time("00:02:000"), ObjectType::Basic, Vector3(100, 100, -200)),
		SpawnInfo(Time("00:03:000"), ObjectType::Boss, Vector3(0, 100, -200))
	});
}

void SpawnInfoManager::Process() {
	if (!SpawnInfoManager::spawnInfos.empty()) {
		if (simulation->time >= SpawnInfoManager::spawnInfos.front().spawn.ms) {
			ObjectType enemyType = SpawnInfoManager::spawnInfos.front().type;

			switch (enemyType) {
			case ObjectType::Basic:
				simulation->enemies.push_back(new Enemy(simulation, SpawnInfoManager::spawnInfos.front()));
				break;
			case ObjectType::Boss:
				simulation->enemies.push_back(new Boss(simulation, SpawnInfoManager::spawnInfos.front()));
				break;
			}
			
			SpawnInfoManager::spawnInfos.pop_front();
		}
	}
}