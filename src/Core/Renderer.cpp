#include "./Renderer.h"
#include <iostream>

Renderer::Renderer() { m_tNear = 0.01f; m_tFar = 1000.0f; }
Renderer::~Renderer() {}

Renderer::Renderer(float tNear, float tFar)
{
	m_tNear = tNear;
	m_tFar = tFar;
}

void Renderer::render(int* imageBuffer, const int& width, const int& height, Sampler& sampler, Scene& scene, Camera& camera)
{
	hitRecord sceneHit;
	Vec2f* samples;

	// Fill image buffer
	// Bottom to top
	for (int y = height - 1; y >= 0; y--) {
		for (int x = 0; x < width; x++) {

			Vec3f pixelColor(0.0f, 0.0f, 0.0f);
			samples = sampler.sample(x, y);

			// Accumulate samples
			for (int i = 0; i < sampler.getNumOfSamples(); i++) {
				float u = samples[i].e[0] / float(width);
				float v = samples[i].e[1] / float(height);

				// Create image ray
				const Ray imageRay = camera.getRay(u, v);

				// Find intersection
				const bool sceneIntersection = scene.findIntersection(imageRay, m_tNear, m_tFar, sceneHit);

				if (sceneIntersection) {
					pixelColor += sceneHit.material->color(imageRay, sceneHit, scene, m_tNear, m_tFar, 0);
				}
				else { // Handling if material is not present - background was hit
					pixelColor += scene.backgroundColor(imageRay);
				}
			}

			pixelColor /= float(sampler.getNumOfSamples());

			imageBuffer[(y * width + x) * 3] = int(255.99f * pixelColor.r());
			imageBuffer[(y * width + x) * 3 + 1] = int(255.99f * pixelColor.g());
			imageBuffer[(y * width + x) * 3 + 2] = int(255.99f * pixelColor.b());
		}
	}
}
