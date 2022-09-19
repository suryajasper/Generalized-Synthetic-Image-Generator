#include "ShaderProgram.h"
#include "Camera.h"
#include "VAO.h"
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
    GLuint width = 800, height = 800;

    window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    gladLoadGL();
    glViewport(0, 0, 800, 800);

    GLfloat vertices[] =
    {
        -1, -1,  1,
        1, -1,  1,
        1,  1,  1,
        -1,  1,  1,

        -1, -1, -1,
        -1,  1, -1,
        1,  1, -1,
        1, -1, -1,

        -1,  1, -1,
        -1,  1,  1,
        1,  1,  1,
        1,  1, -1,

        -1, -1, -1,
        1, -1, -1,
        1, -1,  1,
        -1, -1,  1,

        1, -1, -1,
        1,  1, -1,
        1,  1,  1,
        1, -1,  1,

        -1, -1, -1,
        -1, -1,  1,
        -1,  1,  1,
        -1,  1, -1
    };

    for (auto i = 0; i < sizeof(vertices) / sizeof(float); i++) {
        vertices[i] /= 5.0f;
    }

    GLuint indices[] = {
        0, 1, 2, 0, 2, 3,
        4, 5, 6, 4, 6, 7,
        8, 9, 10, 8, 10, 11,
        12, 13, 14, 12, 14, 15,
        16, 17, 18, 16, 18, 19,
        20, 21, 22, 20, 22, 23
    };

    ShaderProgram* shaderProgram = new ShaderProgram();
    shaderProgram->Initialize("resources/shaders/default.vert", "resources/shaders/default.frag");

    VAO* VertArray = new VAO(sizeof(vertices), vertices, sizeof(indices), indices);

    Camera* camera = new Camera(window, shaderProgram);

    glfwSwapBuffers(window);

    float prevTime = glfwGetTime() - 4.0f;

    /* Loop until the user closes the window */

    float xPos = 0.0f, zPos = -2.0f;
    float speed = 0.5f;

    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(0.0f, 0.8f, 0.8f, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram->BindProgram();

        float currTime = glfwGetTime();
        float deltaTime = currTime - prevTime;

        if (deltaTime > (float)1/60) {
            camera->Update(deltaTime);
            camera->DispatchMatrices();
            prevTime = currTime;
        }

        //GLfloat scale = 0.5f;
        //glUniform1fv(shaderProgram->programId, 1, &scale);

        VertArray->Bind();
        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(GLuint), GL_UNSIGNED_INT, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    delete VertArray;
    delete shaderProgram;

    glfwTerminate();
    return 0;
}