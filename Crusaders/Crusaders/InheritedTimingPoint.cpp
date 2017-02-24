#include "InheritedTimingPoint.hpp"

InheritedTimingPoint::InheritedTimingPoint(int offset, float mspb) 
	: offset(offset), mspb(mspb), sliderMultiplier(-100.0f / mspb) {
}
