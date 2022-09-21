#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VAO
{
public:
	GLuint id;

	VAO(GLuint numVertices, GLuint numIndices);
	~VAO();

	void Bind();
	void Unbind();

	/*
	GLuint BindVBO(GLintptr vertSize, GLfloat* vertices);
	GLuint BindEBO(GLintptr indSize, GLuint* indices);
	*/

	void AddIndices(GLuint* indexBuffer);

	void AddVertexAttribute(GLuint attribLoc, GLuint numComponents, GLfloat* bufferData, GLboolean normalized);
	void Fuck();
	void AddVertexAttribute(GLuint attribLoc, GLuint numComponents, GLfloat* bufferData);

private:
	GLuint* bufferLocs;

	GLuint numVertices;
	GLuint numIndices;
	GLuint maxAttributes = 4;
	GLuint numAttributes = 0;
	GLuint totalStride = 0;
};

