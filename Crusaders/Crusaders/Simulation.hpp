#pragma once
#define M_PI 3.14159265359f

class SpawnInfoManager;
class ObjectPoints;
class Overworld;
class Camera;
class Character;
class Enemy;
class BeatmapManager;
class Bullet;

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
	SimulationState state;
	Overworld* world;
	Character* character;
	Camera* camera;
	BeatmapManager* beatmapManager;

	bool simulationRunning;
	int time;
	int timeEnd;
	int delta;
	// Need for correct calculation independent of framerate
	float dps;
	// In every frame, loadObjectPoints will be loaded by classes
	// Then, Simulation will draw the objects
	// Once Simulation finishes drawing, it clears this data structure for the next frame
	std::vector<ObjectPoints*> loadObjectPoints;
	std::vector<Bullet*> bulletList;
	std::list<Enemy*> enemies;
	std::list<Enemy*> delete_list;

	std::vector<Overworld*> testWorlds;
};