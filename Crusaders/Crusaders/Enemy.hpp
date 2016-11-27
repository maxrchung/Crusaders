#pragma once

class Simulation;
class ObjectPoints;

#include "SpawnInfo.hpp"
#include "EnemyState.hpp"

class Enemy{
public:
	Enemy() {};
	Enemy(Simulation* simulation, SpawnInfo spawninfo);
	ObjectPoints* object;
	Simulation* simulation;
	SpawnInfo spawninfo;
	int health = 10;
	EnemyState state = EnemyState::Idle;
	int temp_time = 0;

	void Update();
	void Draw();
};