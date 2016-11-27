#pragma once

#define M_PI 3.14159265359f

class SpawnInfoManager;
class ObjectPoints;
class Overworld;
class Camera;
class Character;
class Enemy;

#include "SimulationState.hpp"
#include <iostream>
#include <list>
#include <vector>

class Simulation {
public:
	Simulation();
	void Run();
	void Update();
	void Draw();

	void DrawLoad(ObjectPoints* objectPoints);

	SpawnInfoManager* spawnInfoManager;
	SimulationState state = SimulationState::Level1;
	Overworld* world;
	Character* character;
	Camera* camera;

	bool simulationRunning = true ;
	int time = 0;
	int timeEnd = 5000;
	int delta = 200;
	// Need for correct calculation independent of framerate
	float dps = float(delta) / 1000;
	std::vector<ObjectPoints*> loadObjectPoints;
	std::list<Enemy*> enemies;
	std::list<Enemy*> delete_list;

	std::vector<Overworld*> testWorlds;
};