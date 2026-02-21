#include <imgui.h>
#include <skeleton/debug/Editor.hpp>
#include <skeleton/debug/widget_registry.hpp>

namespace skeleton::debug {

static constexpr float PANEL_LEFT_W = 280.0f;
static constexpr float PANEL_RIGHT_W = 280.0f;
static constexpr ImGuiWindowFlags PANEL_FLAGS =
    ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove |
    ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus;

void Editor::draw(SDL_Texture *scene_tex, skeleton::core::Scene *scene) {
  ImVec2 display = ImGui::GetIO().DisplaySize;
  float mid_w = display.x - PANEL_LEFT_W - PANEL_RIGHT_W;

  ImGui::SetNextWindowPos({0, 0}, ImGuiCond_Always);
  ImGui::SetNextWindowSize({PANEL_LEFT_W, display.y}, ImGuiCond_Always);
  ImGui::Begin("Settings", nullptr, PANEL_FLAGS);
  draw_settings(scene);
  ImGui::End();

  ImGui::SetNextWindowPos({PANEL_LEFT_W, 0}, ImGuiCond_Always);
  ImGui::SetNextWindowSize({mid_w, display.y}, ImGuiCond_Always);
  ImGui::Begin("Scene", nullptr, PANEL_FLAGS);
  draw_scene(scene_tex);
  ImGui::End();

  ImGui::SetNextWindowPos({PANEL_LEFT_W + mid_w, 0}, ImGuiCond_Always);
  ImGui::SetNextWindowSize({PANEL_RIGHT_W, display.y}, ImGuiCond_Always);
  ImGui::Begin("Inspector", nullptr, PANEL_FLAGS);
  draw_inspector(scene);
  ImGui::End();
}

void Editor::draw_settings(skeleton::core::Scene *scene) {
  ImGui::SeparatorText("Scene");
  ImGui::Text("%s", scene->get_name().c_str());

  auto &registry = scene->get_registry();
  int count = (int)registry.storage<entt::entity>().size();
  ImGui::Text("%d entities", count);
}

void Editor::draw_scene(SDL_Texture *scene_tex) {
  if (!scene_tex) return;
  ImVec2 avail = ImGui::GetContentRegionAvail();
  ImGui::Image((ImTextureID)scene_tex, avail);
}

void Editor::draw_inspector(skeleton::core::Scene *scene) {
  auto  &registry = scene->get_registry();
  float  avail_h  = ImGui::GetContentRegionAvail().y;

  ImGui::SeparatorText("Entities");
  ImGui::BeginChild("entity_list", {0, avail_h * 0.35f}, ImGuiChildFlags_Borders);
  for (auto e : registry.storage<entt::entity>()) {
    char label[32];
    snprintf(label, sizeof(label), "Entity %u", (unsigned)entt::to_integral(e));
    bool is_selected = (e == selected_);
    if (ImGui::Selectable(label, is_selected))
      selected_ = e;
  }
  ImGui::EndChild();

  ImGui::SeparatorText("Components");
  ImGui::BeginChild("components", {0, 0}, ImGuiChildFlags_Borders);
  if (selected_ != entt::null && registry.valid(selected_))
    draw_entity(registry, selected_);
  else
    ImGui::TextDisabled("No entity selected");
  ImGui::EndChild();
}

} // namespace skeleton::debug
