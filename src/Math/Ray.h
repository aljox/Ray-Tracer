#pragma once
#include "Vec3f.h"

class Ray
{
	private:
		Vec3f o;
		Vec3f dir;

	public:
		Ray();
		~Ray();
		Ray(Vec3f o, Vec3f dir);

		Vec3f pointAt(float t) const;

		Vec3f origin() const;
		Vec3f direction() const ;
};