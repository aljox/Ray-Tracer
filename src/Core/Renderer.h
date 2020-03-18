#pragma once

#include "../Core/Sampler.h"
#include "./Scene.h"
#include "../Material/Material.h"
#include "./Camera.h"

class Renderer
{
	private:
		float m_tNear;
		float m_tFar;

	public:
		Renderer();
		~Renderer();
		Renderer(float tNear, float tFar);

		// TODO: add scene and camera as parameters
		void render(int* imageBuffer, const int& width, const int& height, Sampler& sampler, Scene& scene, Camera& camera);
};