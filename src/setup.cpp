#include "setup.hpp"

#include "primitives/uv_sphere.hpp"
#include "primitives/cube.hpp"

using namespace Engine;

ConceptForge::ConceptForge():
  camera(glm::vec3(7.3589f, 5.3444f, 6.9258f), glm::vec3(0.0f, 1.0f, 0.0f), -132.4f, -28.2f),
  window(Const::WIDTH, Const::HEIGHT, Const::WINDOWNAME, false),
  mainGui(window.window)
{
    // Projection Logic - Initialize
    Projection projection;

    shaderProgram.Init(DrawMode::FILLED, Const::vertexShaderPath, Const::fragmentShaderPath),
    // Bind all textures
    shaderProgram.BindTextures();

    // Setup Main GUI
    Editor::Gizmo gizmo;
    Editor::Inspector inspector;
    Editor::AssetBrowser asset_browser;
    Editor::ObjectCreationMenu objCreatorMenu;

    // Add an empty
    std::unique_ptr<SimObject::Entity> empty = std::make_unique<SimObject::Entity>();
    entities.push_back(std::move(empty));
}

ConceptForge::~ConceptForge(){

}

void ConceptForge::DeltaTimeCalc(){
    // Delta Time calculation
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

bool ConceptForge::WindowShouldClose() {
    return glfwWindowShouldClose(window.window);
}


void ConceptForge::ProcessInput(){
    // input processing
    input.processInput(window.window, camera, deltaTime);
}
void ConceptForge::Render(){
    // rendering commands
    // Clear Screen with this color
    auto clearColor = Const::clearColor;
    glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    window.RenderToFBO();
}

void ConceptForge::CalcProjection(){
    projection.Calculate(camera, shaderProgram);
}

void ConceptForge::SetSelected(int selected){
    if(selected < 0 || selected >= entities.size()){
        std::cout << "Selection is wrong" << std::endl;
        return;
    }
    selectedEntity = selected;
}

void ConceptForge::GUIManagement(){
    glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
    // Remove from here
    // Send Shader Data
    for(const auto& entity : entities) entity->Draw();

    // check and call events
    glfwPollEvents();

    // Imgui
    if (glfwGetWindowAttrib(window.window, GLFW_ICONIFIED) != 0) {
      ImGui_ImplGlfw_Sleep(10);
      return;
    }

    // Create new Frame
    mainGui.NewFrame();
    window.ImGuiBegin();

    mainGui.ShowConsole();

    // Draw All UI
    SimObject::Entity current_entity;
    if(selectedEntity >= 0){
        gizmo.Show(*entities[selectedEntity], projection, camera);
        inspector.Show(*entities[selectedEntity], gizmo.gizmoOperation, gizmo.gizmoMode);
    }

    asset_browser.Show(Const::projectDir);
    window.RenderToImGui();
    objCreatorMenu.Show();

    window.ImGuiEnd();
    // Render
    mainGui.RenderFrame();

    glfwSwapBuffers(window.window);
}
