#pragma once

#include "Enemy.hpp"
#include "Simulation.hpp"
#include "ObjectPoints.hpp"

class Boss : public Enemy {
public:
	Boss();
	Boss(Simulation* simulation);
	ObjectPoints* object;
	Simulation* simulation;
	int new_health = health * 2;
	EnemyState boss_state = state;
};
