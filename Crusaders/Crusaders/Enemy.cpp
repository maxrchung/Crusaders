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
	// set state = idle
}

void Enemy::Update() {
	// if spawn state:
	// start spawn
	// if idle state:
	// rotate X amount every frame
	// if dying:
	// then do what is necessary for death
	if (Enemy::state == EnemyState::Idle) {

	}



}

void Enemy::Draw() {
	simulation->DrawLoad(object);
}
