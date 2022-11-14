#include "Model.h"
#include "Camera.h"
#include "SceneObject.h"
#include "Scene.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

GLFWwindow* CreateWindow(const char* title, GLuint width, GLuint height)
{
    GLFWwindow* window;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window)
    {
        glfwTerminate();
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    gladLoadGL();
    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);

    return window;
}

int main(void)
{
    if (!glfwInit())
        return -1;

    GLuint width = 1200, height = 800;
    GLFWwindow* window = CreateWindow("Generalized Synthetic Image Generator", width, height);

    SceneObject* camera = new SceneObject("Camera");
    Camera* camComp = camera->AddComponent<Camera>();
    camComp->SetAspectRatio((GLfloat)width / height);

    GLfloat lightPositions[4][3] = {
        {3.0f, 3.0f, 4.0f},
        {2.0f, 2.0f, 2.0f},
        {-4.0f, -4.0f, -2.0f},
        {-3.0f, 3.0f, -4.0f},
    };
    GLfloat lightColors[4][3] = {
        {242, 208, 114},
        {226, 242, 121},
        {242, 169, 121},
        {117, 221, 240},
    };
    GLfloat lightIntensities[4] = { 0.8f, 0.8f, 1.3f, 0.4f };

    Scene* scene = new Scene(window);
    scene->SetCamera(camera);

    for (unsigned int i = 0; i < 4; i++) {
        SceneObject* diffuseLight = new SceneObject("Diffuse Light" + std::to_string(i));
        diffuseLight->transform->SetPosition(lightPositions[i][0], lightPositions[i][1], lightPositions[i][2]);
        Light* lightComp = diffuseLight->AddComponent<Light>();
        lightComp->SetIntensity(lightIntensities[i]);
        lightComp->SetColor(lightColors[i][0], lightColors[i][1], lightColors[i][2]);
        scene->AddLight(diffuseLight);
    }
    
    SceneObject* backpack = new SceneObject("backpack");
    Model* backpackModel = backpack->AddComponent<Model>();
    backpackModel->LoadMesh("resources/models/backpack/backpack-2.obj");
    backpackModel->LinkTexture(TEX_MAP_ROUGHNESS, "resources/models/backpack/roughness.jpg");
    backpackModel->LinkTexture(TEX_MAP_NORMAL   , "resources/models/backpack/normal.png");
    backpackModel->LinkTexture(TEX_MAP_SPECULAR , "resources/models/backpack/specular.jpg");
    backpackModel->LinkTexture(TEX_MAP_DIFFUSE  , "resources/models/backpack/diffuse.jpg");
    backpack->transform->SetScale(1.0f);
    scene->AddSceneObject(backpack);

    float prevTime = glfwGetTime();
    float total = 0;

    while (!glfwWindowShouldClose(window))
    {
        float currTime = glfwGetTime();
        float deltaTime = currTime - prevTime;

        if (deltaTime > (float)1/100) {
            Transformable* transform = camera->transform;

            glm::vec3 upVec = { 0, 1, 0 };

            float rotSpeed = 1.0f;
            float speed = 20.0f;

            if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
                transform->rotation.y += rotSpeed * deltaTime;
            if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
                transform->rotation.y += -rotSpeed * deltaTime;
            if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
                transform->rotation.x += rotSpeed * deltaTime;
            if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
                transform->rotation.x += -rotSpeed * deltaTime;

            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
                transform->Translate(speed * deltaTime * transform->rotation);
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
                transform->Translate(-speed * deltaTime * transform->rotation);
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
                transform->Translate(speed * deltaTime * glm::normalize(glm::cross(transform->rotation, upVec)));
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
                transform->Translate(speed * deltaTime * -glm::normalize(glm::cross(transform->rotation, upVec)));

            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
                transform->Translate(speed * deltaTime * upVec);
            if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
                transform->Translate(-speed * deltaTime * upVec);

            total += deltaTime;

            backpack->transform->Rotate(glm::vec3(0, 1, 0) * deltaTime);
            backpack->transform->position.y = 1.5f * glm::sin(0.8f * currTime);

            scene->Render();

            prevTime = currTime;
        }

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}