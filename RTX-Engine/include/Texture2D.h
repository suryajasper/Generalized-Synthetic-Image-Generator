#pragma once
#include <iostream>
#include <glad/glad.h>
#include "ShaderProgram.h"
#include <map>

enum TextureMappingType {
	TEX_MAP_DIFFUSE = 0,
	TEX_MAP_NORMAL = 1,
	TEX_MAP_SPECULAR = 2,
	TEX_MAP_ROUGHNESS = 3,
	TEX_MAP_METALLIC = 4,
	TEX_MAP_OCCLUSION = 5,
};

extern std::map<TextureMappingType, std::string> tmtStr;

class Texture2D
{
public:
	Texture2D(ShaderProgram* shaderProgram, TextureMappingType mapType);
	~Texture2D();

	bool LoadImage(const char* fileName);

	void Bind();
	void Unbind();

private:
	GLuint texId;
	TextureMappingType mapType;

	ShaderProgram* shader;
};

