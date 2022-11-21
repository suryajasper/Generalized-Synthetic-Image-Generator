#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <stdio.h>

#include "Scene.h"
#include "SceneObject.h"
#include "Transformable.h"
#include "GuiSerializable.h"

class UIManager
{
public:
	UIManager(GLFWwindow* window, std::vector<SceneObject*>* sceneObjects);
	~UIManager();

	void DrawTree(SceneObject* node);
	void DisplaySceneHierarchy();
	void DisplaySceneObjectComponents();

	void DisplaySceneObjectControls();

private:
	std::vector<SceneObject*>* sceneObjects;
	SceneObject* active;
	GLFWwindow* window;

	void cpyVec2ToArr(glm::vec2* vec, GLfloat arr[2]);
	void cpyVec3ToArr(glm::vec3* vec, GLfloat arr[3]);
	void Initialize(GLFWwindow* window);
};

