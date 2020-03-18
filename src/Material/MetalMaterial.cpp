#include "./MetalMaterial.h"

MetalMaterial::MetalMaterial() { m_absorbtion = 0.0; }
MetalMaterial::~MetalMaterial() {}
MetalMaterial::MetalMaterial(float absorbtion) { m_absorbtion = absorbtion; }


Vec3f MetalMaterial::color(const Ray& ray, hitRecord& sceneHit, Scene& scene, float& tNear, float tFar, int rayCount)
{
	if (rayCount < RAY_LIMIT) {

		Vec3f outwardNormal;
		Vec3f unitDirIn = unitVector(ray.direction());

		// Outgoing ray
		if (dot(unitDirIn, sceneHit.normal) > 0.0f) {
			outwardNormal = -1.0f * sceneHit.normal;
		}
		else { // Entering ray
			outwardNormal = sceneHit.normal;
		}

		hitRecord reflectedHit;
		Ray reflectedRay(sceneHit.p, reflect(unitVector(ray.direction()), outwardNormal));

		const bool reflectedIntersection = scene.findIntersection(reflectedRay, tNear, tFar, reflectedHit);
		
		if (reflectedIntersection) {
			return (1.0 - m_absorbtion) * reflectedHit.material->color(reflectedRay, reflectedHit, scene, tNear, tFar, rayCount + 1);
		}
		else
		{
			return (1.0 - m_absorbtion)* scene.backgroundColor(ray);
		}

	}
	else {
		return scene.backgroundColor(ray);
	}
}

