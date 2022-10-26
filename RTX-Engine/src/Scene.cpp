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
    for (SceneObject* sceneObj : sceneObjects)
        delete sceneObj;

    delete ui;
    delete light;
    delete camera;
}

void Scene::GetRenderables(SceneObject* root, std::vector<Model*>& modelsOut)
{
    std::vector<SceneObject*> children;

    if (root == nullptr) 
        children = sceneObjects;
    else {
        children = root->children;

        Model* pModel = root->GetComponent<Model>();
        if (pModel != nullptr)
            modelsOut.push_back(pModel);
    }

    if (!children.empty())
        for (SceneObject* sceneObj : children)
            GetRenderables(sceneObj, modelsOut);
}

void Scene::GetRenderables(std::vector<Model*>& modelsOut)
{
    GetRenderables(nullptr, modelsOut);
}

void Scene::SetCamera(SceneObject* camera)
{
    Camera* camComp = camera->GetComponent<Camera>();
    if (camComp != nullptr) {
	    this->camera = camComp;
        sceneObjects.push_back(camera);
    }
}

void Scene::SetLight(SceneObject* light)
{
    Light* lightComp = light->GetComponent<Light>();
    if (lightComp != nullptr) {
        this->light = lightComp;

        std::vector<Model*> models; 
        GetRenderables(models);
        for (Model* model : models)
            model->SetLight(lightComp);

        sceneObjects.push_back(light);
    }
}

void Scene::AddSceneObject(SceneObject* sceneObj)
{
    std::vector<Model*> models;
    GetRenderables(sceneObj, models);
    for (Model* model : models)
        model->SetLight(light);

    sceneObjects.push_back(sceneObj);
}

void Scene::Render()
{
    glClearColor(0.0f, 0.3f, 0.3f, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);

    std::queue<SceneObject*> renderQueue; 
    for (auto iter : sceneObjects) renderQueue.push(iter);

    while (!renderQueue.empty()) {
        SceneObject* sceneObj = renderQueue.front();
        renderQueue.pop();

        Model* pModel = sceneObj->GetComponent<Model>();
        if (pModel != nullptr)
            pModel->Draw(camera);

        for (auto iter : sceneObj->children) renderQueue.push(iter);
    }

    // ui->DisplaySceneObjectControls(&sceneObjects);

    glfwSwapBuffers(window);
}
