#pragma once

class Simulation;

#include "Vector3.hpp"

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
	// We need other so we can calculate a projection to the drawDistance if necessary
	Vector2 ApplyPerspective(Vector3 point, Vector3 other);
	Vector2 ProjectNear(Vector3 behind, Vector3 far);

	Vector3 position;
	// Unit vector pointing in camera's direction
	Vector3 direction;
	// The x, y, and z rotations to get to the direction Vector3
	Vector3 directionRotations;
	Simulation* simulation;
	float drawDistance;
	float fieldOfView;
	float screenMultiplier;
};