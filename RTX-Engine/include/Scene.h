#pragma once
#include "Camera.h"
#include "Model.h"
#include <vector>

class Scene
{
public:
	Scene(GLFWwindow* window);

	void SetCamera(Camera* camera);
	void AddSceneObject(Model* sceneObj);
	void Render();
private:
	GLFWwindow* window;
	Camera* camera;

	std::vector<Model*> sceneObjects;
};

