#include "Camera.hpp"
#include "ObjectPoints.hpp"
#include "Simulation.hpp"

Camera::Camera(Simulation* simulation, Vector3 position, Vector3 direction) 
	: simulation(simulation), position(position), direction(direction), directionRotations(Vector3::Zero), fieldOfView(M_PI * 0.95f), screenMultiplier(Vector2::ScreenSize.x) {
	drawDistance = 1 / (tanf(fieldOfView / 2));
}

void Camera::Move(Vector3 move) {
	// Must be careful not to affect dps twice
	move *= simulation->dps;
	position += move;
}

void Camera::MoveTo(Vector3 moveTo) {
	moveTo *= simulation->dps;
	position = moveTo * simulation->dps;
}

void Camera::Rotate(float rotateX, float rotateY, float rotateZ) {
	rotateX *= simulation->dps;
	rotateY *= simulation->dps;
	rotateZ *= simulation->dps;

	direction = direction.Rotate(rotateX, rotateY, rotateZ).Normalize();
	directionRotations += Vector3(rotateX, rotateY, rotateZ);
}

void Camera::RotateX(float rotateX) {
	Rotate(rotateX, 0, 0);
}

void Camera::RotateY(float rotateY) {
	Rotate(0, rotateY, 0);
}

void Camera::RotateZ(float rotateZ) {
	Rotate(0, 0, rotateZ);
}

Vector3 Camera::ConvertPoint(Vector3 point, Vector3 camPos, Vector3 camRot) {
	Vector3 diff = point - camPos;
	Vector3 camCoor = diff.Rotate(-camRot.x, -camRot.y, -camRot.z);
	return camCoor;
}

Vector2 Camera::ApplyPerspective(Vector3 point, Vector3 other) {
	if (point.z < 0) {
		Vector2 perspected = point.Perspect(0, drawDistance);
		Vector2 screenPoints = perspected * Vector2(Vector2::ScreenSize.x, Vector2::ScreenSize.x);
		return screenPoints;
	}
	else {
		Vector2 projectedNear = ProjectNear(point, other);
		Vector2 screenPoints = projectedNear * Vector2(Vector2::ScreenSize.x, Vector2::ScreenSize.x);
		return screenPoints;
	}
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