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

	void Move(Vector3 move);
	void MoveTo(Vector3 moveTo);

	void Rotate(float rotateX, float rotateY, float rotateZ);
	void RotateX(float rotateX);
	void RotateY(float rotateY);
	void RotateZ(float rotateZ);


	void Scale(float scale);
	void ScaleTo(float scaleTo);

	void Draw();

	Simulation* simulation;

	std::vector<Vector3*> objectPoints;
	std::vector<ObjectLine*> objectLines;
	std::vector<ObjectFace*> objectFaces;
	std::vector<Sprite*> sprites;

	Vector3 center;
};
