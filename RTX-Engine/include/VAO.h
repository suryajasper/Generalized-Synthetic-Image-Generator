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
	
	GLuint CreateEBO(GLuint* indexBuffer);
	GLuint CreateVBO(GLuint bufferSize, GLfloat* vertexBuffer);

	void LinkVertexAttribute(GLuint attribLoc, GLuint numComponents);

private:
	GLuint* bufferLocs;

	GLuint VBO, EBO;

	GLuint numVertices;
	GLuint numIndices;
	GLuint maxAttributes = 4;
	GLuint numAttributes = 0;
	GLuint totalStride = 0;
};

