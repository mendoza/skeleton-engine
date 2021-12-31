#include <Components.hpp>
#include <Systems.hpp>
#include <TestState.hpp>

TestState::TestState(skeleton::GameDataRef Data)
	: Data(Data), Systems(Actors) {}

void TestState::init() {
	// for (int i = 0; i < 3000; i++)
	this->Actors.create<Actor>(this->Data, "scripts/actorTest.lua");

	this->Systems.add<GraphicSystem>();
	this->Systems.add<LogicSystem>();
}

void TestState::handleInput() {
	sf::Event event;
	while (this->Data->Window.pollEvent(event)) {
		if (sf::Event::Closed == event.type) {
			this->Data->Window.close();
		}
	}
}

void TestState::update(float dt) { this->Systems.update(dt); }

void TestState::draw() {
	if (this->Data->DebugMode) {
		ImGui::SFML::Update(this->Data->Window, this->Clock.restart());
	}
	this->Data->Window.clear(sf::Color(125, 125, 125));

	if (this->Data->DebugMode) {
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