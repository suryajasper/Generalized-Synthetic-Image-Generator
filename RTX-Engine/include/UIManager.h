#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <stdio.h>

#include "Scene.h"
#include "Transformable.h"
#include "GuiSerializable.h"

typedef std::pair<std::string, GuiSerializable*> SceneObject;

template<typename Base, typename T>
inline bool instanceof(const T* ptr) {
	return dynamic_cast<const Base*>(ptr) != nullptr;
}

class UIManager
{
public:
	UIManager(GLFWwindow* window);
	~UIManager();

	void DisplaySceneObjectControls(std::vector<SceneObject>* sceneObjects);

private:
	void cpyVec2ToArr(glm::vec2* vec, GLfloat arr[2]);
	void cpyVec3ToArr(glm::vec3* vec, GLfloat arr[3]);
	void Initialize(GLFWwindow* window);
};

