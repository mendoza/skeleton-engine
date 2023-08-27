#include "TestScene.hpp"

TestScene::TestScene() {}

TestScene::~TestScene() {}

void TestScene::on_init() {
	setupLuaState();
	this->Systems.add<GraphicSystem>();
}

void TestScene::setupLuaState() {
	L.open_libraries(sol::lib::base, sol::lib::math, sol::lib::string,
					 sol::lib::io, sol::lib::os);
	skeleton::setEngineMetadata(this->L);
	L.script_file("assets/scripts/test_state.lua");
	sol::table ac = L["actor_parameters"];
	sol::table gc = ac["graphic_parameters"];
	std::string file_path = gc["sprite_filepath"];
	std::string texture_name = gc["sprite_name"];
	this->locator.get<skeleton::SkeletonRenderer>()->add_texture(file_path,
																 texture_name);
	Actor actor_instance = this->entities.create<Actor>(texture_name);

	sol::usertype<Actor> actor_type =
		L.new_usertype<Actor>("Actor", sol::constructors<Actor()>());

	L["actor"] = actor_instance;
	this->script_on_update = L["on_update"];
	this->script_handle_input = L["handle_input"];
}

void TestScene::on_input(SDL_Event &event) { this->script_handle_input(event); }

void TestScene::on_update(float dt) {
	this->Systems.update(dt);
	this->script_on_update(dt);
}

void TestScene::draw_debug_window() {
	// ImGui::Begin("Test State");
	// console.Draw("Console: Test State", &is_open, L);
	// this->data->log_engine();
	// ImGui::TextColored(ImVec4(1, 1, 0, 1), "Actors");
	// ImGui::BeginChild("Scrolling");
	// int count = 0;
	// for (auto entity : Actors.with<GraphicComponent>()) {
	// 	ImGui::Text(
	// 		"Actor %d: %s", count++,
	// 		entity.get<GraphicComponent>().get_current_animation().c_str());
	// }
	// ImGui::EndChild();
	// ImGui::End();
}

void TestScene::on_draw() {
	for (auto entity : entities.with<GraphicComponent>()) {
		std::string texture_name = entity.get<GraphicComponent>().texture_name;
		SDL_Rect *clip = entity.get<GraphicComponent>().clip;
		this->locator.get<skeleton::SkeletonRenderer>()->draw_texture(
			texture_name, clip, 200, 200);
	}
}

void TestScene::on_destroy() {}
