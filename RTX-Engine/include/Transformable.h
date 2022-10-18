#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <GLFW/glfw3.h>

class Transformable
{
public:
	Transformable();
	~Transformable();

	void Rotate(glm::vec3 eulerAngles);
	void Translate(glm::vec3 deltaPos);

	void SetPosition(GLfloat x, GLfloat y, GLfloat z);
	void SetPosition(glm::vec3 position);
	void SetRotation(GLfloat x, GLfloat y, GLfloat z);
	void SetScale(GLfloat scale);

	glm::vec3 position;
	glm::vec3 rotation;
	GLfloat scale;
};

