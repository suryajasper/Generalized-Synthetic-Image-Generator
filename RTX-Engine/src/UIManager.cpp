#include "UIManager.h"

UIManager::UIManager(GLFWwindow* window)
{
	Initialize(window);
}

UIManager::~UIManager()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void UIManager::DisplaySceneObjectControls(std::vector<SceneObjectLegacy>* transforms)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    bool my_tool_active = true;

    ImGui::Begin("My First Tool", &my_tool_active, ImGuiWindowFlags_MenuBar);

    for (SceneObjectLegacy obj : *transforms) {
        std::string name = obj.first;
        GuiSerializable* info = obj.second;

        if (ImGui::CollapsingHeader(name.c_str())) {
            GuiSerialized<GLfloat  >* float1s = info->GetFloat1s();
            GuiSerialized<glm::vec2>* float2s = info->GetFloat2s();
            GuiSerialized<glm::vec3>* float3s = info->GetFloat3s();

            for (auto field : *float1s) {
                ImGui::DragFloat(field.first.c_str(), field.second);
            }
            for (auto field : *float2s) {
                GLfloat arr2[2];
                cpyVec2ToArr(field.second, arr2);
                ImGui::DragFloat2(field.first.c_str(), arr2);
                field.second->x = arr2[0]; field.second->y = arr2[1];
            }
            for (auto field : *float3s) {
                GLfloat arr3[3];
                cpyVec3ToArr(field.second, arr3);
                ImGui::DragFloat3(field.first.c_str(), arr3);
                field.second->x = arr3[0]; field.second->y = arr3[1]; field.second->z = arr3[2];
            }
        }
    }


    ImGui::End();

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
