#pragma once

#include "Face.hpp"
#include "Line.hpp"
#include "ObjectLine.hpp"
#include "ObjectFace.hpp"
#include "Simulation.hpp"
#include "Sprite.hpp"
#include <vector>
#include <unordered_set>

class Simulation;

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
	std::vector<Sprite*> sprites;

	Vector3 center;
};
