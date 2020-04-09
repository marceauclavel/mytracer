## Classes

### Scene
- Sphere* spheres
- Material* materials
- Light* lights
- int nSpheres, nMaterials, nLights
- bool init(const char* ifn)

### Camera
- Point position
- Vector direction
- float xOpening, yOpening
- float xResolution, yResolution
- Pixel* screen
- int nPixels
- int depth

### Intersection
- Ray* iray
- Vector normal
- Material* material
- Shape* shape

## Data structs

### Sphere
- Point position
- float r

### Material
- Color c

### Light
- Point position
- Vector direction
- Color c

### Point
- float x, y, z

### Vector
- float x, y, z

### Color
- int r, g, b

### Pixel
- Color c
- Ray primaryRay

### Ray
- Point position
- Vector direction

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