#include "Simulation.hpp"
#include "SpawnInfoManager.hpp"
#include "Camera.hpp"
#include "Character.hpp"
#include "Boss.hpp"
#include "Sprite.hpp"
#include "ObjectLine.hpp"
#include "ObjectSprite.hpp"
#include "ObjectPoints.hpp"
#include "Overworld.hpp"
#include "BeatmapManager.hpp"
#include "Bullet.hpp"

Simulation::Simulation() 
	: time(5000),
	timeEnd(10000), 
	delta(200), 
	dps((float)delta / 1000), 
	state(SimulationState::Level1), 
	simulationRunning(true) {

	spawnInfoManager = new SpawnInfoManager(this);
	world = new Overworld(this);
	character = new Character(this);
	camera = character->camera;

	for (int i = 0; i < 9; ++i) {
		Overworld* overworld = new Overworld(this);
		overworld->objectPoints->Move(Vector3(-200, 200, 0));
		overworld->objectPoints->Move(Vector3(200 * (i / 3), -200 * (i % 3), 0));
		overworld->objectPoints->Color(Color(rand() % 255, rand() % 255, rand() % 255));
		testWorlds.push_back(overworld);
	}
}

void Simulation::Run() {
	while (simulationRunning) {
		std::cout << "Processing: " << time << std::endl;

		Update();
		UpdateDelete();
		Draw();
		DrawRender();

		time += delta;
		if (time > timeEnd) {
			simulationRunning = false;
		}
	}
}

void Simulation::Update() {
	if (state == SimulationState::Level1) {
		//spawnInfoManager->Process(time);
		beatmapManager->Process();

		world->objectPoints->RotateX(M_PI / 10);

		//camera->RotateX(M_PI / 4);
		//camera->RotateY(M_PI / 4);
		//camera->Move(Vector3(0, 0, -10));

		for (auto bullet : bullets) {
			bullet->Update();
		}
	}
}

void Simulation::UpdateDelete() {
	for (auto bullet : bulletsToDelete) {
		bullets.remove(bullet);
	}
	bulletsToDelete.clear();

	for (auto enemy : enemies) {
		enemy->Update();
	}
	for (auto marked : enemiesToDelete) {
		enemies.remove(marked);
	}
	enemiesToDelete.clear();
}

void Simulation::DrawLoad(ObjectPoints* objectPoints) {
	loadObjectPoints.push_back(objectPoints);
}

void Simulation::Draw() {
	for (auto enemy : enemies) {
		enemy->Draw();
	}

	for (auto bullet : bullets) {
		bullet->Draw();
	}

	character->Draw();

	//world->objectPoints->Draw();

	//for (auto world : testWorlds) {
	//	world->objectPoints->Draw();
	//}
}

void Simulation::DrawRender() {
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
				Sprite* sprite = objectSprite->sprite;
				Vector3 startCamCon = camera->ConvertPoint(*objectLines[i]->start, camPos, camRot);
				Vector3 endCamCon = camera->ConvertPoint(*objectLines[i]->end, camPos, camRot);

				//If both points are behind camera, don't draw it
				if (startCamCon.z >= 0 && endCamCon.z >= 0) {
					sprite->Fade(time, time, 0.0f, 0.0f);
					objectSprite->reset = true;
					continue;
				}

				Vector2 startPoint = camera->ApplyPerspective(startCamCon, endCamCon);
				Vector2 endPoint = camera->ApplyPerspective(endCamCon, startCamCon);
				Vector2 diff = endPoint - startPoint;
				float additionalRot = Vector2(sprite->rotation).AngleBetween(diff);
				float dist = diff.Magnitude();
				if (objectSprite->reset) {
					sprite->Fade(time, time, 1.0f, 1.0f);
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