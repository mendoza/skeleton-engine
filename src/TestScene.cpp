#include <TestScene.hpp>

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
	Actor actor_instance = this->Actors.create<Actor>(gc);

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

void TestScene::create_debug_window() {
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

void TestScene::on_draw() {}

void TestScene::on_destroy() {}
