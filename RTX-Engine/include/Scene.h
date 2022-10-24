#pragma once
#include "Camera.h"
#include "Model.h"
#include "Light.h"
#include "UIManager.h"

#include <map>
#include <vector>
#include <string>

class UIManager;

class Scene
{
public:
	Scene(GLFWwindow* window);
	~Scene();

	void SetCamera(Camera* camera);
	void SetLight(Light* light);

	void AddSceneObject(std::string name, Model* sceneObj);
	void AddSceneObject(Model* sceneObj);

	void Render();
private:
	GLFWwindow* window;
	UIManager* ui;
	Camera* camera;
	Light* light;

	std::vector<std::pair<std::string, GuiSerializable*> > sceneObjects;
	std::vector<Model*> models;
};

