#include "VAO.h"

VAO::VAO(GLuint numVertices, GLuint numIndices, GLuint maxAttributes)
{
	this->maxAttributes = maxAttributes;
	this->numVertices = numVertices;
	this->numIndices = numIndices;
	this->bufferLocs = new GLuint[maxAttributes];

	glGenVertexArrays(1, &id);
}

VAO::~VAO()
{
	glDeleteVertexArrays(1, &id);
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &VBO);
}

void VAO::Bind()
{
	glBindVertexArray(id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
}

void VAO::Unbind()
{
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLuint VAO::CreateEBO(GLuint* indexBuffer) 
{
	std::cout << "EBO " << numIndices << std::endl;

	Bind();

	GLuint bufferSize = numIndices * sizeof(GLuint);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferSize, indexBuffer, GL_STATIC_DRAW);
	
	Unbind();

	return EBO;
}

GLuint VAO::CreateVBO(GLuint bufferSize, GLfloat* vertexBuffer)
{
	std::cout << "VBO " << numVertices << " " << bufferSize << std::endl;

	Bind();

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, bufferSize, vertexBuffer, GL_STATIC_DRAW);

	Unbind();
	
	return VBO;
}

void VAO::LinkVertexAttribute(GLuint attribLoc, GLuint numComponents)
{
	std::cout << "VERT_ATTR " << attribLoc << " " << numComponents << std::endl;

	// binding vertex array and buffer objects
	Bind();

	// calculating stride and size for buffer and allotting memory address
	GLuint bufferStride = maxAttributes * sizeof(GLfloat);
	GLuint* bufferLoc = bufferLocs + numAttributes;

	// assigning attribute information to vertex shader
	glVertexAttribPointer(attribLoc, numComponents, GL_FLOAT, GL_FALSE, bufferStride, (void*) (uintptr_t)totalStride);
	glEnableVertexAttribArray(attribLoc);
	
	// unbinding vertex array and buffer objects
	Unbind();

	// appropriately incrementing stride and number of attributes added
	totalStride += numComponents * sizeof(GLfloat);
	numAttributes++;
}