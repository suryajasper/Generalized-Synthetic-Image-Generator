#include "Camera.h"

void Camera::InitializeComponent()
{
	transform = sceneObject->transform;

	transform->SetPosition(0.0f, 0.0f,  2.0f);
	transform->SetRotation(0.0f, 0.0f, -1.0f);

	name = "Camera";

	Serialize();
}

void Camera::Serialize()
{
	SerializeFloat1("FOV", &fov);
	SerializeFloat1("Sensitivity", &speed);
}

void Camera::ViewProjMatrices(glm::mat4& view, glm::mat4& proj)
{	
	view = glm::mat4x4(1.0f);
	proj = glm::mat4x4(1.0f);

	view = glm::lookAt(transform->position, transform->position + transform->rotation, { 0, 1, 0 });
	proj = glm::perspective(glm::radians(fov), aspectRatio, minDist, maxDist);
}

/*
void Camera::Update(float deltaTime)
{
	static float total = 0;

	glm::vec3 upVec = { 0, 1, 0 };

	float rotSpeed = 1.0f;

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		transform->rotation.y += rotSpeed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		transform->rotation.y += -rotSpeed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		transform->rotation.x += rotSpeed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		transform->rotation.x += -rotSpeed * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		transform->Translate(speed * deltaTime * transform->rotation);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		transform->Translate(-speed * deltaTime * transform->rotation);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		transform->Translate(speed * deltaTime * glm::normalize(glm::cross(transform->rotation, upVec)));
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		transform->Translate(speed * deltaTime * -glm::normalize(glm::cross(transform->rotation, upVec)));

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		transform->Translate(speed * deltaTime * upVec);
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		transform->Translate( -speed * deltaTime * upVec );

	total += deltaTime;
}
*/

void Camera::SetAspectRatio(GLfloat aspectRatio)
{
	this->aspectRatio = aspectRatio;
}

void Camera::SetFOV(GLfloat fov)
{
	this->fov = fov;
}

void Camera::SetClippingDistance(GLfloat minDist, GLfloat maxDist)
{
	this->minDist = minDist;
	this->maxDist = maxDist;
}

void Camera::Activate()
{

}

void Camera::Deactivate()
{

}

