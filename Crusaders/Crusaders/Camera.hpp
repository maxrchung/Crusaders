#pragma once

#include "Simulation.hpp"
#include "Vector3.hpp"

class Simulation;

class Camera {
public:
	Camera(Simulation* simulation, Vector3 position = Vector3::Zero, Vector3 direction = Vector3(0, 0, -1));

	void Move(Vector3 move);
	void MoveTo(Vector3 moveTo);

	void Rotate(float rotateX, float rotateY, float rotateZ);
	void RotateX(float rotateX);
	void RotateY(float rotateY);
	void RotateZ(float rotateZ);

	Vector3 ConvertPoint(Vector3 point, Vector3 camPos, Vector3 rotation);
	// We need otherPoint so we can calculate a projection to the drawDistance if necessary
	Vector2 ApplyPerspective(Vector3 pointToPerspect, Vector3 otherPoint);

	Vector3 localVector;
	Vector3 position;
	Vector3 direction;
	Simulation* simulation;
	float drawDistance = 200.0f;
};