#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <stdio.h>

#include "Scene.h"
#include "SceneObject.h"
#include "Transformable.h"
#include "GuiSerializable.h"

typedef std::pair<std::string, GuiSerializable*> SceneObjectLegacy;

class UIManager
{
public:
	UIManager(GLFWwindow* window);
	~UIManager();

	void DisplaySceneObjectControls(std::vector<SceneObjectLegacy>* sceneObjects);

private:
	void cpyVec2ToArr(glm::vec2* vec, GLfloat arr[2]);
	void cpyVec3ToArr(glm::vec3* vec, GLfloat arr[3]);
	void Initialize(GLFWwindow* window);
};

