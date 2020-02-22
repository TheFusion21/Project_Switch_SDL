#include "Vector2D.h"

Vector2D::Vector2D() : m_x(0), m_y(0)
{
}

Vector2D::Vector2D(float x, float y)
	: m_x(x), m_y(y)
{
}

Vector2D Vector2D::operator+(const Vector2D &rhs) const
{
	return Vector2D(m_x + rhs.m_x, m_y + rhs.m_y);
}

Vector2D &Vector2D::operator+=(const Vector2D &rhs)
{
	m_x += rhs.m_x;
	m_y += rhs.m_y;
	return *this;
}

Vector2D Vector2D::operator*(float scalar)
{
	return Vector2D(m_x * scalar, m_y * scalar);
}

Vector2D Vector2D::operator*=(float scalar)
{
	m_x *= scalar;
	m_y *= scalar;
	return *this;
}

Vector2D Vector2D::operator-(const Vector2D &rhs) const
{
	return Vector2D(m_x - rhs.m_x, m_y - rhs.m_y);
}

Vector2D &Vector2D::operator-=(const Vector2D &rhs)
{
	m_x -= rhs.m_x;
	m_y -= rhs.m_y;
	return *this;
}

Vector2D Vector2D::operator/(float scalar)
{
	return Vector2D(m_x / scalar, m_y / scalar);
}

Vector2D Vector2D::operator/=(float scalar)
{
	m_x /= scalar;
	m_y /= scalar;
	return *this;
}

float Vector2D::GetX()
{
	return m_x;
}

float Vector2D::GetY()
{
	return m_y;
}

void Vector2D::SetX(float x)
{
	m_x = x;
}

void Vector2D::SetY(float y)
{
	m_y = y;
}

void Vector2D::Set(float x, float y)
{
	m_x = x;
	m_y = y;
}

void Vector2D::Set(Vector2D newPos)
{
	m_x = newPos.GetX();
	m_y = newPos.GetY();
}

float Vector2D::Magnitude()
{
	return (sqrt(m_x * m_x + m_y * m_y));
}

void Vector2D::Normalize()
{
	float len = Magnitude();
	if (len > 0) {
		*this *= 1 / len;
	}
}

Vector2D Vector2D::Normalized()
{
	float len = Magnitude();
	if (len > 0) {
		Vector2D vec(*this);
		vec.Normalize();
		return vec;
	}
	return Vector2D();
}
