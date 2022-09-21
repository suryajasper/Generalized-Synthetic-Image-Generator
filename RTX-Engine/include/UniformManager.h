#pragma once
#include <string>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "glm/gtc/type_ptr.hpp"
#include "ShaderProgram.h"

enum UniformType 
{
	UNIFORM_MAT4X4,
	UNIFORM_VEC3,
	UNIFORM_VEC2,
	UNIFORM_FLOAT,
	UNIFORM_INT,
};

class UniformManager
{
public:
	UniformManager(ShaderProgram* shaderProgram);
	~UniformManager();

	void SetUniform(const char* uniformName, UniformType type, void* data);

private:
	GLuint shaderPID;
};

