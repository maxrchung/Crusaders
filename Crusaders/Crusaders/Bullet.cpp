#include "Bullet.hpp"
#include "ObjectPoints.hpp"
#include "Simulation.hpp"
#include <iostream>


Bullet::Bullet(Vector3 start, Vector3 dir, Simulation* sim)
	:startPoint{start}, direction{dir}, simulation{sim}
{
	std::cout << "bullet initialized" << std::endl;
	
	bullet = new ObjectPoints(simulation, {
		Face(Vector3(-1, 1, 1), Vector3(1, 1, 1), Vector3(1, -1, 1), Vector3(-1, -1, 1)),	//front
		Face(Vector3(1, 1, 1), Vector3(1, 1, -4), Vector3(1, -1, -4), Vector3(1, -1, 1)),	//right
		Face(Vector3(1, 1, -4), Vector3(-1, 1, -4), Vector3(-1, -1, -4), Vector3(1, -1, -4)),	//back
		Face(Vector3(-1, 1, -4), Vector3(-1, 1, 1), Vector3(-1, -1, 1), Vector3(-1, -1, -4)) }); //left

	bullet->ScaleTo(10.0f);

	finalPos = dir * bulletPower;
}

void Bullet::Update()
{
	Move();
}

void Bullet::Move()
{
	//std::cout << bullet->center.x << " " << bullet->center.y << " " << bullet->center.z << std::endl;
	bullet->Move(startPoint + direction * bulletPower);
	simulation->DrawLoad(bullet);
}