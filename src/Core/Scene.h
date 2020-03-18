#pragma once
#include <list>
#include "../Math/Ray.h"
#include "../Object/Light.h"
#include "../Object/Hitable.h"


class Scene
{
	private:
		std::list <Hitable*> hitable;
		std::list <Light*> lights;

	public:
		Scene();
		~Scene();

		void addHitable(Hitable* hitableObj);
		void removeHitable(Hitable* hitableObj);

		void addLight(Light* light);
		void removeLight(Light* light);

		bool findIntersection(const Ray& ray, const float& tNear, const float& tFar, hitRecord& rec);	

		Vec3f backgroundColor(const Ray& ray);

		std::list <Light*> getLights() { return lights; }
};