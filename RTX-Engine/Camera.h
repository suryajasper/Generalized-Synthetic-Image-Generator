#pragma once
#include <string>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

class Camera
{
public:
	static Camera* main;

	glm::mat4x4 view;

	glm::vec3 position;
	glm::vec3 rotation;

	GLfloat fov = 45.0f;
	GLfloat minDist = 10.0f, maxDist = 100.0f;

	Camera();
	~Camera();

	void Activate();
	void Deactivate();
};

