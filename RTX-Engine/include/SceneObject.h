#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Transformable;
class Component;

#include <iostream>
#include <vector>
#include <string>

template<typename Base, typename T>
inline bool instanceof(const T* ptr) {
	return dynamic_cast<const Base*>(ptr) != nullptr;
}

class SceneObject
{
public:
	std::string name;
	std::vector<SceneObject*> children;
	Transformable* transform;

	SceneObject(std::string name);
	SceneObject() : SceneObject("Scene Object " + std::to_string(sceneObjectCount)) {};
	~SceneObject();

	void AddChild(SceneObject* child);
	void RemoveChild(SceneObject* child);

	template <class CompType>
	CompType* AddComponent()
	{
		CompType* component = new CompType();
		component->LinkSceneObject(this);
		component->InitializeComponent();

		this->components.push_back(component);
		return component;
	};

	template <class CompType>
	CompType* GetComponent()
	{
		for (Component* comp : this->components)
			if (instanceof<CompType>(comp))
				return (CompType*)comp;

		return nullptr;
	};

	template <class CompType>
	void RemoveComponent()
	{
		for (unsigned int i = 0; i < components.size(); i++) {
			if (instanceof<CompType>(components[i])) {
				delete components[i];
				components.erase(components.begin() + i);
				return;
			}
		}
	};

protected:
	static unsigned int sceneObjectCount;
	std::vector<Component*> components;
};