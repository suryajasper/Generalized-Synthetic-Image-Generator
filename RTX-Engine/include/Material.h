#pragma once
#include <fstream>
#include <iostream>
#include <map>
#include "Texture2D.h"

class Material
{
public:
	Material();
	~Material();

	Texture2D* GetTexture(TextureMappingType texType);
	void LoadTexturesFromMTL(const char* fileName);

private:
	std::map<TextureMappingType, Texture2D*> textures;
};

