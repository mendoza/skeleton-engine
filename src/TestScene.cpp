#include "TestScene.hpp"

TestScene::TestScene(std::string tag) : Scene(tag) {
  srand((unsigned)time(NULL));
}

TestScene::~TestScene() = default;

void TestScene::initialize() {
  setupLuaState();
  skeleton::ServiceLocator::get<skeleton::SkeletonRenderer>()->set_clear_color(
      {0, 0, 0, 100});

  int width = skeleton::ServiceLocator::get<skeleton::SkeletonRenderer>()
                  ->get_window_width();
  int height = skeleton::ServiceLocator::get<skeleton::SkeletonRenderer>()
                   ->get_window_height();

  this->addChild(
      new skeleton::ParticleSystem("particle_system_1", width / 2, height / 2));

    skeleton::Vector2f a(1, 2);
    skeleton::Vector2f b(3, 4);
    skeleton::Vector2f c = a + b;
    skeleton::Vector2f d = a - b;
    skeleton::Vector2f e = a * 2;
    skeleton::Vector2f f = a / 2;
    bool g = a == b;
    bool h = a != b;
    std::cout << c << std::endl;
    std::cout << d << std::endl;
    std::cout << e << std::endl;
    std::cout << f << std::endl;
    std::cout << g << std::endl;
    std::cout << h << std::endl;

}

void TestScene::setupLuaState() {
  this->script_manager->load_script_file("assets/scripts/test_state.lua");

  // L.open_libraries(sol::lib::base, sol::lib::math, sol::lib::string,
  //  sol::lib::io, sol::lib::os);
  // sol::table ac = L["actor_parameters"];
  // sol::table gc = ac["graphic_parameters"];
  // std::string file_path = gc["sprite_filepath"];
  // std::string texture_name = gc["sprite_name"];

  // skeleton::ServiceLocator::get<skeleton::SkeletonRenderer>()->add_texture(
  // file_path, texture_name);

  // this->script_on_update = L["on_update"];
  // this->script_handle_input = L["handle_input"];
}

void TestScene::handle_input(SDL_Event &event) {
  //  this->script_handle_input(event);
  if (event.type == SDL_MOUSEBUTTONDOWN) {
    if (event.button.button == SDL_BUTTON_LEFT) {
      int mouseX = event.button.x;
      int mouseY = event.button.y;
      this->addChild(new skeleton::ParticleSystem("particle_system_1", mouseX,
                                                 mouseY));
    }
  }
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

void TestScene::destroy() {}
