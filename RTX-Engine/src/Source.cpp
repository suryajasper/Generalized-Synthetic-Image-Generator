#include "Model.h"
#include "Camera.h"
#include "SceneObject.h"
#include "Scene.h"
#include "CubeMap.h"
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

    GLuint width = 1920, height = 1080;
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
    GLfloat lightIntensities[4] = { 1.1f, 0.8f, 1.3f, 1.4f };

    Scene* scene = new Scene(window);
    scene->SetCamera(camera);

    ShaderProgram* skyboxShader = new ShaderProgram();
    skyboxShader->Initialize("resources/shaders/skybox.vert", "resources/shaders/skybox.frag");

    std::string skyboxFaces[6] = {
        "resources/images/nature_skybox/nature_right.png",
        "resources/images/nature_skybox/nature_left.png",
        "resources/images/nature_skybox/nature_up.png",
        "resources/images/nature_skybox/nature_down.png",
        "resources/images/nature_skybox/nature_front.png",
        "resources/images/nature_skybox/nature_back.png",
    };

    CubeMap* skybox = new CubeMap(skyboxShader);
    skybox->LoadFaces(skyboxFaces);

    scene->SetSkybox(skybox);

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
    backpackModel->LinkTexture(TEX_MAP_DIFFUSE  , "resources/models/backpack/diffuse.jpg");
    backpackModel->LinkTexture(TEX_MAP_NORMAL   , "resources/models/backpack/normal.png");
    backpackModel->LinkTexture(TEX_MAP_SPECULAR , "resources/models/backpack/specular.jpg");
    backpackModel->LinkTexture(TEX_MAP_ROUGHNESS, "resources/models/backpack/roughness.jpg");
    backpackModel->LinkTexture(TEX_MAP_OCCLUSION, "resources/models/backpack/ao.jpg");
    // backpack->transform->position.x = -1.5f;
    backpack->transform->SetScale(1.0f);

    
    SceneObject* vase = new SceneObject("vase");
    Model* vaseModel = vase->AddComponent<Model>();
    vaseModel->LoadMesh("resources/models/VaseModel/Vase.obj");
    vaseModel->LinkTexture(TEX_MAP_DIFFUSE, "resources/models/VaseModel/VaseColor.png");
    vaseModel->LinkTexture(TEX_MAP_NORMAL, "resources/models/VaseModel/Normal.png");
    vaseModel->LinkTexture(TEX_MAP_ROUGHNESS, "resources/models/VaseModel/Roughness.png");
    vaseModel->LinkTexture(TEX_MAP_OCCLUSION, "resources/models/VaseModel/AmbOcc.png");
    // vase->transform->position.x = 2.2f;
    vase->transform->SetScale(15.0f);

    SceneObject* chest = new SceneObject("treasure chest");
    Model* chestModel = chest->AddComponent<Model>();
    chestModel->LoadMesh("resources/models/treasure-chest/treasure_chest.obj");
    chestModel->LinkTexture(TEX_MAP_DIFFUSE, "resources/models/treasure-chest/textures/diffuse.jpg");
    chestModel->LinkTexture(TEX_MAP_NORMAL, "resources/models/treasure-chest/textures/normal.png");
    chestModel->LinkTexture(TEX_MAP_METALLIC, "resources/models/treasure-chest/textures/metal.png");
    chestModel->LinkTexture(TEX_MAP_ROUGHNESS, "resources/models/treasure-chest/textures/rough.png");
    chest->transform->SetScale(4.0f);

    std::vector<SceneObject*> renderables = {backpack, vase, chest};

    for (SceneObject* renderable : renderables) {
        scene->AddSceneObject(renderable);
        renderable->active = false;
    }

    unsigned int active = 0;
    bool rotating = true;

    float prevTime = glfwGetTime();
    float total = 0;
    GLfloat moveSpeed = 0.5f;

    while (!glfwWindowShouldClose(window))
    {
        float currTime = glfwGetTime();
        float deltaTime = currTime - prevTime;

        if (deltaTime > (float)1/100) {
            Transformable* transform = camera->transform;

            glm::vec3 upVec = { 0, 1, 0 };

            float rotSpeed = 1.0f;
            float speed = 10.0f;

            if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) active = 0;
            if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) active = 1;
            if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) active = 2;

            if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) rotating = !rotating;

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

            for (unsigned int i = 0; i < renderables.size(); i++)
                renderables[i]->active = (i == active);

            if (rotating)
                renderables[active]->transform->Rotate(glm::vec3(0, 1, 0) * deltaTime * moveSpeed);
            // backpack->transform->position.y = 1.5f * glm::sin(moveSpeed * currTime);
            
            /*
            vase->transform->Rotate(glm::vec3(0, 1, 0) * deltaTime * moveSpeed);
            vase->transform->position.y = 1.5f * glm::sin(moveSpeed * currTime) - 2.0f;
            */

            scene->Render();

            prevTime = currTime;
        }

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}