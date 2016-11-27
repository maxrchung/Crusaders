#pragma once

class Camera;
class Simulation;

#include "CharacterState.hpp"
#include "Vector3.hpp"

class Character
{
public:
	Character(Simulation* sim);
	
	Camera* camera;

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