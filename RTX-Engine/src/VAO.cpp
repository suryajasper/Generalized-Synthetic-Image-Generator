#include "VAO.h"

VAO::VAO(GLintptr vertSize, GLfloat* vertices, GLintptr indSize, GLuint* indices)
{
	glGenVertexArrays(1, &id);

	GLuint VBO, EBO;

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	this->bufferObjs.push_back(BindVBO(vertSize, vertices));
	this->bufferObjs.push_back(BindEBO(indSize, indices));

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	// glVertexAttribPointer(1, 3, GL_FLOAT, false, 3 * sizeof(float), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(0);

	Unbind();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

VAO::~VAO()
{
	glDeleteVertexArrays(1, &id);
	for (GLuint buff : bufferObjs)
		glDeleteBuffers(1, &buff);
}

void VAO::Bind()
{
	glBindVertexArray(id);
}

void VAO::Unbind()
{
	glBindVertexArray(0);
}

GLuint VAO::BindVBO(GLintptr vertSize, GLfloat* vertices)
{
	GLuint VBO;

	glGenBuffers(1, &VBO);

	Bind();
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertSize, vertices, GL_STATIC_DRAW);

	return VBO;
}

GLuint VAO::BindEBO(GLintptr indSize, GLuint* indices)
{
	GLuint EBO;

	glGenBuffers(1, &EBO);

	Bind();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indSize, indices, GL_STATIC_DRAW);

	return EBO;
}

