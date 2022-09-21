#include "VAO.h"

VAO::VAO(GLuint numVertices, GLuint numIndices)
{
	this->numVertices = numVertices;
	this->numIndices = numIndices;
	this->bufferLocs = new GLuint[maxAttributes];

	glGenVertexArrays(1, &id);
}

VAO::~VAO()
{
	glDeleteVertexArrays(1, &id);
	for (unsigned int i = 0; i < maxAttributes; i++) {
		glDeleteBuffers(1, bufferLocs+i);
	}
}

void VAO::Bind()
{
	glBindVertexArray(id);
}

void VAO::Unbind()
{
	glBindVertexArray(0);
}

void VAO::AddIndices(GLuint* indexBuffer) 
{
	Bind();

	GLuint bufferSize = numIndices * sizeof(GLuint);
	GLuint* EBOLoc = bufferLocs + numAttributes;

	glGenBuffers(1, EBOLoc);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBOLoc);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferSize, indexBuffer, GL_STATIC_DRAW);

	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	Unbind();

	numAttributes++;
}

void VAO::AddVertexAttribute(GLuint attribLoc, GLuint numComponents, GLfloat* bufferData, GLboolean normalized)
{
	Bind();

	// calculating stride and size for buffer and allotting memory address
	GLuint bufferStride = numComponents * sizeof(GLfloat);
	GLuint bufferSize = numVertices * bufferStride;
	GLuint* bufferLoc = bufferLocs + numAttributes;

	// sending buffer data to GPU
	glGenBuffers(1, bufferLoc);
	glBindBuffer(GL_ARRAY_BUFFER, *bufferLoc);
	glBufferData(GL_ARRAY_BUFFER, bufferSize, bufferData, GL_STATIC_DRAW);

	// assigning attribute information to vertex shader
	glVertexAttribPointer(attribLoc, numComponents, GL_FLOAT, normalized, bufferStride, (void*)totalStride);
	glEnableVertexAttribArray(attribLoc);

	// unbinding array buffer & vertex array
	// glBindBuffer(GL_ARRAY_BUFFER, 0);
	Unbind();

	// appropriately incrementing stride and number of attributes added
	totalStride += bufferStride;
	numAttributes++;
}

void VAO::AddVertexAttribute(GLuint attribLoc, GLuint numComponents, GLfloat* bufferData)
{
	AddVertexAttribute(attribLoc, numComponents, bufferData, GL_FALSE);
}

