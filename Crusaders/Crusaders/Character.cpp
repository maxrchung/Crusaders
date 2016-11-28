#include "Character.hpp"
#include "Bullet.hpp"
#include "Simulation.hpp"
#include "Camera.hpp"
#include "ObjectPoints.hpp"
#include <vector>

Character::Character(Simulation* sim)
	: simulation(sim), camera(new Camera(sim))
{
	health = 100;
	bulletcount = 30;
	gun = new ObjectPoints(simulation, { 
		Face(Vector3(-1, 1, 1), Vector3(1, 1, 1), Vector3(1, -1, 1), Vector3(-1, -1, 1)),	//front
		Face(Vector3(1, 1, 1), Vector3(1, 1, -4), Vector3(1, -1, -4), Vector3(1, -1, 1)),	//right
		Face(Vector3(1, 1, -4), Vector3(-1, 1, -4), Vector3(-1, -1, -4), Vector3(1, -1, -4)),	//back
		Face(Vector3(-1, 1, -4), Vector3(-1, 1, 1), Vector3(-1, -1, 1), Vector3(-1, -1, -4)) }); //left


	gun->Move(Vector3(100,-100,-200));
	gun->ScaleTo(50.0f);

}

void Character::Update()
{
	simulation->camera->localVector = -gun->center + simulation->camera->position; //creates the local vector between camera and gungj	
}

void Character::Draw() {
	simulation->DrawLoad(gun);

}

float Character::enemyDistance(Vector3 enemyVector)
{
	Vector3 resultVector = camera->position.Project(enemyVector);
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
	//std::cout << "Spawn Bullets" << std::endl;
	simulation->bulletList.push_back(new Bullet(gun->center, camera->direction, simulation));
	//spawn bullets
}