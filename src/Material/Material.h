#pragma once
//#include "../Math/Vec3f.h"
#include "../Math/Ray.h"
#include "../Core/Scene.h"
//#include "../Object/Hitable.h"

extern const int RAY_LIMIT;

struct hitRecord;
class Scene;

class Material 
{
	protected:
		Vec3f m_albedo;
	
	public:
		Material() {}
		~Material() {}

		Material(Vec3f albedo) { m_albedo = albedo; }

		virtual Vec3f color(const Ray& ray, hitRecord& sceneHit, Scene& scene, float& tNear, float tFar, int rayCount) { return Vec3f(0.0f, 0.0f, 0.0f); }

		void setAlbedo(Vec3f albedo) { m_albedo = albedo; }
		Vec3f getAlbedo() { return m_albedo; }
};