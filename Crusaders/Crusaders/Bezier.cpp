#include "Bezier.hpp"

std::vector<std::vector<float>> Bezier::binomial = { {1} };

Bezier::Bezier(std::vector<Vector2> transitions) 
	: transitions(transitions) {
}

Vector2 Bezier::findPosition(float time) {
	// Anything larger exceeds float numeric limits
	if (transitions.size() <= 33) {
		return binomialPosition(time);
	}
	else {
		return deCasteljauPosition(time);
	}
}

Vector2 Bezier::binomialPosition(float time) {
	Vector2 position = Vector2::Zero;
	int size = transitions.size();
	std::vector<float> row = getBinomial(size);

	for (int i = 0; i < size; i++) {
		Vector2 point = transitions[i];
		float binomial = row[i];
		if (binomial < 1) {
			throw "Binomial value overflow";
		}
		float t1 = powf(1 - time, size - i - 1);
		float t2 = powf(time, i);
		// Calculate binomial with time first so that we do not run pass float limit
		Vector2 part = point * (binomial * t1 * t2);
		position += part;
	}
	return position;
}

Vector2 Bezier::deCasteljauPosition(float time) {
	return reduceCurve(transitions, time);
}

Vector2 Bezier::reduceCurve(std::vector<Vector2> points, float time) {
	if (points.size() == 1) {
		return points.front();
	}
	else {
		std::vector<Vector2> reduce = std::vector<Vector2>(points.size() - 1);
		for (int i = 0; i < reduce.size(); i++) {
			reduce[i] = points[i] * (1 - time) + points[i + 1] * time;
		}
		return reduceCurve(reduce, time);
	}
}

std::vector<float> Bezier::getBinomial(int count) {
	// Add to the table if we have not calculated the row yet
	if (binomial.size() < count) {
		for (int i = binomial.size(); i <= count; i++) {
			std::vector<float> row = { 1 };
			for (int j = 1; j < i - 1; j++) {
				int value = binomial[i - 1][j - 1] + binomial[i - 1][j];
				row.push_back(value);
			}
			row.push_back(1);
			binomial.push_back(row);
		}
	}

	return binomial[count];
}