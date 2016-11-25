#pragma once

#include "ObjectPoints.hpp"
#include "EnemyState.hpp"
#include "Simulation.hpp"

class Enemy{
public:
	Enemy();
	Enemy(Simulation* simulation);
	ObjectPoints* object;
	Simulation* simulation;
	int health = 10;
	EnemyState state = EnemyState::Idle;

};