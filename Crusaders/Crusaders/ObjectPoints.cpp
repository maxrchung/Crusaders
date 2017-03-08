#include "ObjectPoints.hpp"
#include "ObjectFace.hpp"
#include "Line.hpp"
#include "ObjectLine.hpp"
#include "ObjectSprite.hpp"
#include "Simulation.hpp"

ObjectPoints::ObjectPoints(Simulation* simulation, std::vector<Face> faces)
	: simulation(simulation) {
	// For calculating center
	Vector3 total = Vector3::Zero;
	int counter = 0;

	for (auto face : faces) {
		// Setup face
		ObjectFace* objectFace = new ObjectFace();

		for (auto point : face.points) {
			// Setup points
			Vector3* checkExistingPoint = NULL;
			for (auto objectPoint : objectPoints) {
				if (point == *objectPoint) {
					checkExistingPoint = objectPoint;
					break;
				}
			}

			if (!checkExistingPoint) {
				checkExistingPoint = new Vector3(point);
				objectPoints.push_back(checkExistingPoint);
			}

			objectFace->objectPoints.push_back(checkExistingPoint);

			total += point;
			counter++;
		}

		objectFaces.push_back(objectFace);

		// Setup lines
		for (int i = 0; i < objectFace->objectPoints.size(); ++i) {
			int nextIndex = (i + 1) % objectFace->objectPoints.size();
			Line line = Line(*objectFace->objectPoints[i], *objectFace->objectPoints[nextIndex]);

			ObjectLine* checkExistingLine = NULL;
			for (auto objectLine : objectLines) {
				if ((line.start == *objectLine->start && line.end == *objectLine->end) ||
					(line.end == *objectLine->start && line.start == *objectLine->end)) {
					checkExistingLine = objectLine;
					break;
				}
			}

			if (!checkExistingLine) {
				Vector3* startPoint = NULL;
				Vector3* endPoint = NULL;
				for (auto objectPoint : objectPoints) {
					if (line.start == *objectPoint) {
						startPoint = objectPoint;
					}
					else if (line.end == *objectPoint) {
						endPoint = objectPoint;
					}
				}

				if (!startPoint || !endPoint) {
					throw "Cannot find point!";
				}

				checkExistingLine = new ObjectLine(startPoint, endPoint);
				objectLines.push_back(checkExistingLine);
			}
		}

	}

	// Setup sprites
	for (auto objectLine : objectLines) {
		objectSprites.push_back(new ObjectSprite(new Sprite("dot.png", Vector2::Zero, Layer::Foreground, Origin::CentreLeft)));
	}

	center = total / counter;
}

void ObjectPoints::Move(Vector3 move) {
	move *= simulation->dps;
	center += move;

	for (auto objectPoint : objectPoints) {
		*objectPoint += move;
	}
}

void ObjectPoints::MoveTo(Vector3 moveTo) {
	Vector3 move = moveTo - center;
	center = moveTo;

	for (auto objectPoint : objectPoints) {
		*objectPoint += move;
	}
}

// Be careful of simulation->dps reducing rotations
void ObjectPoints::Rotate(float rotateX, float rotateY, float rotateZ) {
	rotateX *= simulation->dps;
	rotateY *= simulation->dps;
	rotateZ *= simulation->dps;
	
	rotation += Vector3(rotateX, rotateY, rotateZ);

	for (auto objectPoint : objectPoints) {
		Vector3 local = *objectPoint - center;
		Vector3 localRotated = local.Rotate(rotateX, rotateY, rotateZ);
		Vector3 offsetPos = localRotated + center;
		*objectPoint = offsetPos;
	}
}

void ObjectPoints::Rotate(Vector3 rotate) {
	Rotate(rotate.x, rotate.y, rotate.z);
}

void ObjectPoints::RotateX(float rotateX) {
	Rotate(rotateX, 0, 0);
}

void ObjectPoints::RotateY(float rotateY) {
	Rotate(0, rotateY, 0);
}

void ObjectPoints::RotateZ(float rotateZ) {
	Rotate(0, 0, rotateZ);
}

void ObjectPoints::RotateTo(Vector3 rotationTo) {
	// Need to add simulation->dps so we don't have reduced values
	Rotate(-rotation * simulation->dps);
	Rotate(rotationTo * simulation->dps);
}

void ObjectPoints::Scale(float scale) {
	scale *= simulation->dps;
	for (auto objectPoint : objectPoints) {
		*objectPoint = (*objectPoint - center) * scale + center;
	}
}

void ObjectPoints::ScaleTo(float scaleTo) {
	scaleTo *= simulation->dps;
	for (auto objectPoint : objectPoints) {
		*objectPoint = (*objectPoint - center).Normalize() * scaleTo + center;
	}
}

void ObjectPoints::Color(::Color color) {
	for (auto objectSprite : objectSprites) {
		objectSprite->sprite->Color(simulation->time, simulation->time, color, color);
	}
}

void ObjectPoints::Color(int startTime, int endTime, ::Color startColor, ::Color endColor) {
	for (auto objectSprite : objectSprites) {
		objectSprite->sprite->Color(startTime, endTime, startColor, endColor);
	}
}

void ObjectPoints::Fade(float fade) {
	for (auto objectSprite : objectSprites) {
		objectSprite->sprite->Fade(simulation->time, simulation->time, fade, fade);
	}
}

void ObjectPoints::Fade(int startTime, int endTime, float startFade, float endFade) {
	for (auto objectSprite : objectSprites) {
		objectSprite->sprite->Fade(startTime, endTime, startFade, endFade);
	}
}

void ObjectPoints::Draw() {
	simulation->DrawLoad(this);
}