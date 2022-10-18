#include "Model.h"
#include "Camera.h"
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

    Camera* camera = new Camera(window);
    camera->SetAspectRatio((GLfloat)width / height);

    Light* diffuseLight = new Light();
    diffuseLight->SetPosition(1.0f, 1.5f, 2.0f);
    diffuseLight->SetIntensity(1.4f);
    diffuseLight->SetColor(150 / 255.0f, 108 / 255.0f, 224 / 255.0f);

    Scene* scene = new Scene(window);
    scene->SetCamera(camera);
    scene->SetLight(diffuseLight);

    /*
    Model* monkey = new Model();
    monkey->LoadMesh("resources/models/monkey.obj");
    monkey->LinkTexture("resources/images/bricktex.jpg");
    scene->AddSceneObject(monkey);

    Model* cube = new Model();
    cube->LoadMesh("resources/models/cube.obj");
    cube->LinkTexture("resources/images/Clay-Bricks-1.png");
    scene->AddSceneObject(cube);
    */

    Model* car = new Model();
    car->LoadMesh("resources/models/low-res-sphere.obj");
    car->LinkTexture("resources/images/bricktex.jpg");
    scene->AddSceneObject(car);

    float prevTime = glfwGetTime();

    while (!glfwWindowShouldClose(window))
    {
        float currTime = glfwGetTime();
        float deltaTime = currTime - prevTime;

        if (deltaTime > (float)1/100) {

            camera->Update(deltaTime);
            
            /*
            cube->SetPosition(-1, 0, 0);
            cube->Rotate(glm::vec3(1, 1, 0) * deltaTime);

            monkey->SetPosition(1, 0, 0);
            monkey->Rotate(glm::vec3(1, 1, 0) * -deltaTime);
            monkey->SetScale(glm::abs(glm::sin(glfwGetTime())));
            */

            car->Rotate(glm::vec3(0, 1, 0) * deltaTime);
            diffuseLight->SetPosition(camera->position);

            scene->Render();

            prevTime = currTime;
        }

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}