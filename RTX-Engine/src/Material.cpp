#include "Material.h"

Material::Material()
{
}

Material::~Material()
{
}

Texture2D* Material::GetTexture(TextureMappingType texType)
{
	if (textures.find(texType) == textures.end())
		return nullptr;

	return textures[texType];
}

void Material::LoadTexturesFromMTL(const char* fileName)
{

}
