#pragma once
#include "./Material.h"

class MetalMaterial : public Material
{
	private:
		float m_absorbtion;
	
	public:
		MetalMaterial();
		~MetalMaterial();
		MetalMaterial(float absorbtion);

		Vec3f color(const Ray& ray, hitRecord& sceneHit, Scene& scene, float& tNear, float tFar, int rayCount);

		void setAbsorbtion(float absorbtion) { m_absorbtion = absorbtion; }
		float getAbsorbtion() { return m_absorbtion; }
};