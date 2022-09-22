#pragma once
//#include "stb_image_resize.h"
#include <iostream>
#include <glad/glad.h>
#include "UniformManager.h"

enum TextureMappingType {
	TEX_MAP_COLOR,
	TEX_MAP_NORMAL,
	TEX_MAP_SPECULAR,
	TEX_MAP_ROUGHNESS,
	TEX_MAP_METALLIC,
};

class Texture2D
{
public:
	Texture2D(ShaderProgram* shaderProgram);
	~Texture2D();

	bool LoadImage(TextureMappingType mapType, const char* fileName);

	void Bind();
	void Unbind();

private:
	GLuint texId;

	UniformManager* uniformManager;
};

