#include "Beatmap.hpp"
#include "Camera.hpp"
#include "Log.hpp"
#include "ObjectLine.hpp"
#include "ObjectSprite.hpp"
#include "ObjectPoints.hpp"
#include "Path.hpp"
#include "Simulation.hpp"
#include "Sprite.hpp"

Simulation::Simulation(Path* path) 
	: time(0), timeEnd(30000), delta(200), dps((float)delta / 1000), state(SimulationState::Level1), simulationRunning(true), path(path), markerDistance(10000.0f), cameraHeight(5000.0f), log(new Log) {
	camera = new Camera(this);
	// Rotate 180
	// Make sure to multiply by dps so we account for time
	camera->RotateY(M_PI / dps);

	Vector3 camPos(0, cameraHeight / dps, time / dps);
	camera->MoveTo(camPos);

	// Fill markers
	for (auto marker : path->markers) {
		marker->setObjectPoints(this);
		remainingMarkers.push(marker);
	}
	fillCurrentMarkers();
}

void Simulation::Run() {
	while (simulationRunning) {
		std::cout << "Processing: " << time << std::endl;

		Update();
		Draw();
		DrawRender();

		time += delta;
		if (time > timeEnd) {
			simulationRunning = false;
		}
	}
}

void Simulation::Update() {
	Vector3 camPos(0, cameraHeight, time / dps);
	camera->MoveTo(camPos);

	while (!currentMarkers.empty()) {
		Marker* marker = currentMarkers.front();
		if (marker->position.z <= camera->position.z) {
			marker->objectPoints->Fade(0.0f);
			currentMarkers.pop_front();
		}
		else {
			break;
		}
	}

	fillCurrentMarkers();
}

void Simulation::DrawLoad(ObjectPoints* objectPoints) {
	loadObjectPoints.push_back(objectPoints);
}

void Simulation::Draw() {
	for (auto marker : currentMarkers) {
		DrawLoad(marker->objectPoints);
	}
}

void Simulation::DrawRender() {
	// http://stackoverflow.com/questions/21622956/how-to-convert-direction-vector-to-euler-angles
	// Be careful using the above. It's okay in explaining some of the theory,
	// but the axes are not the same.
	// The above is still a good reference, but having to take care of a lot of wanky cases
	// when angles are negative can be really difficult. I decided to make my life easy to track
	// both a direction Vector3 and also the actual rotation amounts with directionRotations.
	Vector3 camPos = camera->position;
	Vector3 camRot = camera->directionRotations;

	for (auto objectPoints : loadObjectPoints) {
		auto& objectLines = objectPoints->objectLines;
		auto& objectSprites = objectPoints->objectSprites;
		for (int i = 0; i < objectLines.size(); ++i) {
			ObjectSprite* objectSprite = objectSprites[i];
			Sprite* sprite = objectSprite->sprite;
			Vector3 startCamCon = camera->ConvertPoint(*objectLines[i]->start, camPos, camRot);
			Vector3 endCamCon = camera->ConvertPoint(*objectLines[i]->end, camPos, camRot);
			Vector2 startPoint = camera->ApplyPerspective(startCamCon, endCamCon);
			Vector2 endPoint = camera->ApplyPerspective(endCamCon, startCamCon);
			Vector2 diff = endPoint - startPoint;
			float additionalRot = Vector2(sprite->rotation).AngleBetween(diff);
			float dist = diff.Magnitude();
			if (objectSprite->reset) {
				//sprite->Fade(time, time, 1.0f, 1.0f);
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
	loadObjectPoints.clear();
}

void Simulation::fillCurrentMarkers() {
	// May need to do some kind of snaking calculation that sums all marker distances passed
	while (!remainingMarkers.empty()) {
		Vector3 distance = remainingMarkers.front()->position - camera->position;
		float magnitude = distance.Magnitude();

		if (magnitude <= markerDistance) {
			currentMarkers.push_back(remainingMarkers.front());
			remainingMarkers.pop();
		}
		else {
			break;
		}
	}
}