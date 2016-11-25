#include "Simulation.hpp"
#include "Storyboard.hpp"
#include "Overworld.hpp"
#include "ObjectPoints.hpp"

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

		time += delta;
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
		//// Convert point to camera's coordinate position
		//Vector3 cameraPosition;
		//// Must be normalzied
		//Vector3 cameraDirection;
		//Vector3 cameraUp;

		//float heading = atan2(cameraDirection.x, cameraDirection.y);
		//float pitch = asin(cameraPosition.z);
		//float bank = 0;

		// draw all objects

		for (auto objectPoints : loadObjectPoints) {
			auto& objectLines = objectPoints->objectLines;
			auto& sprites = objectPoints->sprites;
			for (int i = 0; i < objectLines.size(); ++i) {
				Vector2 startPoint = objectLines[i]->start->Perspect(0, 200);
				Vector2 endPoint = objectLines[i]->end->Perspect(0, 200);
				sprites[i]->Move(time, time + delta, sprites[i]->position, startPoint);

				Vector2 diff = endPoint - startPoint;
				float additionalRot = Vector2(sprites[i]->rotation).AngleBetween(diff);
				sprites[i]->Rotate(time, time + delta, sprites[i]->rotation, sprites[i]->rotation + additionalRot);

				float dist = diff.Magnitude();
				sprites[i]->ScaleVector(time, time + delta, sprites[i]->scaleVector, Vector2(dist, 1));
			}
		}
	}
}

void Simulation::LoadDraw(ObjectPoints* objectPoints)
{
	loadObjectPoints.push_back(objectPoints);
}
