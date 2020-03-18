#pragma once
#include <Math.h>

class Vec3f 
{
	public:
		float e[3];

		Vec3f() {};
		~Vec3f() {};
		Vec3f(float x, float y, float z) { e[0] = x; e[1] = y; e[2] = z; };

		inline float x() const { return e[0]; }
		inline float y() const { return e[1]; }
		inline float z() const { return e[2]; }
		inline float r() const { return e[0]; }
		inline float g() const { return e[1]; }
		inline float b() const { return e[2]; }

		inline Vec3f& operator+=(const Vec3f& v);
		inline Vec3f& operator-=(const Vec3f& v);
		inline Vec3f& operator*=(const Vec3f& v);
		inline Vec3f& operator/=(const Vec3f& v);
		inline Vec3f& operator*=(const float t);
		inline Vec3f& operator/=(const float t);

		inline float length();
		inline float squaredLength();
		inline void makeUnitVector();
};

inline Vec3f& Vec3f::operator+=(const Vec3f& v)
{
	e[0] += v.e[0];
	e[1] += v.e[1];
	e[2] += v.e[2];
	return *this;
}

inline Vec3f& Vec3f::operator-=(const Vec3f& v)
{
	e[0] -= v.e[0];
	e[1] -= v.e[1];
	e[2] -= v.e[2];
	return *this;
}

inline Vec3f& Vec3f::operator*=(const Vec3f& v)
{
	e[0] *= v.e[0];
	e[1] *= v.e[1];
	e[2] *= v.e[2];
	return *this;
}

inline Vec3f& Vec3f::operator/=(const Vec3f& v)
{
	e[0] /= v.e[0];
	e[1] /= v.e[1];
	e[2] /= v.e[2];
	return *this;
}

inline Vec3f& Vec3f::operator*=(const float t)
{
	e[0] *= t;
	e[1] *= t;
	e[2] *= t;
	return *this;
}

inline Vec3f& Vec3f::operator/=(const float t)
{
	e[0] /= t;
	e[1] /= t;
	e[2] /= t;
	return *this;
}

inline float Vec3f::length()
{
	return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
}

inline float Vec3f::squaredLength()
{
	return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
}

inline void Vec3f::makeUnitVector() {
	float k = 1 / (e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
	e[0] *= k;
	e[1] *= k;
	e[2] *= k;
}

// Vector utility methodts
inline Vec3f operator+(const Vec3f& v1, const Vec3f& v2)
{
	return Vec3f(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline Vec3f operator-(const Vec3f& v1, const Vec3f& v2)
{
	return Vec3f(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

inline Vec3f operator*(const Vec3f& v1, const Vec3f& v2)
{
	return Vec3f(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

inline Vec3f operator/(const Vec3f& v1, const Vec3f& v2)
{
	return Vec3f(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

inline Vec3f operator*(float t, const Vec3f& v)
{
	return Vec3f(v.e[0] * t, v.e[1] * t, v.e[2] * t);
}

inline Vec3f operator/(const Vec3f& v, float t)
{
	return Vec3f(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}

inline Vec3f unitVector(Vec3f v)
{
	return v / v.length();
}

inline Vec3f cross(const Vec3f& v1, const Vec3f& v2)
{
	return Vec3f(v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
		v1.e[2] * v2.e[0] - v1.e[0] * v2.e[2],
		v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]);
}

inline float dot(const Vec3f& v1, const Vec3f& v2)
{
	return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}

inline float length(const Vec3f& v)
{
	return sqrt(v.e[0] * v.e[0] + v.e[1] * v.e[1] + v.e[2] * v.e[2]);
}

inline float lengthNonSquared(const Vec3f& v)
{
	return v.e[0] * v.e[0] + v.e[1] * v.e[1] + v.e[2] * v.e[2];
}

// incomping vector must point to surface
inline Vec3f reflect(const Vec3f& v, const Vec3f& n) {
	return v - 2.0f * dot(v, n) * n;
}


