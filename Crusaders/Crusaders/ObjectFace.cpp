#include "ObjectFace.hpp"

ObjectFace::ObjectFace() {
}

ObjectFace::ObjectFace(Vector3* first, Vector3* second, Vector3* third, Vector3* fourth)
	: objectPoints({ first, second, third, fourth }) {
}

ObjectFace::ObjectFace(std::vector<Vector3*> objectPoints)
	: objectPoints(objectPoints) {
}
