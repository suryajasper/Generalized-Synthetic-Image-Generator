#pragma once
#include <string>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "glm/gtc/type_ptr.hpp"
#include "ShaderProgram.h"

enum UniformType 
{
	UNIFORM_MAT4X4,
	UNIFORM_VEC3,
	UNIFORM_VEC2,
	UNIFORM_FLOAT,
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

