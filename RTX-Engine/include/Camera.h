#pragma once
#include <string>
#include <vector>
#include <glad/glad.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "SceneObject.h"
#include "ShaderProgram.h"
#include "Transformable.h"
#include "Component.h"

class Camera : public Component, public GuiSerializable
{
public:
	void InitializeComponent() override;
	void Serialize() override;
	
	void ViewProjMatrices(glm::mat4& view, glm::mat4& proj);

	void SetAspectRatio(GLfloat aspectRatio);
	void SetFOV(GLfloat fov);
	void SetClippingDistance(GLfloat minDist, GLfloat maxDist);

	void Activate();
	void Deactivate();

private:
	Transformable* transform;

	GLfloat aspectRatio = 1.0f;
	GLfloat fov = 45.0f;
	GLfloat minDist = 0.1f, maxDist = 100.0f;

	GLfloat speed = 20.0f;

	bool firstClick = false;
};
