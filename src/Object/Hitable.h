#pragma once

#include "../Math/Ray.h"
#include "./Object.h"
//#include "../Material/Material.h"

class Material;

struct hitRecord 
{
	float t;
	Vec3f p;
	Vec3f normal;
	//Problem ka direkt v material castam in pol uporabim original funkcijo namesto izpeljano
	Material* material;
};

class Hitable: public Object 
{
	protected:
		Material* m_material;

	public:
		Hitable() {}
		~Hitable() {}
		Hitable(Material* material) { m_material = material; }

		virtual bool intersects(const Ray& ray, float tNear, float tFar, hitRecord& rec) { return false; }

		void setMaterial(Material* material) { m_material = material; }
		Material* getMaterial() { return m_material; }
};