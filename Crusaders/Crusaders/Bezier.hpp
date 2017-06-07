#pragma once

#include "Vector2.hpp"
#include <vector>

class Bezier {
public:
	Bezier(std::vector<Vector2> transitions);
	Vector2 findPosition(float time);
private:
	Vector2 binomialPosition(float time);
	Vector2 deCasteljauPosition(float time);
	Vector2 reduceCurve(std::vector<Vector2> points, float time);
	std::vector<Vector2> transitions;
	// Count is the number of points we are looking up the binomial table for
	std::vector<float> getBinomial(int count);
	static std::vector<std::vector<float>> binomial;
};