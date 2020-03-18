#include <iostream>
#include "Sphere.h"

Sphere::Sphere() {};
Sphere::~Sphere() {};
Sphere::Sphere(Vec3f position, float radious, Material* material) { m_position = position; m_radious = radious; m_material = material; }

bool Sphere::intersects(const Ray& ray, float tNear, float tFar, hitRecord& rec)
{	
	Vec3f oc = ray.origin() - m_position;
	float a = dot(ray.direction(), ray.direction());
	float b = 2.0 * dot(oc, ray.direction());
	float c = dot(oc, oc) - m_radious * m_radious;

	float det = b * b - 4.0 * a * c;

	if (det > 0.0) {
		float temp = (-b - sqrt(det)) / (2.0 * a);
		if (temp > tNear && temp < tFar) {
			rec.t = temp;
			rec.p = ray.pointAt(temp);
			rec.normal = (rec.p - m_position) / m_radious;
			rec.material = m_material;
			return true;
		}

		temp = (-b + sqrt(det)) / (2.0 * a);
		if (temp > tNear && temp < tFar) {
			rec.t = temp;
			rec.p = ray.pointAt(temp);
			rec.normal = (rec.p - m_position) / m_radious;
			rec.material = m_material;
			return true;
		}
	}
	
	return false;
}

float Sphere::getRadious() { return m_radious; }
void Sphere::setRadious(float radious) { m_radious = radious; }