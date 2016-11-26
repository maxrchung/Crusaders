#pragma once

#include "Enemy.hpp"
#include "Simulation.hpp"
#include "ObjectPoints.hpp"
#include "SpawnInfo.hpp"

class Boss : public Enemy {
public:
	Boss(Simulation* simulation, SpawnInfo spawnInfo);
	ObjectPoints* object;
	Simulation* simulation;
	SpawnInfo spawnInfo;
	int new_health = health;
	EnemyState boss_state = state;

	void Update();
	void Draw(); 
};
