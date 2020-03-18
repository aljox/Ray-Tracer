#include "./DiffuseMaterial.h"

DiffuseMaterial::DiffuseMaterial() {}
DiffuseMaterial::~DiffuseMaterial() {}

DiffuseMaterial::DiffuseMaterial(Vec3f albedo) 
{
	m_ambientColor = albedo;
	m_diffuseColor = albedo;
	m_specularColor = albedo;
	m_shininess = 64;
}

DiffuseMaterial::DiffuseMaterial(Vec3f ambientColor, Vec3f diffuseColor, Vec3f specularColor, int shininess)
{
	m_ambientColor = ambientColor;
	m_diffuseColor = diffuseColor;
	m_specularColor = specularColor;
	m_shininess = shininess;
}

Vec3f DiffuseMaterial::color(const Ray& ray, hitRecord& sceneHit, Scene& scene, float& tNear, float tFar, int rayCount)
{
		Vec3f color(0.0f, 0.0f, 0.0f);
		std::list <Light*> lights = scene.getLights();

		// For each light compute shadow ray and perform shading
		for (Light* const light : lights) {
			
			Vec3f phongShading;

			hitRecord shadowRayRecord;
			Ray shadowRay(sceneHit.p, light->generateShadowRayDir(sceneHit.p));
			bool shadowIntersection = scene.findIntersection(shadowRay, tNear, tFar, shadowRayRecord);

			// Point light
			if (light->getType().compare("PointLight") == 0) {

				if (!shadowIntersection) {
					phongShading = phong(ray, light, sceneHit, shadowRay, false);
				}
				else {

					// If shadow ray has intersected, intersection must not
					// be further away than light source
					float distToLight = lengthNonSquared(light->getPosition() - sceneHit.p);
					float distToShadowIntersect = lengthNonSquared(shadowRayRecord.p - sceneHit.p);
					
					if (distToLight <= distToShadowIntersect) {

						phongShading = phong(ray, light, sceneHit, shadowRay, false);
					}
					else {
						// Only ambient
						phongShading = phong(ray, light, sceneHit, shadowRay, true);
					}
				}

				// Attenuation
				float d = length(light->getPosition() - sceneHit.p);
				float attenuation = 1.0f / (1.0f + d + pow(d, 2));

				phongShading *= attenuation;
			}
			// Directional light
			else if(light->getType().compare("DirectionalLight") == 0) { 

				if (!shadowIntersection) {
					phongShading = phong(ray, light, sceneHit, shadowRay, false);
				}
				else {
					phongShading = phong(ray, light, sceneHit,  shadowRay, true);
				}

			}

			color += light->getIntensity() * light->getAlbedo() * phongShading;
		}

		return color;
}

Vec3f DiffuseMaterial::phong(const Ray& incomingRay, Light* light, hitRecord& sceneHit, Ray& shadowRay, bool shadow) {
	// Basic ambient term
	Vec3f ambient = light->getAmbientConst() * m_ambientColor;
	Vec3f diffuse(0.0f, 0.0f, 0.0f);
	Vec3f specular(0.0f, 0.0f, 0.0f);

	if (!shadow) {

		// Diffuse term
		float diff = fmax(0.0f, dot(unitVector(shadowRay.direction()), unitVector(sceneHit.normal)));
		diffuse = light->getDiffuseConst() * diff * m_diffuseColor;

		//Specular term
		Vec3f reflectedLightDirection = reflect(unitVector(-1.0f * shadowRay.direction()), sceneHit.normal);
		float spec = pow(fmax(0.0f, dot(unitVector(reflectedLightDirection), unitVector(-1.0f * incomingRay.direction()))), m_shininess);
		specular = light->getSpecularConst() * spec * m_specularColor;
	}

	return ambient + diffuse + specular;
}
