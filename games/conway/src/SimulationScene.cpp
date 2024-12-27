#include "SimulationScene.hpp"
#include "GameOfLifeNode.hpp"
#include <skeleton/Nodes/Node.hpp>
#include <skeleton/Nodes/Particles.hpp>
#include <skeleton/Nodes/SpriteNode.hpp>
#include <string>

SimulationScene::SimulationScene(std::string name) : Scene() {
  srand((unsigned)time(NULL));
  this->name = name;
}

SimulationScene::~SimulationScene() = default;

void SimulationScene::handle_init() {
  skeleton::Renderer::get_instance().set_draw_color({0, 0, 0, 100});

  int width = skeleton::Renderer::get_instance().get_window_width();
  int height = skeleton::Renderer::get_instance().get_window_height();

  skeleton::Renderer::get_instance().set_draw_color({125, 125, 125, 255});

  this->add_child(new GameOfLife(height, width));
}

void SimulationScene::handle_input(SDL_Event &event) {
  //  this->script_handle_input(event);
  if (ImGui::GetIO().WantCaptureMouse) {
    return;
  }
  /*if (event.type == SDL_MOUSEBUTTONDOWN &&*/
  /*    event.button.button == SDL_BUTTON_LEFT) {*/
  /*  int mouseX = event.button.x;*/
  /*  int mouseY = event.button.y;*/
  /*}*/
}

void SimulationScene::handle_update(double dt) {}

void SimulationScene::handle_fixed_update(double dt) {}

void SimulationScene::handle_draw() {}

void SimulationScene::handle_destroy() {}

void DrawNodeTree(skeleton::Node *node) {
  // Ensure the node is valid
  if (!node) {
    return;
  }

  // Determine the flags based on whether the node has children
  ImGuiTreeNodeFlags nodeFlags =
      (node->children.empty()) ? ImGuiTreeNodeFlags_Leaf : 0;

  // Display node in the tree
  if (ImGui::TreeNodeEx(node->get_name().c_str(), nodeFlags)) {
    // Recursively draw children
    for (auto &child : node->children) {
      DrawNodeTree(child);
    }

    // Close the tree node
    ImGui::TreePop();
  }
}

void SimulationScene::draw_debug_window() {
  // Create a window called "My First Tool", with a menu bar.
  bool my_tool_active = true;
  ImGui::Begin("Debug Window", &my_tool_active, ImGuiWindowFlags_MenuBar);
  if (ImGui::BeginMenuBar()) {
    if (ImGui::BeginMenu("File")) {
      if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */
      }
      if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */
      }
      if (ImGui::MenuItem("Close", "Ctrl+W")) {
        my_tool_active = false;
      }
      ImGui::EndMenu();
    }
    ImGui::EndMenuBar();
  }
  DrawNodeTree(this);
  ImGui::End();
}
