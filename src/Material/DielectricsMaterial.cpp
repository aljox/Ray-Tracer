#include "./DielectricsMaterial.h"

DielectricsMaterial::DielectricsMaterial() {}
DielectricsMaterial::~DielectricsMaterial() {}

DielectricsMaterial::DielectricsMaterial(float refractiveCoef) 
{ 
	m_albedo = Vec3f(1.0f, 1.0f, 1.0f); 
	m_refractiveCoef = refractiveCoef;
}

DielectricsMaterial::DielectricsMaterial(Vec3f albedo, float refractiveCoef)
{
	m_albedo = albedo; 
	m_refractiveCoef = refractiveCoef;
}

Vec3f DielectricsMaterial::color(const Ray& ray, hitRecord& sceneHit, Scene& scene, float& tNear, float tFar, int rayCount)
{
	if (rayCount < RAY_LIMIT) {
		
		float refractionIndex; // n1/n2
		float schlickCoef;
		Vec3f outwardNormal;

		Vec3f unitDirIn = unitVector(ray.direction());

		// Handling ray entering or leaving dielectrics material
		// Outgoing ray
		if (dot(unitDirIn, sceneHit.normal) > 0.0f) {
			refractionIndex = m_refractiveCoef;
			outwardNormal = -1.0f * sceneHit.normal;
			schlickCoef = m_refractiveCoef - 1.0f;
		}
		else { // Entering ray
			refractionIndex = 1.0f / m_refractiveCoef;
			outwardNormal = sceneHit.normal;
			schlickCoef = 1.0f - m_refractiveCoef;
		}

		float cosineIN = dot(-1.0f * unitDirIn, outwardNormal);
		float discriminant = 1.0f - refractionIndex * refractionIndex * (1.0f - dot(-1.0f * unitDirIn, outwardNormal));

		if (discriminant > 0.0f) { // reflection + refraction

			float reflectedAmount = schlickApprox(m_refractiveCoef, schlickCoef, cosineIN);

			RefractInfo refractInfo;
			refractInfo.refractionIndex = refractionIndex;
			refractInfo.discriminant = discriminant;
			refractInfo.unitDirIn = unitDirIn;
			refractInfo.outwardNormal = outwardNormal;

			// Compute color
			Vec3f refractedColor = refractColor(sceneHit, scene, tNear, tFar, rayCount, refractInfo);
			Vec3f reflectedColor = reflectColor(ray, sceneHit, scene, tNear, tFar, rayCount, outwardNormal);

			return m_albedo * ((1.0f - reflectedAmount) * refractedColor + reflectedAmount * reflectedColor);

		}
		else if (discriminant < 0.0f) { // Only reflection

			Vec3f reflectedColor = reflectColor(ray, sceneHit, scene, tNear, tFar, rayCount, outwardNormal);

			return m_albedo * reflectedColor;
		}
		else { // No reflection and no refraction
			return m_albedo;
		}

	}
	else {
		return scene.backgroundColor(ray);
	}
}

Vec3f DielectricsMaterial::reflectColor(const Ray& ray, hitRecord& sceneHit, Scene& scene, float& tNear, float tFar, int rayCount, Vec3f outwardNormal)
{	
	Vec3f reflectedColor;

	hitRecord reflectedHit;
	Ray reflectedRay(sceneHit.p, reflect(unitVector(ray.direction()), outwardNormal));

	const bool reflectedIntersection = scene.findIntersection(reflectedRay, tNear, tFar, reflectedHit);

	if (reflectedIntersection) {
		reflectedColor = reflectedHit.material->color(reflectedRay, reflectedHit, scene, tNear, tFar, rayCount + 1);
	}
	else {
		reflectedColor = scene.backgroundColor(reflectedRay);
	}

	return reflectedColor;
}

Vec3f DielectricsMaterial::refractColor(hitRecord& sceneHit, Scene& scene, float& tNear, float tFar, int rayCount, RefractInfo refractInfo)
{	
	Vec3f refractedColor;

	hitRecord refractedHit;

	Vec3f refractedDir = refractInfo.refractionIndex * (refractInfo.unitDirIn + dot(-1.0f * refractInfo.unitDirIn, refractInfo.outwardNormal) * refractInfo.outwardNormal) - sqrt(refractInfo.discriminant) * refractInfo.outwardNormal;
	Ray refractedRay(sceneHit.p, unitVector(refractedDir));

	const bool refractedIntersection = scene.findIntersection(refractedRay, tNear, tFar, refractedHit);

	if (refractedIntersection) {
		refractedColor = refractedHit.material->color(refractedRay, refractedHit, scene, tNear, tFar, rayCount + 1);
	}
	else {
		refractedColor = scene.backgroundColor(refractedRay);
	}

	return refractedColor;
}

float DielectricsMaterial::schlickApprox(float refractiveCoef, float schlickCoef, float cosineIn)
{
	float reflectionCoef = pow(schlickCoef / (1.0f + refractiveCoef), 2);
	return reflectionCoef + (1.0f - reflectionCoef) * pow(1.0f - cosineIn, 5);
}

void DielectricsMaterial::setRefractiveCoef(float refractiveCoef) { m_refractiveCoef = refractiveCoef; }

float DielectricsMaterial::getRefractiveCoef() { return m_refractiveCoef; }