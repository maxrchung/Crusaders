#pragma once

#include "Camera.hpp"
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
#include "BeatmapManager.hpp"
#include "Bullet.hpp"

#define M_PI 3.14159265359f

class SpawnInfoManager;
class ObjectPoints;
class Overworld;
class Camera;
class Character;
class Enemy;
class BeatmapManager;
class Bullet;

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
	BeatmapManager* beatmapManager;

	bool simulationRunning = true ;
	int time = 0;
	int timeEnd = 5000;
	int delta = 200;
	// Need for correct calculation independent of framerate
	float dps = float(delta) / 1000;
	std::vector<ObjectPoints*> loadObjectPoints;
	std::vector<Bullet*> bulletList;
	std::list<Enemy*> enemies;

};