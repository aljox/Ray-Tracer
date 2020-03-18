#pragma once

#include "./Material.h"

struct RefractInfo
{
	float refractionIndex;
	float discriminant;
	Vec3f unitDirIn;
	Vec3f outwardNormal;
};

class DielectricsMaterial : public Material
{
	private:
		float m_refractiveCoef;
	
	public:
		DielectricsMaterial();
		~DielectricsMaterial();
		DielectricsMaterial(float refractiveCoef);
		DielectricsMaterial(Vec3f albedo, float m_refractiveCoef);

		Vec3f color(const Ray& ray,  hitRecord& sceneHit, Scene& scene, float& tNear, float tFar, int rayCount);

		Vec3f reflectColor(const Ray& ray, hitRecord& sceneHit, Scene& scene, float& tNear, float tFar, int rayCount, Vec3f outwardNormal);
		Vec3f refractColor(hitRecord& sceneHit, Scene& scene, float& tNear, float tFar, int rayCount, RefractInfo refractInfo);
		float schlickApprox(float refractiveCoef, float schlickCoef, float cosineIn);

		void setRefractiveCoef(float refractiveCoef);
		float getRefractiveCoef();
};