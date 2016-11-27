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

void SpawnInfoManager::Process(int time) {
	// Compare time to front of list, pop off and spawn enemies
	// psuedocode:
	// if time > front of list
	// pop off front of spawninfo list
	// switch case type
	// case: new BasicCubeMonsterFaceThing()
	// simulation->objects.push_back(case) 
	ObjectType enemy;
	if (!SpawnInfoManager::spawnInfos.empty()) {
		if (time >= SpawnInfoManager::spawnInfos.front().spawn.ms) {
			enemy = SpawnInfoManager::spawnInfos.front().type;
			Enemy* enemy_object;
			switch (enemy) {
			case ObjectType::Basic:
				enemy_object = new Enemy(simulation, SpawnInfoManager::spawnInfos.front());
				break;
			case ObjectType::Boss:
				enemy_object = new Boss(simulation, SpawnInfoManager::spawnInfos.front());
				break;
			}
			simulation->enemies.push_back(enemy_object);
			SpawnInfoManager::spawnInfos.pop_front();
		}
	}
}