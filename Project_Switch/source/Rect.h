#ifndef RECT_H
#define RECT_H
#include "Vector2D.h"
class Rect
{
public:
	Rect(float x, float y, float width, float height);
	Rect();

	float GetXMin();

	float GetYMin();

	float GetXMax();

	float GetYMax();

	Vector2D GetCenter();

	Vector2D GetPosition();

	Vector2D GetSize();


	void Set(float x, float y, float width, float height);

	bool Overlaps(Rect rect);
private:
	float _x;
	float _y;
	float _width;
	float _height;
};
#endif