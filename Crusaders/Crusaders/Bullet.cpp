#include "Bullet.hpp"
#include "ObjectPoints.hpp"
#include "Simulation.hpp"
#include <iostream>

Bullet::Bullet(Simulation* sim, Vector3 start, Vector3 dir)
	: simulation(sim), startPoint(start), bulletPower(50), direction(dir)
{
	std::cout << "bullet initialized" << std::endl;
	
	bullet = new ObjectPoints(simulation, {
		Face(Vector3(-1, 1, 1), Vector3(1, 1, 1), Vector3(1, -1, 1), Vector3(-1, -1, 1)),	//front
		Face(Vector3(1, 1, 1), Vector3(1, 1, -4), Vector3(1, -1, -4), Vector3(1, -1, 1)),	//right
		Face(Vector3(1, 1, -4), Vector3(-1, 1, -4), Vector3(-1, -1, -4), Vector3(1, -1, -4)),	//back
		Face(Vector3(-1, 1, -4), Vector3(-1, 1, 1), Vector3(-1, -1, 1), Vector3(-1, -1, -4)) }); //left

	bullet->ScaleTo(10.0f);
	bullet->MoveTo(startPoint);
	finalPos = dir * bulletPower;
}

void Bullet::Update()
{
	//std::cout << bullet->center.x << " " << bullet->center.y << " " << bullet->center.z << std::endl;
	bullet->Move(direction * bulletPower);
}

void Bullet::Draw()
{
	simulation->DrawLoad(bullet);
}