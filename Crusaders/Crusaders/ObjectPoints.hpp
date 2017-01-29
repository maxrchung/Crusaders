#pragma once

class ObjectFace;
class ObjectLine;
class ObjectSprite;
class Simulation;

#include "Face.hpp"
#include "Sprite.hpp"
#include <unordered_set>
#include <vector>

class ObjectPoints {
public:
	ObjectPoints(Simulation* simulation, std::vector<Face> faces);

	// Local
	void Move(Vector3 move);
	// Global
	void MoveTo(Vector3 moveTo);

	// Local
	void Rotate(float rotateX, float rotateY, float rotateZ);
	// Local
	void Rotate(Vector3 rotate);
	// Local
	void RotateX(float rotateX);
	// Local
	void RotateY(float rotateY);
	// Local
	void RotateZ(float rotateZ);
	// Global
	void RotateTo(Vector3 rotateTo);

	// Local
	void Scale(float scale);
	// Global
	void ScaleTo(float scaleTo);

	// Different coloring should really only be used for debug purposes
	// Because controlling overlaps will be difficult, we want to make sure all lines are the same color
	void Color(Color color);
	// Colors a sprite over a period of time
	// Be careful when using this since you should not call this repeatedly
	void Color(int startTime, int endTime, ::Color startColor, ::Color endColor);

	// This will instantly set the fade of all sprites at simulation->time
	// You should probably only ever use this to instantly hide something and not do a gradual fade over time
	void Fade(float fade);
	// Fades a sprite over a period of time
	// Be careful using this and only call this once, it doesn't make sense to call this repeatedly
	void Fade(int startTime, int endTime, float startFade, float endFade);

	void Draw();

	Simulation* simulation;

	std::vector<Vector3*> objectPoints;
	std::vector<ObjectLine*> objectLines;
	std::vector<ObjectFace*> objectFaces;
	std::vector<ObjectSprite*> objectSprites;

	Vector3 center;
	Vector3 rotation;
};
