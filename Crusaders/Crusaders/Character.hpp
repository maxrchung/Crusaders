#pragma once

#include "Camera.hpp"
#include "CharacterState.hpp"
#include "Simulation.hpp"
#include "Vector3.hpp"
#include "Bullet.hpp"

class Camera;
class ObjectPoints;
class Simulation;

class Character
{
public:
	Character(Simulation* sim);
	
	Camera* camera;

	void shoot();
	void Update();
	void Draw();
	void spawnBullets();

	float enemyDistance(Vector3 enemyVector);
	ObjectPoints* gun;

private:
	CharacterState state = CharacterState::Idle;

	int bulletcount;
	int health;
	Simulation* simulation;

	//some structure to hold monsters in sight of char, <DEQUE> OF TYPE OBJECT*

	//some ray-casted line, using projection, which exists in OsuukiSB

};