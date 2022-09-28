#include "ShaderProgram.h"
#include "Camera.h"
#include "VAO.h"
#include "Texture2D.h"
#include "Mesh.h"
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

    GLfloat vertices[] =
    { //     COORDINATES     /   TexCoord  //
        -0.5f, 0.0f,  0.5f,     0.0f, 0.0f,
        -0.5f, 0.0f, -0.5f,     5.0f, 0.0f,
         0.5f, 0.0f, -0.5f,     0.0f, 0.0f,
         0.5f, 0.0f,  0.5f,     5.0f, 0.0f,
         0.0f, 0.8f,  0.0f,     2.5f, 5.0f,
    };

    // Indices for vertices order
    GLuint indices[] =
    {
        0, 1, 2,
        0, 2, 3,
        0, 1, 4,
        1, 2, 4,
        2, 3, 4,
        3, 0, 4
    };

    ShaderProgram* shaderProgram = new ShaderProgram();
    shaderProgram->Initialize("resources/shaders/default.vert", "resources/shaders/default.frag");

    VAO* VertArray = new VAO(sizeof(vertices)/sizeof(GLfloat), sizeof(indices)/sizeof(GLuint), 5);
    VertArray->CreateVBO(sizeof(vertices), vertices);
    VertArray->CreateEBO(indices);
    VertArray->LinkVertexAttribute(0, 3);
    VertArray->LinkVertexAttribute(1, 2);

    UniformManager* uniformManager = new UniformManager(shaderProgram);

    Texture2D* tex2d = new Texture2D(shaderProgram);
    tex2d->LoadImage(TEX_MAP_COLOR, "resources/images/Clay-Bricks-1.png");

    Camera* camera = new Camera(window, shaderProgram);
    camera->SetAspectRatio((float) width / height);

    glfwSwapBuffers(window);

    glEnable(GL_DEPTH_TEST);

    float prevTime = glfwGetTime() - 4.0f;

    Mesh* mesh = new Mesh((char*) "resources/cube.obj");

    /* Loop until the user closes the window */

    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(0.0f, 0.3f, 0.3f, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);

        shaderProgram->BindProgram();

        float currTime = glfwGetTime();
        float deltaTime = currTime - prevTime;

        if (deltaTime > (float)1/60) {
            camera->Update(deltaTime);
            camera->DispatchMatrices();
            prevTime = currTime;
        }

        GLfloat scale = 0.5f;
        uniformManager->SetUniform("scale", UNIFORM_FLOAT, &scale);
        //glUniform1fv(shaderProgram->programId, 1, &scale);

        tex2d->Bind();
        VertArray->Bind();
        // glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

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