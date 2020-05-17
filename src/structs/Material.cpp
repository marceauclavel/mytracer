#include "Material.h"

Material::Material() {
	col = Color(0, 0, 0);
}

Material::Material(Color ncol) {
	col = ncol;
}
