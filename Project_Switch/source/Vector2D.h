#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <math.h>

class Vector2D
{
public:
	Vector2D();

	Vector2D(float x, float y);

	Vector2D operator+(const Vector2D &rhs) const;

	Vector2D &operator+=(const Vector2D &rhs);

	Vector2D operator*(float scalar);

	Vector2D operator*=(float scalar);

	Vector2D operator-(const Vector2D &rhs) const;

	Vector2D &operator-=(const Vector2D &rhs);

	Vector2D operator/(float scalar);

	Vector2D operator/=(float scalar);

	float GetX();

	float GetY();

	void SetX(float x);

	void SetY(float y);

	void Set(float x, float y);

	void Set(Vector2D newPos);

	float Magnitude();

	void Normalize();

	Vector2D Normalized();

	static Vector2D Lerp(Vector2D start, Vector2D end, float t);

private:
	float m_x;
	float m_y;
};

#endif // VECTOR2D_H