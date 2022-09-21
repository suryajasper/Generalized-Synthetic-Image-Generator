#pragma once
//#include "stb_image_resize.h"
#include <iostream>
#include <glad/glad.h>
#include "UniformManager.h"

class Texture2D
{
public:
	Texture2D(ShaderProgram* shaderProgram, const char* fileName);
	~Texture2D();

	bool LoadImage(const char* fileName);

	void Bind();
	void Unbind();

private:
	GLuint texId;

	UniformManager* uniformManager;
};

