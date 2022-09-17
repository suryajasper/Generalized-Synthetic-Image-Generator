#pragma once

#include <string>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VAO
{
public:
	GLuint id;

	VAO(GLintptr vertSize, GLfloat* vertices, GLintptr indSize, GLuint* indices);
	~VAO();

	void Bind();
	void Unbind();

	GLuint BindVBO(GLintptr vertSize, GLfloat* vertices);
	GLuint BindEBO(GLintptr indSize, GLuint* indices);

private:
	std::vector<GLuint> bufferObjs;

};

