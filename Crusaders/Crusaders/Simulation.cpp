#include "Simulation.hpp"
#include "Storyboard.hpp"
#include "Overworld.hpp"
#include "ObjectPoints.hpp"

Simulation::Simulation() {
	// Probably where you want to initialize everything
	spawnInfoManager = new SpawnInfoManager(this);

	// new world
	world = new Overworld(this);
	character = new Character(this);
}

void Simulation::Run() {
	while (simulationRunning) {
		std::cout << "Processing: " << time << std::endl;

		Update();
		Draw();

		time += delta;
		if (time > timeEnd) {
			simulationRunning = false;
		}
	}
}

void Simulation::Update() {
	if (state == SimulationState::Intro) {
	}

	else if (state == SimulationState::Level1) {
		spawnInfoManager->Process(time);

		world->objectPoints->RotateX(M_PI / 10);
		character->direction.RotateX(M_PI / 100);
	}
}

void Simulation::Draw() {
	// draw all objects
	world->objectPoints->Draw();

	Vector3 camPos = character->position;
	Vector3 camDir = character->direction;

	// http://stackoverflow.com/questions/21622956/how-to-convert-direction-vector-to-euler-angles
	// Be careful using the above. It's okay in explaining some of the theory,
	// but the axes work very differently OsuukiSB.
	float heading = atan2(camDir.x, -camDir.z);
	float pitch = asin(camDir.y);
	float bank = 0;
	Vector3 camRot = Vector3(-pitch, -heading, -bank);

	if (state == SimulationState::Intro) {

	}

	else if (state == SimulationState::Level1) {
		for (auto objectPoints : loadObjectPoints) {
			auto& objectLines = objectPoints->objectLines;
			auto& sprites = objectPoints->sprites;
			for (int i = 0; i < objectLines.size(); ++i) {
				Vector2 startPoint = DrawApplyPerspective(*objectLines[i]->start, camPos, camRot);
				Vector2 endPoint = DrawApplyPerspective(*objectLines[i]->end, camPos, camRot);
				sprites[i]->Move(time, time + delta, sprites[i]->position, startPoint);

				Vector2 diff = endPoint - startPoint;
				float additionalRot = Vector2(sprites[i]->rotation).AngleBetween(diff);
				sprites[i]->Rotate(time, time + delta, sprites[i]->rotation, sprites[i]->rotation + additionalRot);

				float dist = diff.Magnitude();
				sprites[i]->ScaleVector(time, time + delta, sprites[i]->scaleVector, Vector2(dist, 1));
			}
		}
	}

	loadObjectPoints.clear();
}

Vector2 Simulation::DrawApplyPerspective(Vector3 point, Vector3 camPos, Vector3 camRot)
{
	Vector3 diff = point - camPos;
	Vector3 camCoor = diff.Rotate(camRot.x, camRot.y, camRot.z);
	return camCoor.Perspect(0, drawDistance);
}


void Simulation::DrawLoad(ObjectPoints* objectPoints)
{
	loadObjectPoints.push_back(objectPoints);
}
