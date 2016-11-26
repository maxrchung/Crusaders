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
	camera = character->camera;
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
	if (state == SimulationState::Level1) {
		spawnInfoManager->Process(time);

		world->objectPoints->RotateX(M_PI / 10);
		character->camera->RotateX(M_PI / 2);
		character->camera->RotateY(M_PI / 4);

	}
}

void Simulation::Draw() {
	// draw all objects
	world->objectPoints->Draw();

	// http://stackoverflow.com/questions/21622956/how-to-convert-direction-vector-to-euler-angles
	// Be careful using the above. It's okay in explaining some of the theory,
	// but the axes are not the same in OsuukiSB.
	Vector3 camPos = camera->position;
	Vector3 camDir = camera->direction;
	float heading = atan2(camDir.x, -camDir.z);
	float pitch = asin(camDir.y);
	float bank = 0;
	Vector3 camRot = Vector3(-pitch, -heading, -bank);

	if (state == SimulationState::Level1) {
		for (auto objectPoints : loadObjectPoints) {
			auto& objectLines = objectPoints->objectLines;
			auto& objectSprites = objectPoints->objectSprites;
			for (int i = 0; i < objectLines.size(); ++i) {
				ObjectSprite* objectSprite = objectSprites[i];
				Vector3 startCamCon = camera->ConvertPoint(*objectLines[i]->start, camPos, camRot);
				Vector3 endCamCon = camera->ConvertPoint(*objectLines[i]->end, camPos, camRot);

				// If both points are behind camera, don't draw it
				if (startCamCon.z >= 0 || endCamCon.z >= 0) {
					objectSprite->reset = true;
					continue;
				}

				Sprite* sprite = objectSprite->sprite;
				Vector2 startPoint = camera->ApplyPerspective(startCamCon, endCamCon);
				Vector2 endPoint = camera->ApplyPerspective(endCamCon, startCamCon);
				Vector2 diff = endPoint - startPoint;
				float additionalRot = Vector2(sprite->rotation).AngleBetween(diff);
				float dist = diff.Magnitude();

				if (objectSprite->reset) {
					sprite->Move(time, time + delta, startPoint, startPoint);
					sprite->Rotate(time, time + delta, sprite->rotation + additionalRot, sprite->rotation + additionalRot);
					sprite->ScaleVector(time, time + delta, Vector2(dist, 1), Vector2(dist, 1));
					objectSprite->reset = false;
				}
				else {
					sprite->Move(time, time + delta, sprite->position, startPoint);
					sprite->Rotate(time, time + delta, sprite->rotation, sprite->rotation + additionalRot);
					sprite->ScaleVector(time, time + delta, sprite->scaleVector, Vector2(dist, 1));
				}
			}
		}
	}

	loadObjectPoints.clear();
}


void Simulation::DrawLoad(ObjectPoints* objectPoints)
{
	loadObjectPoints.push_back(objectPoints);
}
