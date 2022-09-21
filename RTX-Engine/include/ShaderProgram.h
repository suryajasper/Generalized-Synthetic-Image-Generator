#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <glad/glad.h>

class ShaderProgram
{
public:
	GLuint programId;

	ShaderProgram();
	~ShaderProgram();

	GLuint Initialize(std::string vertFile, std::string fragFile);

	static GLuint CreateShader(int shaderType, std::string path);

	void AttachShader(GLuint shaderId);
	void DeleteShader(GLuint shaderId);

	void BindProgram();
	void LinkProgram();

private:
	std::vector<GLuint> shaders;
	static void ReadShaderDataFromFile(std::string path, char** shaderData);
};
