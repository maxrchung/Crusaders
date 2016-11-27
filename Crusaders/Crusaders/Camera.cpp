#include "Camera.hpp"

Camera::Camera(Simulation* simulation, Vector3 position, Vector3 direction)
	: simulation(simulation), position(position), direction(direction), drawDistance(1.0f) {
}

void Camera::Move(Vector3 move) {
	move *= simulation->dps;
	position += move;
}

void Camera::MoveTo(Vector3 moveTo) {
	moveTo *= simulation->dps;
	position = moveTo * simulation->dps;
}

void Camera::Rotate(float rotateX, float rotateY, float rotateZ) {
	direction = direction.Rotate(rotateX, rotateY, rotateZ).Normalize();
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
	Rotate(0, 0, rotateZ);
}

Vector3 Camera::ConvertPoint(Vector3 point, Vector3 camPos, Vector3 camRot) {
	Vector3 diff = point - camPos;
	Vector3 camCoor = diff.Rotate(camRot.x, camRot.y, camRot.z);
	return camCoor;
}

Vector2 Camera::ApplyPerspective(Vector3 point, Vector3 other) {
	if (point.z < 0) {
		Vector2 perspected = point.Perspect(0, drawDistance);
		return perspected;
	}
	//else {
	//	if (other.z <= -drawDistance) {
	//		Vector2 projectedNear = ProjectNear(point, other);
	//		return projectedNear;
	//	}
	//}
}

Vector2 Camera::ProjectNear(Vector3 behind, Vector3 far) {
	Vector3 originalFar = far;

	// Switch the Z axis so perspective projection is pointed towards -Z
	float projectDistance = 0.01f;
	behind.z *= -1;
	far.z *= -1;

	// Move so that far is at 0,0,0
	projectDistance -= far.z;
	behind -= far;
	far -= far;

	Vector2 perspected = behind.Perspect(0, projectDistance);
	Vector3 projectedNear = originalFar - Vector3(perspected.x, perspected.y, projectDistance);

	return Vector2(projectedNear.x, projectedNear.y);
}