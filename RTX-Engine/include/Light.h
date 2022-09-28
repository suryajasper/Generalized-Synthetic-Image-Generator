#pragma once
#include "glad/glad.h"
#include <glm/glm.hpp>
#include "Transformable.h"

class Light : public Transformable
{
public:
	Light(GLfloat intensity, GLfloat radius, glm::vec3 color);
	Light();
	~Light();

	void SetIntensity(GLfloat intensity);
	void SetRadius(GLfloat radius);
	void SetColor(GLfloat r, GLfloat g, GLfloat b);

	GLfloat intensity;
	GLfloat radius;
	glm::vec3 color;
};

