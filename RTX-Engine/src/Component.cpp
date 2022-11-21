#include "Component.h"

Component::Component()
{
	this->sceneObject = nullptr;
    this->name = "Component";
}

void Component::LinkSceneObject(SceneObject* sceneObject)
{
	this->sceneObject = sceneObject;
}

void Component::SerializeFloat1(std::string name, GLfloat* float1)
{
    float1s.push_back(std::make_pair(name, float1));
}

void Component::SerializeFloat2(std::string name, glm::vec2* float2)
{
    float2s.push_back(std::make_pair(name, float2));
}

void Component::SerializeFloat3(std::string name, glm::vec3* float3)
{
    float3s.push_back(std::make_pair(name, float3));
}

GuiSerialized<GLfloat>* Component::GetFloat1s()
{
    return &float1s;
}

void Component::Serialize()
{
}

GuiSerialized<glm::vec2>* Component::GetFloat2s()
{
    return &float2s;
}

GuiSerialized<glm::vec3>* Component::GetFloat3s()
{
    return &float3s;
}

void Component::cpyVec2ToArr(glm::vec2* vec, GLfloat arr[2])
{
    arr[0] = vec->x;
    arr[1] = vec->y;
}

void Component::cpyVec3ToArr(glm::vec3* vec, GLfloat arr[3])
{
    arr[0] = vec->x;
    arr[1] = vec->y;
    arr[2] = vec->z;
}