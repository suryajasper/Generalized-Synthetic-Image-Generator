#include "Component.h"

Component::Component()
{
	this->sceneObject = nullptr;
}

void Component::LinkSceneObject(SceneObject* sceneObject)
{
	this->sceneObject = sceneObject;
}
