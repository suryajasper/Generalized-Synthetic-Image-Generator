#include "Camera.h"

Camera::Camera(GLFWwindow* window, ShaderProgram* shaderProgram)
{
	SetPosition(0.0f, 0.0f, 2.0f);
	rotation = { 0.0f, 0.0f, -1.0f };

	this->window = window;
	this->shaderProgram = shaderProgram;
	this->uniformManager = new UniformManager(shaderProgram);
}

Camera::Camera(GLFWwindow* window, ShaderProgram* shaderProgram, GLfloat aspectRatio, GLfloat fov, GLfloat minDist, GLfloat maxDist)
{
	SetPosition(0.0f, 0.0f,  2.0f);
	rotation = { 0.0f, 0.0f, -1.0f };

	this->window = window;
	this->shaderProgram = shaderProgram;
	this->uniformManager = new UniformManager(shaderProgram);
	
	this->aspectRatio = aspectRatio;
	this->fov = fov;
	this->minDist = minDist;
	this->maxDist = maxDist;
}

Camera::~Camera()
{
	delete shaderProgram;
}

void Camera::DispatchMatrices() 
{
	shaderProgram->BindProgram();

	glm::vec3 position = *GetPosition();

	glm::mat4x4 model = glm::mat4x4(1.0f);
	glm::mat4x4 view = glm::mat4x4(1.0f);
	glm::mat4x4 proj = glm::mat4x4(1.0f);

	model = glm::rotate(model, glm::radians(rot), { 0, 1, 0 });
	view = glm::lookAt(position, position + rotation, {0, 1, 0});
	proj = glm::perspective(glm::radians(fov), aspectRatio, minDist, maxDist);

	glm::mat4x4 MPV = proj * view * model;

	uniformManager->SetUniform("MPV", UNIFORM_MAT4X4, &MPV);
}

void Camera::Update(float deltaTime)
{
	glm::vec3 upVec = { 0, 1, 0 };

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

