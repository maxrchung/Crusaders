#include "Simulation.hpp"
#include "Overworld.cpp"
#include "ObjectPoints.cpp"

Simulation::Simulation() {
	// Probably where you want to initialize everything
	spawnInfoManager = new SpawnInfoManager(this);

	// new world
	world = new Overworld();
	

}

void Simulation::Run() {
	while (simulationRunning) {

		Update();
		Draw();

		time += timePerFrame;
	}
}

void Simulation::Update() {
	if (state == SimulationState::Intro) {

	}

	else if (state == SimulationState::Level1) {
		spawnInfoManager->Process(time);

		// move all objects
		// do logic here
	}
}

void Simulation::Draw() {
	if (state == SimulationState::Intro) {

	}

	else if (state == SimulationState::Level1) {
		// draw all objects
	}
}