#include "TestScene.hpp"
#include "Node.hpp"
#include "Particles.hpp"
#include "SpriteNode.hpp"
#include <string>

TestScene::TestScene(std::string tag) : Scene(tag) {
  srand((unsigned)time(NULL));
}

TestScene::~TestScene() = default;

std::string TestScene::get_particle_system_name() {
  return "particle_system_" + std::to_string(this->particle_system_count++);
}

void TestScene::handle_init() {
  skeleton::Renderer::get_instance().set_clear_color({0, 0, 0, 100});

  int width = skeleton::Renderer::get_instance().get_window_width();
  int height = skeleton::Renderer::get_instance().get_window_height();

  this->add_child(new skeleton::ParticleSystem(get_particle_system_name(),
                                               width / 2, height / 2));
  this->add_child(new skeleton::SpriteNode("./assets/spritesheets/player.png",
                                           width / 2, height / 2));
}

void TestScene::handle_input(SDL_Event &event) {
  //  this->script_handle_input(event);
  if (event.type == SDL_MOUSEBUTTONDOWN) {
    if (event.button.button == SDL_BUTTON_LEFT) {
      int mouseX = event.button.x;
      int mouseY = event.button.y;
      this->add_child(new skeleton::ParticleSystem(get_particle_system_name(),
                                                   mouseX, mouseY));
    }
  }
}

void TestScene::handle_update(double dt) {
  // for (auto it = this->children.begin(); it != this->children.end();) {
  //   if (auto particle_system = dynamic_cast<skeleton::ParticleSystem *>(*it))
  //   {
  //     if (particle_system->is_ready_to_die) {
  //       it = this->children.erase(it);
  //       delete particle_system;
  //     }
  //   } else {
  //     it++;
  //   }
  // }
}

void TestScene::handle_fixed_update(double dt) {}

void TestScene::handle_draw() {}

void TestScene::handle_destroy() {}

void DrawNodeTree(skeleton::Node *node) {
  // Ensure the node is valid
  if (!node) {
    return;
  }

  // Determine the flags based on whether the node has children
  ImGuiTreeNodeFlags nodeFlags =
      (node->children.empty()) ? ImGuiTreeNodeFlags_Leaf : 0;

  // Display node in the tree
  if (ImGui::TreeNodeEx(node->get_tag().c_str(), nodeFlags)) {
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
