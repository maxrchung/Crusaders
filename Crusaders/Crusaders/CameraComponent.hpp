#ifndef CAMERACOMPONENT_HPP
#define CAMERACOMPONENT_HPP

class ObjectPoints;
class Simulation;

#include "Vector3.hpp"

// CameraComponent allows an object to move along with the camera
class CameraComponent {
public:
	CameraComponent();
	CameraComponent(Simulation* simulation, Vector3 anchor, ObjectPoints* objectPoints);

	Vector3 anchor;
	ObjectPoints* objectPoints;
	Simulation* simulation;
};

#endif//CAMERACOMPONENT_HPP