#pragma once

#include "Character.hpp"
#include "ObjectPoints.hpp"
#include "SimulationState.hpp"
#include "SpawnInfoManager.hpp"
#include <list>
#include "Object.hpp"
#include "Overworld.hpp"
#include "Enemy.hpp"
#include <deque>
#include <iostream>

#define M_PI 3.14159265359f

class SpawnInfoManager;
class ObjectPoints;
class Overworld;
class Character;
class Enemy;

class Simulation {
public:
	Simulation();
	void Run();
	void Update();
	void Draw();
	Vector2 DrawApplyPerspective(Vector3 point, Vector3 camPos, Vector3 rotation);
	void DrawLoad(ObjectPoints* objectPoints);

	SpawnInfoManager* spawnInfoManager;
	SimulationState state = SimulationState::Level1;
	Overworld* world;
	Character* character;

	float drawDistance = 100.0f;
	bool simulationRunning = true ;
	int time = 0;
	int delta = 1000;
	std::vector<ObjectPoints*> loadObjectPoints;
	std::list<Enemy*> enemies;

};