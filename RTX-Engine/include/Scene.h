#pragma once
#include "Model.h"
#include "Camera.h"
#include "Light.h"
#include "SceneObject.h"
#include "UIManager.h"

#include <map>
#include <vector>
#include <queue>
#include <string>

class UIManager;

class Scene
{
public:
	Scene(GLFWwindow* window);
	~Scene();

	void GetRenderables(SceneObject* root, std::vector<Model*>& modelsOut);
	void GetRenderables(std::vector<Model*>& modelsOut);

	void SetCamera(SceneObject* camera);
	void AddLight(SceneObject* light);
	void AddSceneObject(SceneObject* sceneObj);

	void Render();
private:
	GLFWwindow* window;
	UIManager* ui;
	Camera* camera;

	std::vector<Light*> lights;
	std::vector<SceneObject*> sceneObjects;
};

