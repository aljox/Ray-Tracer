#include "./Scene.h"

Scene::Scene() {}
Scene::~Scene() {}

void Scene::addHitable(Hitable* hitableObj) 
{
	hitable.push_back(hitableObj);
}

void Scene::removeHitable(Hitable* hitableObj)
{
	hitable.remove(hitableObj);
}

void Scene::addLight(Light* light)
{
	lights.push_back(light);
}
void Scene::removeLight(Light* light)
{
	lights.remove(light);
}

// Find closest intersection with ray and geometry in scene
bool Scene::findIntersection(const Ray& ray, const float& tNear, const float& tFar, hitRecord& rec)
{
	bool hitAnything = false;
	hitRecord temp;
	float nearestHit = tFar + 1.0f;

	for (Hitable* const hitableObj : hitable) {
		if (hitableObj->intersects(ray, tNear, tFar, temp)) {
			if (temp.t < nearestHit) {
				nearestHit = temp.t;
				rec = temp;
				hitAnything = true;
			}
		}
	}

	return hitAnything;
}

Vec3f Scene::backgroundColor(const Ray& ray)
{
	Vec3f unitDir = unitVector(ray.direction());
	float t = (unitDir.y() + 1.0f) * 0.5f;
	return (1.0f - t) * Vec3f(1.0f, 1.0f, 1.0f) + t * Vec3f(0.5f, 0.7f, 1.0f);
}