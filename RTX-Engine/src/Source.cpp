#include "Model.h"
#include "Camera.h"
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

    Model* monkey = new Model();
    monkey->LoadMesh("resources/monkey.obj");
    monkey->LinkTexture("resources/images/bricktex.jpg");

    Model* cube = new Model();
    cube->LoadMesh("resources/cube.obj");
    cube->LinkTexture("resources/images/Clay-Bricks-1.png");

    Camera* camera = new Camera(window);
    camera->SetAspectRatio((GLfloat)width / height);

    float prevTime = glfwGetTime() - 4.0f;

    while (!glfwWindowShouldClose(window))
    {
        float currTime = glfwGetTime();
        float deltaTime = currTime - prevTime;

        if (deltaTime > (float)1/100) {
            glClearColor(0.0f, 0.3f, 0.3f, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            glClear(GL_DEPTH_BUFFER_BIT);

            camera->Update(deltaTime);

            prevTime = currTime;
            
            cube->SetPosition(-1, 0, 0);
            cube->Rotate(glm::vec3(1, 1, 0) * deltaTime);
            cube->Draw(camera);

            monkey->SetPosition(1, 0, 0);
            monkey->Rotate(glm::vec3(1, 1, 0) * -deltaTime);
            monkey->SetScale(glm::abs(glm::sin(glfwGetTime())));
            monkey->Draw(camera);

            glfwSwapBuffers(window);
        }

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}