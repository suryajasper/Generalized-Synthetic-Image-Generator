#include "UIManager.h"

UIManager::UIManager(GLFWwindow* window, std::vector<SceneObject*>* sceneObjects)
{
    this->sceneObjects = sceneObjects;
    this->window = window;
    this->active = nullptr;

	Initialize(window);
}

UIManager::~UIManager()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void UIManager::DrawTree(SceneObject* node)
{
    bool opened = ImGui::TreeNode(node->name.c_str());

    if (ImGui::IsItemClicked())
        active = node;

    if (opened) {
        for (SceneObject* child : node->children)
            DrawTree(child);
        ImGui::TreePop();
    }
}

void UIManager::DisplaySceneHierarchy()
{
    bool my_tool_active = true;

    ImGui::Begin("Scene Objects", &my_tool_active, ImGuiWindowFlags_MenuBar);

    for (SceneObject* obj : *sceneObjects)
        DrawTree(obj);
    
    ImGui::End();
}

void UIManager::DisplaySceneObjectComponents()
{
    ImGuiViewport* main_viewport = ImGui::GetMainViewport();

    float right = main_viewport->WorkPos.x + main_viewport->Size.x;
    float top = main_viewport->WorkPos.y;

    ImGui::SetNextWindowPos(ImVec2(right - 600, top + 20), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);

    bool my_tool_active = true;

    ImGui::Begin(active->name.c_str(), &my_tool_active, ImGuiWindowFlags_MenuBar);

    for (Component* comp : active->components) {
        if (ImGui::CollapsingHeader(comp->name.c_str())) {

            GuiSerialized<GLfloat  >* float1s = comp->GetFloat1s();
            GuiSerialized<glm::vec2>* float2s = comp->GetFloat2s();
            GuiSerialized<glm::vec3>* float3s = comp->GetFloat3s();

            float speed = 0.05f;
            if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) speed *= 5.0f;
            else if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) speed /= 5.0f;

            for (auto field : *float1s) {
                ImGui::DragFloat(field.first.c_str(), field.second, speed);
            }
            for (auto field : *float2s) {
                GLfloat arr2[2];
                cpyVec2ToArr(field.second, arr2);

                ImGui::DragFloat2(field.first.c_str(), arr2, speed);

                field.second->x = arr2[0]; 
                field.second->y = arr2[1];
            }
            for (auto field : *float3s) {
                GLfloat arr3[3];
                cpyVec3ToArr(field.second, arr3);

                ImGui::DragFloat3(field.first.c_str(), arr3, speed);

                field.second->x = arr3[0]; 
                field.second->y = arr3[1]; 
                field.second->z = arr3[2];
            }

        }
    }

    ImGui::End();
}

void UIManager::DisplaySceneObjectControls()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (active == nullptr) active = (*sceneObjects)[0];

    DisplaySceneHierarchy();
    DisplaySceneObjectComponents();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UIManager::cpyVec2ToArr(glm::vec2* vec, GLfloat arr[2])
{
    arr[0] = vec->x;
    arr[1] = vec->y;
}

void UIManager::cpyVec3ToArr(glm::vec3* vec, GLfloat arr[3])
{
    arr[0] = vec->x;
    arr[1] = vec->y;
    arr[2] = vec->z;
}

void UIManager::Initialize(GLFWwindow* window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
}
