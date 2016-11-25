#include "SpawnInfoManager.hpp"

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
}