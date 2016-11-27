#include "Enemy.hpp"
#include "ObjectPoints.hpp"
#include "Simulation.hpp"

Enemy::Enemy(Simulation* simulation, SpawnInfo spawninfo)
	: simulation(simulation), spawninfo(spawninfo) {
	object = new ObjectPoints(simulation, {Face(Vector3(-1, 1, 1), Vector3(1, 1, 1), Vector3(1, -1, 1), Vector3(-1, -1, 1)),
										   Face(Vector3(1, 1, 1), Vector3(1, 1, -1), Vector3(1, -1, -1), Vector3(1, -1, 1)),
										   Face(Vector3(1, 1, -1), Vector3(-1, 1, -1), Vector3(-1, -1, -1), Vector3(1, -1, -1)),
										   Face(Vector3(-1, 1, -1), Vector3(-1, 1, 1), Vector3(-1, -1, 1), Vector3(-1, -1, -1))});
	
	object->Move(spawninfo.location);
	object->ScaleTo(50.0f);
}

void Enemy::Update() {
	health--; // to check death animation: remove this later
	if (health == 0) {
		Enemy::state = EnemyState::Dying;
	}

	if (Enemy::state == EnemyState::Idle) {
		object->RotateY(M_PI / 3);
		

	}
	else if (Enemy::state == EnemyState::Dying) {
		temp_time += object->simulation->delta;
		if (temp_time < 1000) {
			object->Rotate(M_PI * 3.5, M_PI * 3.5, M_PI * 3.5);
		}
		else {
			simulation->delete_list.push_back(this);
		}
	}



}

void Enemy::Draw() {
	simulation->DrawLoad(object);
}
