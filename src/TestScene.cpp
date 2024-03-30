#include <string>
#include "TestScene.hpp"
#include "Particles.hpp"
#include "Node.hpp"

TestScene::TestScene(std::string tag) : Scene(tag) {
  srand((unsigned)time(NULL));
}

TestScene::~TestScene() = default;

std::string TestScene::get_particle_system_name() {
  return "particle_system_" + std::to_string(this->particle_system_count++);
}

void TestScene::handle_init() {
  skeleton::ServiceLocator::get<skeleton::SkeletonRenderer>()->set_clear_color(
      {0, 0, 0, 100});

  int width = skeleton::ServiceLocator::get<skeleton::SkeletonRenderer>()
                  ->get_window_width();
  int height = skeleton::ServiceLocator::get<skeleton::SkeletonRenderer>()
                   ->get_window_height();

  this->addChild(
      new skeleton::ParticleSystem(get_particle_system_name(), width / 2, height / 2));
}


void TestScene::handle_input(SDL_Event &event) {
  //  this->script_handle_input(event);
  if (event.type == SDL_MOUSEBUTTONDOWN) {
    if (event.button.button == SDL_BUTTON_LEFT) {
      int mouseX = event.button.x;
      int mouseY = event.button.y;
      this->addChild(new skeleton::ParticleSystem(get_particle_system_name(), mouseX,
                                                 mouseY));
    }
  }
}

void TestScene::handle_update(double dt) {
}

void TestScene::handle_fixed_update(double dt) {
}

void TestScene::handle_draw() {
}

void TestScene::handle_destroy() {
}


void DrawNodeTree(skeleton::Node *node) {
  // Ensure the node is valid
  if (!node) {
    return;
  }

  // Determine the flags based on whether the node has children
  ImGuiTreeNodeFlags nodeFlags =
      (node->children.empty()) ? ImGuiTreeNodeFlags_Leaf : 0;

  // Display node in the tree
  if (ImGui::TreeNodeEx(node->tag.c_str(), nodeFlags)) {
    // Recursively draw children
    for (auto &child : node->children) {
      DrawNodeTree(child);
    }

    // Close the tree node
    ImGui::TreePop();
  }
}

void TestScene::draw_debug_window() {
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


