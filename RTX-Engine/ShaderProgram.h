#pragma once
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <glad/glad.h>

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();

	GLuint Initialize(std::string vertFile, std::string fragFile);

	static GLuint CreateShader(int shaderType, std::string path);

	void AttachShader(GLuint shaderId);
	void DeleteShader(GLuint shaderId);

	void BindProgram();
	void LinkProgram();

private:
	GLuint programId;
	std::vector<GLuint> shaders;
	static char** ReadShaderDataFromFile(std::string path);
};

