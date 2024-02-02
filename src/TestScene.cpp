#include "TestScene.hpp"
#include <memory>

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

  // create a circle of particle systems around the center of the screen
  for (int i = 0; i < 360; i += 1) {
    float angle = 2 * 3.14159 * float(i) / 360.0f;
    float x = cos(angle) * 200 + width / 2;
    float y = sin(angle) * 200 + height / 2;
    this->addChild(new skeleton::ParticleSystem("particle_system", x, y));
  }
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
      // ecs.entity().set(
      // 	[mouseX, mouseY](Position &p, Velocity &v, Square &s) {
      // 		// calculate position and velocity to form a circle from the
      // 		// middle of the screen

      // 		float angle = 2 * 3.14159 * float(rand() % 1000) / 1000.0f;
      // 		p.x = mouseX;
      // 		p.y = mouseY;

      // 		v.x = cos(angle) * 0.1f;
      // 		v.y = sin(angle) * 0.1f;
      // 		int r = rand() % 255;
      // 		int g = rand() % 255;
      // 		int b = rand() % 255;
      // 		s = {10, 10, r, g, b, 255};
      // 	});
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
  ImGui::Text("Scene tag: %s", this->tag.c_str());
  DrawNodeTree(this);
  ImGui::End();
}

void TestScene::destroy() {}
