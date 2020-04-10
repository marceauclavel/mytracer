## Classes

### Scene
- Sphere* spheres
- Material* materials
- Light* lights
- int nSpheres, nMaterials, nLights
- bool init(const char* ifn)

### Camera
- Point pos
- Vector dir
- int xOpening, yOpening
- int xRes, yRes
- int depth
- int nPixels
- Pixel* screen
- bool print(const char* ofn)

### Intersection
- Ray* iray
- Vector n
- Material* mat
- Sphere* sph

## Data structs

### Sphere
- Point pos
- float r

### Material
- Color col

### Light
- Point pos
- Color col

### Point
- float x, y, z

### Vector
- float x, y, z

### Color
- int r, g, b

### Pixel
- Color col
- Ray pray

### Ray
- Point pos
- Vector dir

## Functions

- Color computeColor(Pixel)
- Intersection intersect(Ray, Scene)
- Color computeAmbiant(Intersection)
- Color computeDirectDiffuse(Ray)

## Pseudo code
- scene.init
- camera.init
- for pixel in camera.screen { computeColor(pixel) }
- saveImage