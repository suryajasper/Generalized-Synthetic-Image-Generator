#include "Transformable.h"
#include "SceneObject.h"

unsigned int SceneObject::sceneObjectCount = 0;

SceneObject::SceneObject(std::string name)
{
	active = true;

	sceneObjectCount++;

	Transformable* transform = new Transformable();
	transform->InitializeComponent();
	this->components.push_back(transform);
	this->transform = transform;
	
	this->name = name;
}

SceneObject::~SceneObject()
{
	delete transform;

	for (Component* comp : this->components)
		delete comp;

	for (SceneObject* obj : this->children)
		delete obj;
}

void SceneObject::AddChild(SceneObject* child)
{
	this->children.push_back(child);
}

void SceneObject::RemoveChild(SceneObject* child)
{
	for (unsigned int i = 0; i < children.size(); i++) {
		if (children[i] == child) {
			delete child;
			children.erase(children.begin() + i);
			return;
		}
	}
}