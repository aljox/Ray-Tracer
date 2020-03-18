#include <iostream>
#include <fstream>

#include "./FileOutput/Output.h"
#include "./Core/StratifiedSampler.h"
#include "./Core/Renderer.h"
#include "./Core/Scene.h"
#include "./Core/Camera.h"
#include "./Object/Sphere.h"
#include "./Object/DirectionalLight.h"
#include "./Object/PointLight.h"
#include "./Material/DiffuseMaterial.h"
#include "./Material/MetalMaterial.h"
#include "./Material/DielectricsMaterial.h"

const int RAY_LIMIT = 10;

double random_double() 
{
	return rand() / (RAND_MAX + 1.0);
}

void generateScene(Scene& scene) 
{
	
	DiffuseMaterial* diffuseMaterialGrey = new DiffuseMaterial(Vec3f(0.5f, 0.5f, 0.5f));
	Sphere* sphere = new Sphere(Vec3f(0.0f, -1000.0f, 0.0f), 1000.0f, diffuseMaterialGrey);
	scene.addHitable(sphere);

	int i = 1;
	
	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			Sphere* randSphere = nullptr;

			float choose_mat = random_double();
			Vec3f center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

			if ((center - Vec3f(4, 0.2, 0)).length() > 0.9) {
				if (choose_mat < 0.8) {  // diffuse
					randSphere = new Sphere(
						center, 0.2,
						new DiffuseMaterial(Vec3f(random_double() * random_double(),
							random_double() * random_double(),
							random_double() * random_double()))
					);

					scene.addHitable(randSphere);
				}
				else if (choose_mat < 0.95) { // metal
					randSphere = new Sphere(
						center, 0.2f,
						new MetalMaterial(0.1f));

					scene.addHitable(randSphere);
				}
				else {  // glass
					randSphere = new Sphere(center, 0.2f, new DielectricsMaterial(Vec3f(random_double() * random_double(),
						random_double() * random_double(),
						random_double() * random_double()), 
						1.5f));

					scene.addHitable(randSphere);
				}
			}
		}
	}

	scene.addHitable(new Sphere(Vec3f(0.0f, 1.0f, 0.0f), 1.0f, new DielectricsMaterial(Vec3f(1.0f, 1.0f, 1.0f), 1.5f)));
	scene.addHitable(new Sphere(Vec3f(-4.0f, 1.0f, 0.3f), 1.0f, new DiffuseMaterial(Vec3f(0.4f, 0.2f, 0.1f))));
	scene.addHitable(new Sphere(Vec3f(4.0f, 1.0f, -0.3f), 1.0f, new MetalMaterial(0.1f)));
}

int main()
{	
	// Set image dimensions
	const int width = 400;
	const int height = 200;

	// Init sampler
	int numOfSamples = 1;
	Sampler sampler(numOfSamples);
	//StratifiedSampler stratifiedSampler(numOfSamples, true);

	// Set up canvas
	int* imageBuffer = new int[width * height * 3];

	// Light init
	DirectionalLight* dirLight = new DirectionalLight(unitVector(Vec3f(-1.0f, -1.0f, -1.0f)), Vec3f(1.0f, 1.0f, 1.0f), 1.0f, 0.2f, 1.0f, 1.0f);
	//PointLight* pointLight = new PointLight(Vec3f(1.0f, 1.0f, 1.0f), Vec3f(-0.2f, 0.0f, -0.2f), 0.4f);

	// Scene init
	Scene scene;
	generateScene(scene);

	scene.addLight(dirLight);
	//scene.addLight(pointLight);

	// Init camera
	Camera camera(Vec3f(13.0f, 2.0f, 3.0f), Vec3f(0.0f, 0.0f, 0.0f), 25.0f, (float) width / (float) height);

	// Init renderer
	Renderer renderer;

	// Render to image buffer
	renderer.render(imageBuffer, width, height, sampler, scene, camera);

	// Write to ppm file
	Output output("rayTracedImage.ppm");
	output.writePPM(imageBuffer, width, height);

	return 0;
}