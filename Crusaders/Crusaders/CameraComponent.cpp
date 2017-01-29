#include "CameraComponent.hpp"
#include "ObjectPoints.hpp"


CameraComponent::CameraComponent() {}

CameraComponent::CameraComponent(Simulation* simulation, Vector3 anchor, ObjectPoints* objectPoints) 
 : simulation(simulation), anchor(anchor), objectPoints(objectPoints) {
}