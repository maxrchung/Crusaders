#pragma once

class ObjectPoints;
class Simulation;

#include "Vector3.hpp"

class Bullet
{
public:
	Bullet(Vector3 start, Vector3 dir, Simulation* sim);
	Simulation* simulation;
	void Update();
	void Move();
private:
	Vector3 startPoint;
	Vector3 direction;
	Vector3 finalPos;
	ObjectPoints* bullet;
	static const int bulletPower = 50;

};