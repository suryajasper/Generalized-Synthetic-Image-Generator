#pragma once
#include <string>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "UniformManager.h"
#include "ShaderProgram.h"
#include "Transformable.h"

class Camera : Transformable
{
public:
	GLFWwindow* window;

	glm::vec3 rotation;

	Camera(GLFWwindow* window);
	~Camera();

	void ViewProjMatrices(glm::mat4& view, glm::mat4& proj);
	void Update(float deltaTime);

	void SetAspectRatio(GLfloat aspectRatio);
	void SetFOV(GLfloat fov);
	void SetClippingDistance(GLfloat minDist, GLfloat maxDist);

	void Activate();
	void Deactivate();

private:
	GLfloat aspectRatio = 1.0f;
	GLfloat fov = 45.0f;
	GLfloat minDist = 0.1f, maxDist = 100.0f;

	GLfloat speed = 20.0f;

	glm::vec3 trans = { 0, 0, 0 };

	bool firstClick = false;
	float rot = 0.0f;
};
