#pragma once

class SceneObject;
class Component;

#include "SceneObject.h"

class Component
{
public:
	Component();

	void LinkSceneObject(SceneObject* sceneObject);

	virtual void InitializeComponent() {};

	SceneObject* sceneObject;
};

