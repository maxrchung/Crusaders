#include "Enemy.hpp"
#include "ObjectPoints.hpp"
#include "Simulation.hpp"

Enemy::Enemy() {
}

Enemy::Enemy(Simulation* simulation)
	: simulation(simulation) {
	object = new ObjectPoints(simulation, {Face(Vector3(-1, 1, 1), Vector3(1, 1, 1), Vector3(1, -1, 1), Vector3(-1, -1, 1))});
}



