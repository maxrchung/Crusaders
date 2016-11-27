#pragma once

#include "Enemy.hpp"
#include "SpawnInfo.hpp"

class Boss : public Enemy {
public:
	Boss(Simulation* simulation, SpawnInfo spawnInfo);

	void Update();
	void Draw(); 
};
