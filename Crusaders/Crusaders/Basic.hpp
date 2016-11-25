#pragma once

#include "Object.hpp"
#include "ObjectType.hpp"

class Basic : public Object {
public:
	ObjectType type = ObjectType::Basic;
};
