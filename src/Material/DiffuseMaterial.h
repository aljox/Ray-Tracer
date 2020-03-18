#pragma once
#include "./Material.h"

class DiffuseMaterial : public Material
{
	private:
		Vec3f m_ambientColor;
		Vec3f m_diffuseColor;
		Vec3f m_specularColor;
		int m_shininess;

	public:
		DiffuseMaterial();
		~DiffuseMaterial();
		DiffuseMaterial(Vec3f albedo);
		DiffuseMaterial(Vec3f ambientColor, Vec3f diffuseColor, Vec3f specularColor, int shininess);

		Vec3f color(const Ray& ray, hitRecord& sceneHit, Scene& scene, float& tNear, float tFar, int rayCount);
		Vec3f phong(const Ray& incomingRay, Light* light, hitRecord& sceneHit, Ray& shadowRay, bool shadow);

		void setAmbientColor(Vec3f ambientColor) { m_ambientColor = ambientColor; }
		void setDiffuseColor(Vec3f diffuseColor) { m_diffuseColor = diffuseColor; }
		void setSpecularColor(Vec3f specularColor) { m_specularColor = specularColor; }
		void setShininess(int shininess) { m_shininess = shininess; }

		Vec3f getAmbientColor() { return m_ambientColor; }
		Vec3f getDiffuseColor() { return m_diffuseColor; }
		Vec3f getSpecularColor() { return m_specularColor; }
		int getShininess() { return m_shininess; }
};