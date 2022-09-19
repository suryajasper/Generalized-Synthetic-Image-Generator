#pragma once
#include <string>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "ShaderProgram.h"

class Camera
{
public:
	ShaderProgram* shaderProgram;
	GLFWwindow* window;

	glm::vec3 position;
	glm::vec3 rotation;

	GLfloat aspectRatio = 1.0f;
	GLfloat fov = 45.0f;
	GLfloat minDist = 0.1f, maxDist = 100.0f;

	GLfloat speed = 25.0f;

	Camera(GLFWwindow* window, ShaderProgram* shaderProgram);
	Camera(GLFWwindow* window, ShaderProgram* shaderProgram, GLfloat aspectRatio, GLfloat fov, GLfloat minDist, GLfloat maxDist);
	~Camera();

	void DispatchMatrices();
	void Update(float deltaTime);

	void Activate();
	void Deactivate();

private:
	float rot = 0.0f;
};
