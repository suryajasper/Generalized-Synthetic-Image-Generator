#include "Scene.h"

Scene::Scene(GLFWwindow* window)
{
	this->window = window;
    this->light = nullptr;
}

Scene::~Scene() 
{
    for (Model* sceneObj : sceneObjects)
        delete sceneObj;

    delete light;
    delete camera;
}

void Scene::SetCamera(Camera* camera)
{
	this->camera = camera;
}

void Scene::SetLight(Light* light)
{
    this->light = light;

    for (Model* sceneObj : sceneObjects)
        sceneObj->SetLight(light);
}

void Scene::AddSceneObject(std::string name, Model* sceneObj)
{
    sceneObj->SetLight(light);
    sceneObjects.push_back(sceneObj);
}

void Scene::AddSceneObject(Model* sceneObj)
{
    AddSceneObject("Untitled " + std::to_string(sceneObjects.size()), sceneObj);
}

void Scene::Render()
{
    glClearColor(0.0f, 0.3f, 0.3f, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);

    for (Model* sceneObj : sceneObjects)
        sceneObj->Draw(camera);

    glfwSwapBuffers(window);
}
