#include "Overworld.hpp"
#include "Face.hpp"

Overworld::Overworld() {
	new Face((1, 1, 1), (-1, 1, 1), (-1, -1, 1), (1, -1, 1));
	new Face((1, 1, -1), (1, 1, 1), (1, -1, 1), (1, -1, -1));
	new Face((-1, 1, -1), (1, 1, -1), (1, -1, -1), (-1, -1, -1));
	new Face((-1, 1, 1), (-1, 1, -1), (-1, -1, -1), (-1, -1, 1));
	
}
