#pragma once

class ObjectFace;
class ObjectLine;
class ObjectSprite;
class Simulation;

#include "Face.hpp"
#include "Sprite.hpp"
#include <unordered_set>
#include <vector>

class ObjectPoints {
public:
	ObjectPoints(Simulation* simulation, std::vector<Face> faces);

	// Local
	void Move(Vector3 move);
	// Global
	void MoveTo(Vector3 moveTo);

	// Local
	void Rotate(float rotateX, float rotateY, float rotateZ);
	// Local
	void RotateX(float rotateX);
	// Local
	void RotateY(float rotateY);
	// Local
	void RotateZ(float rotateZ);

	// Local
	void Scale(float scale);
	// Global
	void ScaleTo(float scaleTo);

	void Draw();

	Simulation* simulation;

	std::vector<Vector3*> objectPoints;
	std::vector<ObjectLine*> objectLines;
	std::vector<ObjectFace*> objectFaces;
	std::vector<ObjectSprite*> objectSprites;

	Vector3 center;
};
