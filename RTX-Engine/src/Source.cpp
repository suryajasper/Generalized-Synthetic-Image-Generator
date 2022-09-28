#include "Model.h"
#include "Camera.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLuint width = 1200, height = 800;

    window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    gladLoadGL();
    glViewport(0, 0, width, height);

    Model* cube = new Model();
    cube->LoadMesh("resources/cube.obj");
    cube->LinkTexture("resources/images/Clay-Bricks-1.png");

    Model* cube2 = new Model();
    cube2->LoadMesh("resources/cube.obj");
    cube2->LinkTexture("resources/images/Clay-Bricks-1.png");

    Camera* camera = new Camera(window);
    camera->SetAspectRatio((float) width / height);

    glfwSwapBuffers(window);

    glEnable(GL_DEPTH_TEST);

    float prevTime = glfwGetTime() - 4.0f;

    /* Loop until the user closes the window */

    while (!glfwWindowShouldClose(window))
    {
        /* Render here */

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

            cube2->SetPosition(1, 0, 0);
            cube2->Rotate(glm::vec3(1, 1, 0) * -deltaTime);
            cube2->Draw(camera);
            glfwSwapBuffers(window);
        }

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}