#include "Camera.h"

Camera::Camera() 
{
	if (main == nullptr)
		Activate();

	view = glm::mat4x4();
	position = glm::vec3();
	rotation = glm::vec3();
}

Camera::~Camera()
{
	delete main;
}

void Camera::Activate()
{
	this->main = this;
}

void Camera::Deactivate()
{
	this->main = nullptr;
}

