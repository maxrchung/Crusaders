#include "Face.hpp"

Face::Face(std::vector<Vector3> points) 
	: points(points) {
}

Face::Face(Vector3 first, Vector3 second, Vector3 third, Vector3 fourth)
	: points({ first, second, third, fourth }) {
}
