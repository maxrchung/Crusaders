#include "Character.hpp"
#include <vector>
#include "Simulation.hpp"
#include "CharacterState.h"

Character::Character(Simulation* sim)
	: simulation{sim}
{
}

void Character::Update()
{
	if (state == Idle)
	{
		shoot();
	}
}

float Character::enemyDistance(Vector3 enemyVector)
{
	Vector3 resultVector = position.project(enemyVector);
	return resultVector.Magnitude();
}

Vector3 Character::getPosition()
{
	return position;
}

void Character::setPosition(Vector3 newPosition)
{
	position = newposition;
}

void Character::shoot()
{
	//for object in simulation->enemies
	state = CharacterState::Shooting;
	spawnBullets();
	state = CharacterState::Idle;
}

void Character::spawnBullets()
{
	//spawn bullets
}