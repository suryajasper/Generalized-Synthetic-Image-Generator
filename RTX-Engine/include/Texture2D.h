#pragma once
#include <iostream>
#include <glad/glad.h>
#include "ShaderProgram.h"
#include <map>

enum TextureMappingType {
	TEX_MAP_DIFFUSE,
	TEX_MAP_NORMAL,
	TEX_MAP_SPECULAR,
	TEX_MAP_ROUGHNESS,
};

extern std::map<TextureMappingType, std::string> tmtStr;

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

	ShaderProgram* shader;
};

