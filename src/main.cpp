#include "setup.hpp"

using namespace Engine;

int main() {
  ConceptForge forge;
  forge.SetSelected(0);

  // Render Loop
  while (!forge.WindowShouldClose()) {
    forge.Render();
    forge.DeltaTimeCalc();
    forge.ProcessInput();
    forge.CalcProjection();
    forge.GUIManagement();
  }

  return 0;
}
