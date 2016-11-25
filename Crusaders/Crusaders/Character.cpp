#include "Character.hpp"
#include <vector>
#include "Simulation.hpp"

Character::Character(Simulation* sim)
	: simulation{sim}
{
}

void Character::Update()
{
	if (state == CharacterState::Idle)
	{
		shoot();
	}
}

float Character::enemyDistance(Vector3 enemyVector)
{
	Vector3 resultVector = position.Project(enemyVector);
	return resultVector.Magnitude();
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