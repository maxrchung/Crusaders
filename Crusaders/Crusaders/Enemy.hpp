#pragma once

#include "ObjectPoints.hpp"
#include "EnemyState.hpp"
#include "Simulation.hpp"
#include "SpawnInfo.hpp"

class Simulation;
class ObjectPoints;

class Enemy{
public:
	Enemy() {};
	Enemy(Simulation* simulation, SpawnInfo spawninfo);
	ObjectPoints* object;
	Simulation* simulation;
	SpawnInfo spawninfo;
	int health = 10;
	EnemyState state = EnemyState::Idle;

	void Update();
	void Draw();
};