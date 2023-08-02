#include <TestScene.hpp>

TestScene::TestScene() {}

void TestScene::on_init() {
	setupLuaState();
	this->Systems.add<GraphicSystem>();
}

void TestScene::setupLuaState() {
	L.open_libraries(sol::lib::base, sol::lib::math, sol::lib::string,
					 sol::lib::io, sol::lib::os);
	this->set_engine_user_types();
	L.script_file("assets/scripts/test_state.lua");
	sol::table gc = L["actor_parameters"]["graphic_parameters"];
	Actor actor_instance = this->Actors.create<Actor>(gc);

	sol::usertype<Actor> actor_type =
		L.new_usertype<Actor>("Actor", sol::constructors<Actor()>());

	actor_type["flip_horizontal"] = &Actor::flip_horizontal;
	actor_type["flip_vertical"] = &Actor::flip_vertical;
	actor_type["play_animation"] = &Actor::play_animation;

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

void TestScene::on_draw() {
	for (auto entity : Actors.with<GraphicComponent, PositionComponent>()) {
		// entity.get<GraphicComponent>().sprite.setPosition(
		// 	entity.get<PositionComponent>().x,
		// 	entity.get<PositionComponent>().y);
		// this->data->render_window.draw(entity.get<GraphicComponent>().sprite);
	}
}

void TestScene::on_destroy() {}
