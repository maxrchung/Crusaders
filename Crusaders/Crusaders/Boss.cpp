#include "Boss.hpp"
#include "ObjectPoints.hpp"
#include "Simulation.hpp"




Boss::Boss(Simulation* simulation, SpawnInfo spawnInfo) {
	Enemy(simulation, spawnInfo);
	object = new ObjectPoints(simulation, {Face(Vector3(-1, 1, 1), Vector3(1, 1, 1), Vector3(1, -1, 1), Vector3(-1, -1, 1)),
										   Face(Vector3(1, 1, 1), Vector3(1, 1, -1), Vector3(1, -1, -1), Vector3(1, -1, 1)),
										   Face(Vector3(1, 1, -1), Vector3(-1, 1, -1), Vector3(-1, -1, -1), Vector3(1, -1, -1)),
										   Face(Vector3(-1, 1, -1), Vector3(-1, 1, 1), Vector3(-1, -1, 1), Vector3(-1, -1, -1))});
}
