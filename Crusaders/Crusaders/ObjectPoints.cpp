#include "ObjectPoints.hpp"

ObjectPoints::ObjectPoints(Simulation* simulation, std::vector<Face> faces)
	: simulation(simulation), faces(faces) {
	Vector3 total = Vector3::Zero;
	int counter = 0;
	for (auto face : faces) {
		for (auto point : face.points) {
			total += point;
			counter++;
		}
	}

	center = total / counter;
}

void ObjectPoints::Move(Vector3 move) {
	center += move;

	for (auto& face : faces) {
		for (auto& point : face.points) {
			point += move;
		}
	}
}

void ObjectPoints::MoveTo(Vector3 moveTo) {
	Vector3 move = moveTo - center;
	center = moveTo;

	for (auto& face : faces) {
		for (auto& point : face.points) {
			point += move;
		}
	}

}

void ObjectPoints::Rotate(float rotateX, float rotateY, float rotateZ) {
	for (auto& face : faces) {
		for (auto& point : face.points) {
			point = (point - center).Rotate(rotateX, rotateY, rotateZ);
		}
	}
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

void ObjectPoints::Scale(float scale) {
	for (auto& face : faces) {
		for (auto& point : face.points) {
			point = (point - center) * scale + center;
		}
	}
}

void ObjectPoints::ScaleTo(float scaleTo) {
	for (auto& face : faces) {
		for (auto& point : face.points) {
			point = (point - center).Normalize() * scaleTo + center;
		}
	}
}

void ObjectPoints::Draw() {
	simulation->LoadDraw(this);
}