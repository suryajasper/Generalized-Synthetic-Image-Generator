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

    SceneObject* diffuseLight = new SceneObject("Diffuse Light");
    diffuseLight->transform->SetPosition(1.0f, 1.5f, 2.0f);
    Light* lightComp = diffuseLight->AddComponent<Light>();
    lightComp->SetIntensity(1.4f);
    lightComp->SetColor(150 / 255.0f, 108 / 255.0f, 224 / 255.0f);

    Scene* scene = new Scene(window);
    scene->SetCamera(camera);
    scene->SetLight(diffuseLight);

    SceneObject* car = new SceneObject("Car");
    Model* carModel = car->AddComponent<Model>();
    carModel->LoadMesh("resources/models/car.obj");
    carModel->LinkTexture("resources/images/car-tex.jpg");
    scene->AddSceneObject(car);

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

            car->transform->Rotate(glm::vec3(0, 1, 0) * deltaTime);
            // diffuseLight->SetPosition(camera->position);

            scene->Render();

            prevTime = currTime;
        }

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}