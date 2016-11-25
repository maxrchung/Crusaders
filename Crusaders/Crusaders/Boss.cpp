#include "Boss.hpp"
#include "ObjectPoints.hpp"
#include "Simulation.hpp"


Boss::Boss() {
}

Boss::Boss(Simulation* simulation)
	: simulation(simulation) {
	object = new ObjectPoints(simulation, {Face(Vector3(-1, 1, 1), Vector3(1, 1, 1), Vector3(1, -1, 1), Vector3(-1, -1, 1))});
}
