#include "SpawnInfoManager.hpp"
#include "Enemy.hpp"
#include "Boss.hpp"
#include "Simulation.hpp"

SpawnInfoManager::SpawnInfoManager(Simulation* simulation) 
	: simulation(simulation) {
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
	if (time > SpawnInfoManager::spawnInfos.front().spawn.ms){
		enemy = SpawnInfoManager::spawnInfos.front().type;
		Enemy* enemy_object;
		Boss* boss_object;
		SpawnInfoManager::spawnInfos.pop_front();
		switch (enemy) {
			case ObjectType::Basic: 
				enemy_object = new Enemy(simulation);
				simulation->LoadDraw(enemy_object->object);
				break;
			case ObjectType::Boss: 
				boss_object = new Boss(simulation);
				simulation->LoadDraw(boss_object->object);
		}
	}
}