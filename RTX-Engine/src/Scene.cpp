#include "Scene.h"

Scene::Scene(GLFWwindow* window)
{
	this->window = window;
    this->light = nullptr;
    this->camera = nullptr;

    this->ui = new UIManager(window);
}

Scene::~Scene() 
{
    for (Model* sceneObj : models)
        delete sceneObj;

    delete ui;
    delete light;
    delete camera;
}

void Scene::SetCamera(Camera* camera)
{
	this->camera = camera;
    sceneObjects.push_back(std::make_pair("Camera", camera));
}

void Scene::SetLight(Light* light)
{
    this->light = light;

    for (Model* sceneObj : models)
        sceneObj->SetLight(light);

    sceneObjects.push_back(std::make_pair("Light", light));
}

void Scene::AddSceneObject(std::string name, Model* sceneObj)
{
    sceneObj->SetLight(light);
    models.push_back(sceneObj);
    sceneObjects.push_back(std::make_pair(name, sceneObj));

    for (SceneObject s : sceneObjects) {
        std::cout << s.first << " " << s.second << std::endl;
    }
}

void Scene::AddSceneObject(Model* sceneObj)
{
    AddSceneObject("Untitled " + std::to_string(models.size()), sceneObj);
}

void Scene::Render()
{
    glClearColor(0.0f, 0.3f, 0.3f, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);

    for (Model* sceneObj : models)
        sceneObj->Draw(camera);

    ui->DisplaySceneObjectControls(&sceneObjects);

    glfwSwapBuffers(window);
}
