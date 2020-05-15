#include <fstream>
#include <iostream>

#include "header.h"

bool init(Scene* scene, Camera* camera, char* ifn) {

	std::ifstream file(ifn);
	if (!file) return false;
	file >> scene->nMaterials >> scene->nSpheres >> scene->nLights;
	file >> camera->pos >> camera->dir >> camera->xOpening >> camera->yOpening >> camera->xRes >> camera->yRes >> camera->depth;

	camera->nPixels = camera->xRes * camera->yRes;

	//memory allocation
	scene->materials = new Material[scene->nMaterials];
	scene->spheres = new Sphere[scene->nSpheres];
	scene->lights = new Light[scene->nLights];
	camera->screen = new Pixel[camera->nPixels];

	//filling scene data
	for (int i = 0; i < scene->nMaterials; i++){
		file >> scene->materials[i];
	}
	for (int i = 0; i < scene->nSpheres; i++){
		file >> scene->spheres[i];
	}
	for (int i = 0; i < scene->nLights; i++){
		file >> scene->lights[i];
	}

	return true;
}

bool trace(Scene* scene, Camera* camera, char* ofn) {
	float xStep, yStep;
	Vector dir, xDir, yDir;
	Point pos;
	for ( int i = 0; i < camera->xRes; i++) {
		for ( int j = 0; j < camera->yRes; j++) {
			pos = camera->pos;
			dir = camera->dir;
			//xDir = dir.cross(Vector(0, 0, 1));
			//yDir = Vector(0, 0, 1);
			Ray pray;
		}
	}
	Vector veca = Vector(1., 1., 1.);
	Vector vecb = Vector(1., 0., 0.);
	//Vector vecc = veca.cross(vecb);
	std::cout << "testing veca " << veca.x << " " << veca.y << " " << veca.z << std::endl;
	std::cout << "testing vecb " << vecb.x << " " << vecb.y << " " << vecb.z << std::endl;
	//std::cout << "testing vecc " << vecc.x << " " << vecc.y << " " << vecc.z << std::endl;
	return true;
}

int main(int argc, char** argv) {
	if (argc < 3) {
		std::cerr << "[inut file] [output file]" << std::endl;
		return -1;
	}
	//initialising scene and camera
	Scene scene;
	Camera camera;
	if (init(&scene, &camera, argv[1])) {
		std::cout << "initialization successfull !" << std::endl;
	}
	//compute the image
	if (trace(&scene, &camera, argv[2])) {
		std::cout << "tracing successfull !" << std::endl;
	}

	return -1;
}

