#pragma once

class SceneObject;
class Component;

#include "SceneObject.h"

template <class T>
using GuiSerialized = std::vector<std::pair<std::string, T*>>;

class Component
{
public:
	SceneObject* sceneObject;
	std::string name;

	Component();

	void LinkSceneObject(SceneObject* sceneObject);

	virtual void InitializeComponent() {};
	virtual void Serialize();

	void SerializeFloat1(std::string name, GLfloat* float1);
	void SerializeFloat2(std::string name, glm::vec2* float2);
	void SerializeFloat3(std::string name, glm::vec3* float3);

	GuiSerialized<GLfloat>* GetFloat1s();
	GuiSerialized<glm::vec2>* GetFloat2s();
	GuiSerialized<glm::vec3>* GetFloat3s();
	
private:
	GuiSerialized<GLfloat> float1s;
	GuiSerialized<glm::vec2> float2s;
	GuiSerialized<glm::vec3> float3s;

	void cpyVec2ToArr(glm::vec2* vec, GLfloat arr[2]);
	void cpyVec3ToArr(glm::vec3* vec, GLfloat arr[3]);
};

