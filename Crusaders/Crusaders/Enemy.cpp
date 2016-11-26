#include "Enemy.hpp"
#include "ObjectPoints.hpp"
#include "Simulation.hpp"
#include "SpawnInfoManager.hpp"
#include <list>



Enemy::Enemy(Simulation* simulation, SpawnInfo spawninfo)
	: simulation(simulation), spawninfo(spawninfo) {
	object = new ObjectPoints(simulation, {Face(Vector3(-1, 1, 1), Vector3(1, 1, 1), Vector3(1, -1, 1), Vector3(-1, -1, 1)),
										   Face(Vector3(1, 1, 1), Vector3(1, 1, -1), Vector3(1, -1, -1), Vector3(1, -1, 1)),
										   Face(Vector3(1, 1, -1), Vector3(-1, 1, -1), Vector3(-1, -1, -1), Vector3(1, -1, -1)),
										   Face(Vector3(-1, 1, -1), Vector3(-1, 1, 1), Vector3(-1, -1, 1), Vector3(-1, -1, -1))});
	
	object->Move(spawninfo.location);
	object->ScaleTo(100.0f);
	
}



