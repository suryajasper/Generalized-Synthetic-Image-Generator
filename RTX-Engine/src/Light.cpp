#include "Light.h"

void Light::InitializeComponent()
{
	this->intensity = 1.0f;
	this->color = glm::vec3(235, 225, 178) / 255.0f;

	name = "Light";

	Serialize();
}

void Light::Serialize()
{
	SerializeFloat1("Intensity", &intensity);
	SerializeFloat3("Color", &color);
}

void Light::SetIntensity(GLfloat intensity)
{
	this->intensity = intensity;
}

void Light::SetColor(GLfloat r, GLfloat g, GLfloat b)
{
	this->color = { r, g, b };
}
