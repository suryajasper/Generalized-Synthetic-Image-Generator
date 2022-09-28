#include "Scene.h"

Scene::Scene(GLFWwindow* window)
{
	this->window = window;
}

void Scene::SetCamera(Camera* camera)
{
	this->camera = camera;
}

void Scene::AddSceneObject(Model* sceneObj)
{
	sceneObjects.push_back(sceneObj);
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
