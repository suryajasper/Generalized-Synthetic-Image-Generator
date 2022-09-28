#include "Transformable.h"

Transformable::Transformable()
{
	this->position = new glm::vec3(0.0f);
	this->scale = new glm::vec3(1.0f);
	this->rotation = new glm::quat(1.0f, 1.0f, 0.0f, 0.0f);
}

Transformable::~Transformable()
{
}

void Transformable::Rotate(glm::vec3* eulerAngles)
{
}

void Transformable::Translate(glm::vec3 deltaPos)
{
	*(this->position) += deltaPos;
}

void Transformable::SetPosition(GLfloat x, GLfloat y, GLfloat z)
{
	this->position = new glm::vec3(x, y, z);
}

void Transformable::SetScale(GLfloat scale)
{
	this->scale = new glm::vec3(scale);
}

void Transformable::SetScale(GLfloat x, GLfloat y, GLfloat z)
{
	this->scale = new glm::vec3(x, y, z);
}

void Transformable::SetRotation(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	this->rotation = new glm::quat(x, y, z, w);
}

glm::vec3* Transformable::GetPosition()
{
	return position;
}

glm::vec3* Transformable::GetScale()
{
	return scale;
}

glm::quat* Transformable::GetRotation()
{
	return rotation;
}
