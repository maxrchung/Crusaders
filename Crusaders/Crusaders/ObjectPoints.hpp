#pragma once

#include "Face.hpp"
#include "Simulation.hpp"
#include <vector>

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
	std::vector<Face> faces;
	Vector3 center;
};
