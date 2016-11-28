#include "Boss.hpp"
#include "ObjectPoints.hpp"
#include "Simulation.hpp"

Boss::Boss(Simulation* simulation, SpawnInfo spawnInfo) {
	this->simulation = simulation;
	this->spawninfo = spawnInfo;
	object = new ObjectPoints(simulation, {Face(Vector3(-1, 1, 1), Vector3(1, 1, 1), Vector3(1, -1, 1), Vector3(-1, -1, 1)),
										   Face(Vector3(1, 1, 1), Vector3(1, 1, -1), Vector3(1, -1, -1), Vector3(1, -1, 1)),
										   Face(Vector3(1, 1, -1), Vector3(-1, 1, -1), Vector3(-1, -1, -1), Vector3(1, -1, -1)),
										   Face(Vector3(-1, 1, -1), Vector3(-1, 1, 1), Vector3(-1, -1, 1), Vector3(-1, -1, -1))});

	object->Move(spawninfo.location);
	object->ScaleTo(100.0f);
	health = 20;
}

void Boss::Update() {
	health--;
	if (health == 0) {
		state = EnemyState::Dying;
	}

	if (state == EnemyState::Idle) {
		object->RotateX(M_PI / 3);
	}
	else if (state == EnemyState::Dying) {
		temp_time += object->simulation->delta;
		if (temp_time < 1000) {
			object->Rotate(M_PI * 3.5, M_PI * 3.5, M_PI * 3.5);
		}
		else {
			simulation->enemiesToDelete.push_back(this);
		}
	}
}


void Boss::Draw() {
	simulation->DrawLoad(object);
}
