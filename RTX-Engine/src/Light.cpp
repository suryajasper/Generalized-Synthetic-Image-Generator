#include "Light.h"

Light::Light(GLfloat intensity, GLfloat radius, glm::vec3 color)
{
	this->intensity = intensity;
	this->radius = radius;
	this->color = color;
}

Light::Light()
{
	this->intensity = 1.0f;
	this->radius = glm::radians(45.0f);
	this->color = glm::vec3(235, 225, 178) / 255.0f;
}

Light::~Light()
{
}

void Light::SetIntensity(GLfloat intensity)
{
	this->intensity = intensity;
}

void Light::SetRadius(GLfloat radius)
{
	this->radius = radius;
}

void Light::SetColor(GLfloat r, GLfloat g, GLfloat b)
{
	this->color = { r, g, b };
}
