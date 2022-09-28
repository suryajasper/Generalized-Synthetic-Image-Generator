#pragma once
#include "Camera.h"
#include "Model.h"
#include "Light.h"
#include <vector>

class Scene
{
public:
	Scene(GLFWwindow* window);
	~Scene();

	void SetCamera(Camera* camera);
	void SetLight(Light* light);
	void AddSceneObject(Model* sceneObj);
	void Render();
private:
	GLFWwindow* window;
	Camera* camera;
	Light* light;

	std::vector<Model*> sceneObjects;
};

