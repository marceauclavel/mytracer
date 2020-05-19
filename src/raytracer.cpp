#include <fstream>
#include <iostream>
#include <cmath>

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

	//linking spheres to materials
	for (int i = 0; i < scene->nSpheres; i++){
		scene->spheres[i].mat = scene->materials[scene->spheres[i].matNb];
	}

	return true;
}

void intersect(Ray ray, Scene* scene, Intersection* intersection){
	Material background;
	int closestSphereIndex = -1;
	float dmin = std::numeric_limits<double>::infinity();
	for (int i = 0; i < scene->nSpheres; ++i){
		float d = scene->spheres[i].intersects(ray);
		if (d != -1){
			if (d < dmin){
				dmin = d;
				closestSphereIndex = i;
			}
		}
	}
	if (closestSphereIndex == -1) {
		intersection->mat = &background;
		intersection->d = -1;
	} else {
		intersection->mat = &scene->spheres[closestSphereIndex].mat;
		intersection->sph = &scene->spheres[closestSphereIndex];
		intersection->d = dmin;
		Vector n = Vector(intersection->sph->pos.x, intersection->sph->pos.y, intersection->sph->pos.z) + ( (-1 * dmin) * ray.dir);
		n.normalize();
		intersection->n = n;
	}
}

int computeShadow(Scene* scene, Intersection* intersection) {
	Light light = scene->lights[0];
	Vector lightDir = (intersection->d * intersection->iray->dir) + (-1. *  Vector((float)light.pos.x, (float)light.pos.y, (float)light.pos.z));
	lightDir.normalize();
	std::cout << lightDir << std::endl;
	float intensity = (-1. * intersection->n).dot(lightDir);
	return intensity;
}

Color mixColor(Color a, Color b, float coeff) {
	int nr = coeff * a.r + (1 - coeff) * b.r;
	int ng = coeff * a.g + (1 - coeff) * b.g;
	int nb = coeff * a.b + (1 - coeff) * b.b;
	Color col(nr, ng, nb);
	return col;
}

bool trace(Scene* scene, Camera* camera) {
	camera->setupScreen();
	Pixel* currentPixel;
	Intersection intersection;
	Color diffuse;
	Color zBuffer;
	float shadow;
	Color dark(0);
	Color col;
	for (unsigned int p = 0; p < camera->nPixels; ++p){
		currentPixel = &camera->screen[p];
		intersect(currentPixel->pray, scene, &intersection);
		if (intersection.d  == -1 ) {
			currentPixel->col = intersection.mat->col;
		} else {
			diffuse = mixColor(dark, intersection.mat->col, .5);
			int ZbufferValue = std::max(0, (int)(255 * (1 - (intersection.d / 10.))));
			zBuffer = Color(ZbufferValue);
			col = mixColor(diffuse, zBuffer, .8);
			shadow = computeShadow(scene, &intersection);
			std::cout << shadow << std::endl;
			//col = Color(shadow * col.r, shadow * col.g, shadow * col.b);
			currentPixel->col = col;
		}
	}
	return true;
}

bool print(Camera* camera, char* ofn) {
	std::ofstream ofs(ofn, std::ios::out | std::ios::binary);
	ofs << "P6\n" << camera->xRes << " " << camera->yRes << "\n255\n";
	for (unsigned i = 0; i < camera->nPixels; ++i) {
		//if (i%2 == 0) {
		//ofs << (unsigned char)(255) <<
		//(unsigned char)(255) <<
		//(unsigned char)(255);
		//} else {
		ofs << (unsigned char)(std::min(255, camera->screen[i].col.r )) <<
		(unsigned char)(std::min(255, camera->screen[i].col.g )) <<
		(unsigned char)(std::min(255, camera->screen[i].col.b ));
		//}
	}
	ofs.close();
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
	if (trace(&scene, &camera)) {
		std::cout << "tracing successfull !" << std::endl;
	}
	//print the image
	if (print(&camera, argv[2])) {
		std::cout << "printing successfull !" << std::endl;
	}
	return -1;
}

