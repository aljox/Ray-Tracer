#include "Ray.h"

Ray::Ray() {}
Ray::~Ray() {}
Ray::Ray(Vec3f origin, Vec3f direction) { o = origin; dir = unitVector(direction); }

Vec3f Ray::pointAt(float t) const 
{
	return o + t * dir;
}

Vec3f Ray::origin() const { return o; }

Vec3f Ray::direction() const { return dir; }

