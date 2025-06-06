#pragma once

// Includes GLFW and glad
#include "window.hpp"

#include "input.hpp"

#include "shaderman.hpp"

#include <string>
#include <memory>

// GLM
#ifndef GLM_ENABLE_EXPERIMENTAL
#define GLM_ENABLE_EXPERIMENTAL
#endif
#include "glm/gtx/matrix_decompose.hpp"

#include "constants.hpp"
#include "projection.hpp"

// Imgui Based UI
#include "editor/gui.hpp"

#include "primitives/entity.hpp"

#include "editor/asset_browser.hpp"
#include "editor/gizmo.hpp"
#include "editor/inspector.hpp"
#include "editor/object_creation_menu.hpp"

namespace Engine {
    class ConceptForge{
    public:
        // Time management
        float lastFrame = 0.0f; // Time of last frame
        // Projection Logic
        Camera camera;
        WindowManagement::Window window;
        ShaderManagement::ShaderProgram shaderProgram;
        InputManagement::Input input;
        Projection projection;
        Editor::Gizmo gizmo;

        // GUI
        Editor::MainGUI mainGui;
        Editor::Inspector inspector;
        Editor::AssetBrowser asset_browser;
        Editor::ObjectCreationMenu objCreatorMenu;

        ConceptForge();
        ~ConceptForge();

        float deltaTime = 0.0f; // Time between current frame and last frame

        // Seperate functions
        bool WindowShouldClose();
        void DeltaTimeCalc();
        void ProcessInput();
        void Render();
        void CalcProjection();
        void GUIManagement();

        std::vector<std::shared_ptr<SimObject::Entity>> entities;
        int selectedEntity = 0;
        void SetSelected(int selected);
    };
}
