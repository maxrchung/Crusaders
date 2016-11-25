#pragma once

class Character
{
public:
	Character(Simulation* sim);
	//will contain a Camera object
	//will contain gun ObjecT?
	Vector3 getPosition();

	void setPosition(Vector3 newPosition);
	void shoot();
	void Update();
	void spawnBullets();

	float enemyDistance(Vector3 enemyVector);

private:
	Vector3 position = Vector3(0, 0, 0);
	CharacterState state = CharacterState::Idle;

	int bulletcount;
	int health;
	Simulation* simulation;


	//some structure to hold monsters in sight of char, <DEQUE> OF TYPE OBJECT*

	//some ray-casted line, using projection, which exists in OsuukiSB

};