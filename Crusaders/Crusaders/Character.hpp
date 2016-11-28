#pragma once

class Camera;
class Simulation;
class ObjectPoints;

#include "CharacterState.hpp"
#include "Vector3.hpp"

class Character
{
public:
	Character(Simulation* sim);
	
	Camera* camera;

	void Update();
	void Draw();

	float enemyDistance(Vector3 enemyVector);
	ObjectPoints* gun;

private:
	CharacterState state;

	int bulletCount;
	int health;
	Simulation* simulation;
};