#pragma once

class ObjectPoints;
class Simulation;

#include "Vector3.hpp"

class Bullet {
public:
	Bullet(Simulation* sim, Vector3 start, Vector3 dir);
	Simulation* simulation;
	void Update();
	void Draw();
private:
	Vector3 startPoint;
	Vector3 direction;
	Vector3 finalPos;
	ObjectPoints* bullet;

	// Making this unstatic since it's possible we want different power for bullets
	int bulletPower;
};