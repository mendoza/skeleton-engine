#include <Components.hpp>
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
	L.script_file("assets/scripts/actorTest.lua");

	sol::usertype<Actor> actor_type =
		L.new_usertype<Actor>("Actor", sol::constructors<Actor()>());

	actor_type["rotate"] = &Actor::rotate;
	actor_type["forward"] = &Actor::forward;
	actor_type["backward"] = &Actor::backward;
	actor_type["stop"] = &Actor::stop;
	actor_type["flipH"] = &Actor::flipH;
	actor_type["flipV"] = &Actor::flipV;
	actor_type["playAnimation"] = &Actor::playAnimation;
	actor_type["position"] = &Actor::getPosition;

	sol::usertype<sf::Vector2f> sfVector2f = L.new_usertype<sf::Vector2f>(
		"vector2f",
		sol::constructors<sf::Vector2f(), sf::Vector2f(float, float)>(), "x",
		&sf::Vector2f::x, "y", &sf::Vector2f::y);

	Actor actor = this->Actors.create<Actor>(
		this->Data, L["actorParams"]["graphicComponent"]);
	L.set("actor", actor);
	skeleton::setLogger(L);
	this->state_update = L["update"];
}

void TestState::handleInput() {
	sf::Event event;
	while (this->Data->Window.pollEvent(event)) {
		ImGui::SFML::ProcessEvent(event);
		if (sf::Event::Closed == event.type) {
			this->Data->Window.close();
		}

		if (event.type == sf::Event::Resized) {
			// update the view to the new size of the window
			sf::FloatRect visibleArea(0, 0, event.size.width,
									  event.size.height);
			this->Data->Window.setView(sf::View(visibleArea));
		}

		if (event.type == sf::Event::KeyPressed) {
			this->state_handle_input(event.key.code);
		}
	}
}

void TestState::update(float dt) {
	this->Systems.update(dt);
	this->state_update(dt);
}

void TestState::draw(float dt) {
	this->Data->Window.clear(sf::Color(125, 125, 125));

	if (this->Data->DebugMode) {
		ImGui::SFML::Update(this->Data->Window, sf::seconds(dt));
		ImGui::Begin("Debug Test.");
		this->Data->logEngine();
		ImGui::Text("Current State: Test State");
		ImGui::TextColored(ImVec4(1, 1, 0, 1), "Actors");
		ImGui::BeginChild("Scrolling");
	}

	int count = 0;
	for (auto entity : Actors.with<GraphicComponent>()) {
		this->Data->Window.draw(entity.get<GraphicComponent>().Sprite);
		if (this->Data->DebugMode) {
			ImGui::Text(
				"Actor %d: %s", count++,
				entity.get<GraphicComponent>().CurrentAnimation.c_str());
		}
	}
	if (this->Data->DebugMode) {
		ImGui::EndChild();
		ImGui::End();
		ImGui::EndFrame();
		ImGui::SFML::Render(this->Data->Window);
	}
	this->Data->Window.display();
}
