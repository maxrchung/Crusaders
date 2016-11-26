#pragma once

#include "Sprite.hpp"

// Used as a wrapper around Sprite
// There needs to be a way to tell a sprite to reset itself
class ObjectSprite {
public:
	ObjectSprite(Sprite* sprite);

	bool reset = true;
	Sprite* sprite;
};