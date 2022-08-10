#include <Components.hpp>
#include <ConsoleWidget.hpp>
#include <Systems.hpp>
#include <TestState.hpp>

TestState::TestState(skeleton::GameDataRef Data)
	: Data(Data), Systems(Actors) {}

void TestState::init() {
	setupLuaState();
	this->Systems.add<GraphicSystem>();
}

void TestState::setupLuaState() {
	L.open_libraries(sol::lib::base, sol::lib::math, sol::lib::string,
					 sol::lib::io, sol::lib::os);

	L.script_file("assets/scripts/test_state.lua");
	sol::table gc = L["actor_params"]["graphic_component"];
	Actor actor = this->Actors.create<Actor>(this->Data, gc);

	sol::usertype<Actor> actor_type =
		L.new_usertype<Actor>("Actor", sol::constructors<Actor()>());

	actor_type["rotate"] = &Actor::rotate;
	actor_type["forward"] = &Actor::forward;
	actor_type["backward"] = &Actor::backward;
	actor_type["stop"] = &Actor::stop;
	actor_type["flipH"] = &Actor::flipH;
	actor_type["flipV"] = &Actor::flipV;
	actor_type["play_animation"] = &Actor::playAnimation;
	actor_type["position"] = &Actor::getPosition;
	sol::usertype<sf::Vector2f> sfVector2f = L.new_usertype<sf::Vector2f>(
		"vector2f",
		sol::constructors<sf::Vector2f(), sf::Vector2f(float, float)>(), "x",
		&sf::Vector2f::x, "y", &sf::Vector2f::y);

	L["actor"] = actor;
	skeleton::setLogger(L);
	this->on_update = L["on_update"];
	this->handle_input = L["handle_input"];
}

void TestState::handleInput(sf::Event event) {
	if (event.type == sf::Event::KeyPressed)
		this->handle_input(event.key.code);
}

void TestState::update(float dt) {
	this->Systems.update(dt);
	this->on_update(dt);
}

void TestState::drawDebugWindow() {
	console.Draw("Console: Test State", p_open, L);

	ImGui::Begin("Test State");
	this->Data->logEngine();
	ImGui::TextColored(ImVec4(1, 1, 0, 1), "Actors");
	ImGui::BeginChild("Scrolling");
	int count = 0;
	for (auto entity : Actors.with<GraphicComponent>()) {
		ImGui::Text("Actor %d: %s", count++,
					entity.get<GraphicComponent>().CurrentAnimation.c_str());
	}
	ImGui::EndChild();
	ImGui::End();
}

void TestState::draw(float dt) {
	for (auto entity : Actors.with<GraphicComponent>())
		this->Data->Window.draw(entity.get<GraphicComponent>().Sprite);
}
