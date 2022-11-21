#pragma once
#include "glad/glad.h"
#include <glm/glm.hpp>
#include "Transformable.h"

class Light : public Component
{
public:
	void InitializeComponent() override;
	void Serialize() override;

	void SetIntensity(GLfloat intensity);
	void SetColor(GLfloat r, GLfloat g, GLfloat b);

	GLfloat intensity;
	glm::vec3 color;
};
