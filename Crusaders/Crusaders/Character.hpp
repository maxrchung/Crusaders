#pragma once

#include "CharacterState.hpp"
#include "Simulation.hpp"
#include "Vector3.hpp"

class Simulation;

class Character
{
public:
	Character(Simulation* sim);
	
	Vector3 position = Vector3(0, 0, 0);
	Vector3 direction = Vector3(0, 0, -1);
	Vector3 up = Vector3(0, 1, 0);

	void shoot();
	void Update();
	void spawnBullets();

	float enemyDistance(Vector3 enemyVector);

private:
	CharacterState state = CharacterState::Idle;

	int bulletcount;
	int health;
	Simulation* simulation;

	//some structure to hold monsters in sight of char, <DEQUE> OF TYPE OBJECT*

	//some ray-casted line, using projection, which exists in OsuukiSB

};