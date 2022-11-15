#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <glm/glm.hpp>
#include "glm/gtc/type_ptr.hpp"
#include <glad/glad.h>

enum UniformType
{
	UNIFORM_MAT4X4,
	UNIFORM_VEC3,
	UNIFORM_VEC2,
	UNIFORM_FLOAT,
	UNIFORM_INT,
};

class ShaderProgram
{
public:
	GLuint programId;

	ShaderProgram();
	~ShaderProgram();

	GLuint Initialize(std::string vertFile, std::string fragFile);

	static GLuint CreateShader(int shaderType, std::string path);

	void SetUniform(const char* uniformName, UniformType type, void* data);

	void AttachShader(GLuint shaderId);
	void DeleteShader(GLuint shaderId);

	void BindProgram();
	void LinkProgram();

private:
	std::vector<GLuint> shaders;
	unsigned int numTextures;
	static void ReadShaderDataFromFile(std::string path, char** shaderData);
};

