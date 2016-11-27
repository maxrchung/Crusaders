#include "Overworld.hpp"
#include "ObjectPoints.hpp"
#include "Simulation.hpp"

Overworld::Overworld(Simulation* simulation) 
	: simulation(simulation) {
	objectPoints = new ObjectPoints(simulation, {
		Face(Vector3(1, 1, 1), Vector3(-1, 1, 1), Vector3(-1, -1, 1), Vector3(1, -1, 1)),
		Face(Vector3(1, 1, -1), Vector3(1, 1, 1), Vector3(1, -1, 1), Vector3(1, -1, -1)),
		Face(Vector3(-1, 1, -1), Vector3(1, 1, -1), Vector3(1, -1, -1), Vector3(-1, -1, -1)),
		Face(Vector3(-1, 1, 1), Vector3(-1, 1, -1), Vector3(-1, -1, -1), Vector3(-1, -1, 1))
	});

	objectPoints->ScaleTo(scale);
	//objectPoints->RotateY(-M_PI / 3);
	objectPoints->Move(Vector3(0, 0, -300));
}


