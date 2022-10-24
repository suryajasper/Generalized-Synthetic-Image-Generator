#include "Transformable.h"

Transformable::Transformable()
{
	this->position = glm::vec3(0.0f);
	this->scale = 1.0f;
	this->rotation = glm::vec3(0.0f);

	Serialize();
}

Transformable::~Transformable()
{
}

void Transformable::Rotate(glm::vec3 eulerAngles)
{
	rotation += eulerAngles;
}

void Transformable::Translate(glm::vec3 deltaPos)
{
	position += deltaPos;
}

void Transformable::SetPosition(GLfloat x, GLfloat y, GLfloat z)
{
	this->position = glm::vec3(x, y, z);
}

void Transformable::SetPosition(glm::vec3 position)
{
	this->position.x = position.x;
	this->position.y = position.y;
	this->position.z = position.z;
}

void Transformable::SetRotation(GLfloat x, GLfloat y, GLfloat z)
{
	this->rotation = glm::vec3(x, y, z);
}

void Transformable::SetScale(GLfloat scale)
{
	this->scale = scale;
}

void Transformable::Serialize()
{
	SerializeFloat1("Scale", &scale);
	SerializeFloat3("Position", &position);
	SerializeFloat3("Rotation", &rotation);
}