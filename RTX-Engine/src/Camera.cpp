#include "Camera.h"

Camera::Camera(GLFWwindow* window)
{
	SetPosition(0.0f, 0.0f, 2.0f);
	rotation = { 0.0f, 0.0f, -1.0f };

	this->window = window;
}

Camera::~Camera()
{
}

void Camera::ViewProjMatrices(glm::mat4& view, glm::mat4& proj)
{
	glm::vec3 position = *GetPosition();
	
	view = glm::mat4x4(1.0f);
	proj = glm::mat4x4(1.0f);

	view = glm::lookAt(position, position + rotation, {0, 1, 0});
	proj = glm::perspective(glm::radians(fov), aspectRatio, minDist, maxDist);
}

void Camera::Update(float deltaTime)
{
	static float total = 0;

	glm::vec3 upVec = { 0, 1, 0 };

	trans = glm::vec3(0, glm::sin(total), 0);

	rot += speed * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		rotation.y +=  speed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		rotation.y += -speed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		rotation.x += speed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		rotation.x += -speed * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		Translate(  speed * deltaTime * rotation );
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		Translate( -speed * deltaTime * rotation );
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		Translate(  speed * deltaTime *  glm::normalize(glm::cross(rotation, upVec)) );
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		Translate(  speed * deltaTime * -glm::normalize(glm::cross(rotation, upVec)) );

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		Translate(  speed * deltaTime * upVec );
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		Translate( -speed * deltaTime * upVec );

	total += deltaTime;
}

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

