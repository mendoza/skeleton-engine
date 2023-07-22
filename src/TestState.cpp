#include <TestState.hpp>

TestState::TestState(skeleton::GameDataRef Data) : State(Data) {}

void TestState::on_init() {
	setupLuaState();
	this->Systems.add<GraphicSystem>();
}

void TestState::setupLuaState() {
	L.open_libraries(sol::lib::base, sol::lib::math, sol::lib::string,
					 sol::lib::io, sol::lib::os);
	this->set_engine_user_types();
	L.script_file("assets/scripts/test_state.lua");
	sol::table gc = L["actor_parameters"]["graphic_parameters"];
	Actor actor_instance = this->Actors.create<Actor>(this->data, gc);

	sol::usertype<Actor> actor_type =
		L.new_usertype<Actor>("Actor", sol::constructors<Actor()>());

	actor_type["move"] = &Actor::move;
	actor_type["rotate"] = &Actor::rotate;
	actor_type["stop"] = &Actor::stop;
	actor_type["flip_horizontal"] = &Actor::flip_horizontal;
	actor_type["flip_vertical"] = &Actor::flip_vertical;
	actor_type["play_animation"] = &Actor::play_animation;
	actor_type["get_position"] = &Actor::get_position;
	actor_type["get_direction"] = &Actor::get_direction;

	L["actor"] = actor_instance;
	this->script_on_update = L["on_update"];
	this->script_handle_input = L["handle_input"];
}

void TestState::on_input(sf::Event event) { this->script_handle_input(event); }

void TestState::on_update(float dt) {
	this->Systems.update(dt);
	this->script_on_update(dt);
}

void TestState::create_debug_window() {
	ImGui::Begin("Test State");
	console.Draw("Console: Test State", &is_open, L);
	this->data->log_engine();
	ImGui::TextColored(ImVec4(1, 1, 0, 1), "Actors");
	ImGui::BeginChild("Scrolling");
	int count = 0;
	for (auto entity : Actors.with<GraphicComponent>()) {
		ImGui::Text(
			"Actor %d: %s", count++,
			entity.get<GraphicComponent>().get_current_animation().c_str());
	}
	ImGui::EndChild();
	ImGui::End();
}

void TestState::on_draw() {
	for (auto entity : Actors.with<GraphicComponent, PositionComponent>()) {
		entity.get<GraphicComponent>().sprite.setPosition(
			entity.get<PositionComponent>().x,
			entity.get<PositionComponent>().y);

		this->data->render_window.draw(entity.get<GraphicComponent>().sprite);
	}
}
