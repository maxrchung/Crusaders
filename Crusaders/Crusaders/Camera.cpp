#include "Camera.hpp"
#include "ObjectPoints.hpp"
#include "Simulation.hpp"
#include "Character.hpp"

Camera::Camera(Simulation* simulation, Vector3 position, Vector3 direction)
	: simulation(simulation), position(position), direction(direction) {
}

void Camera::Move(Vector3 move) {
	simulation->character->gun->Move(move); //multiplying dps twice causes this not to move
	move *= simulation->dps;
	position += move;
}

void Camera::MoveTo(Vector3 moveTo) {
	moveTo *= simulation->dps;
	position = moveTo * simulation->dps;
}

void Camera::Rotate(float rotateX, float rotateY, float rotateZ) {
	//std::cout << localVector.x << " " << localVector.y << " " << localVector.z << std::endl;
	direction = direction.Rotate(rotateX, rotateY, rotateZ).Normalize();
	simulation->character->gun->Rotate(rotateX, -rotateY, -rotateZ);//.Normalize();
	Vector3 local = simulation->character->gun->center - position;
	Vector3 localRotated = local.Rotate(rotateX, -rotateY, -rotateZ);
	Vector3 offsetPos = position + localRotated;
	simulation->character->gun->MoveTo(offsetPos);

}

void Camera::RotateX(float rotateX) {
	rotateX *= simulation->dps;
	Rotate(rotateX, 0, 0);
}

void Camera::RotateY(float rotateY) {
	rotateY *= simulation->dps;
	Rotate(0, rotateY, 0);
}

void Camera::RotateZ(float rotateZ) {
	rotateZ *= simulation->dps;
	Rotate(0, 0, rotateZ);
}

Vector3 Camera::ConvertPoint(Vector3 point, Vector3 camPos, Vector3 camRot) {
	Vector3 diff = point - camPos;
	Vector3 camCoor = diff.Rotate(camRot.x, camRot.y, camRot.z);
	return camCoor;
}

Vector2 Camera::ApplyPerspective(Vector3 pointToPerspect, Vector3 otherPoint) {
	if (pointToPerspect.z < 0) {
		Vector2 perspected = pointToPerspect.Perspect(0, drawDistance);
		return perspected;
	}
}