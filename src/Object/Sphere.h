#pragma once
#include "Hitable.h"

class Sphere : public Hitable
{
	private:
		float m_radious;
	public:
		Sphere();
		~Sphere();
		Sphere(Vec3f position, float radious, Material* material);

		bool intersects(const Ray& ray, float tNear, float tFar, hitRecord& rec);

		float getRadious();
		void setRadious(float radious);
};