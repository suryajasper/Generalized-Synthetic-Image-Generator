#include "Camera.h"

Camera::Camera(GLFWwindow* window, ShaderProgram* shaderProgram)
{
	position = { 0.0f, 0.5f,  2.0f };
	rotation = { 0.0f, 0.0f, -1.0f };

	this->window = window;
	this->shaderProgram = shaderProgram;
}

Camera::Camera(GLFWwindow* window, ShaderProgram* shaderProgram, GLfloat aspectRatio, GLfloat fov, GLfloat minDist, GLfloat maxDist)
{
	position = { 0.0f, 0.5f,  2.0f };
	rotation = { 0.0f, 0.0f, -1.0f };

	this->window = window;
	this->shaderProgram = shaderProgram;
	
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

	GLuint modelLoc = glGetUniformLocation(shaderProgram->programId, "model");
	GLuint viewLoc = glGetUniformLocation(shaderProgram->programId, "view");
	GLuint projLoc = glGetUniformLocation(shaderProgram->programId, "proj");

	glm::mat4x4 model = glm::mat4x4(1.0f);
	glm::mat4x4 view = glm::mat4x4(1.0f);
	glm::mat4x4 proj = glm::mat4x4(1.0f);

	model = glm::rotate(model, glm::radians(rot), { 0, 1, 0 });

	// view = glm::translate(view, { 0, 0, -2.0f }); 
	view = glm::lookAt(position, position + rotation, glm::vec3(0.0f, 1.0f, 0.0f));
	proj = glm::perspective(glm::radians(fov), aspectRatio, minDist, maxDist);

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
}

void Camera::Update(float deltaTime)
{
	glm::vec3 upVec = { 0, 1, 0 };

	rot += speed * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		position +=  speed * deltaTime * rotation;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		position += -speed * deltaTime * rotation;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		position +=  speed * deltaTime *  glm::normalize(glm::cross(rotation, upVec));
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		position +=  speed * deltaTime * -glm::normalize(glm::cross(rotation, upVec));

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		position +=  speed * deltaTime * upVec;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		position += -speed * deltaTime * upVec;
}

void Camera::Activate()
{

}

void Camera::Deactivate()
{

}

