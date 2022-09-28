#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <GLFW/glfw3.h>

class Transformable
{
public:
	Transformable();
	~Transformable();

	void Rotate(glm::vec3* eulerAngles);
	void Translate(glm::vec3 deltaPos);

	void SetPosition(GLfloat x, GLfloat y, GLfloat z);
	void SetScale(GLfloat scale);
	void SetScale(GLfloat x, GLfloat y, GLfloat z);
	void SetRotation(GLfloat x, GLfloat y, GLfloat z, GLfloat w);

	glm::vec3* GetPosition();
	glm::vec3* GetScale();
	glm::quat* GetRotation();

private:
	glm::vec3* position;
	glm::vec3* scale;
	glm::quat* rotation;
};

