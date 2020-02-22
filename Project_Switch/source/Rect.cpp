#include "Rect.h"

Rect::Rect(float x, float y, float width, float height) :
	_x(x), _y(y), _width(width), _height(height)
{
}

float Rect::GetXMin()
{
	return _x;
}

float Rect::GetYMin()
{
	return _y;
}

float Rect::GetXMax()
{
	return _x + _width;
}

float Rect::GetYMax()
{
	return _y + _height;
}

Vector2D Rect::GetCenter()
{
	return Vector2D(_x - _width/2.0f, _y - _height/2.0f);
}

Vector2D Rect::GetPosition()
{
	return Vector2D(_x, _y);
}

Vector2D Rect::GetSize()
{
	return Vector2D(_width, _height);
}

void Rect::Set(float x, float y, float width, float height)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;
}

bool Rect::Overlaps(Rect rect)
{
	return false;
}
