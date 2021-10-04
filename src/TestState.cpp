#include <Components.hpp>
#include <Systems.hpp>
#include <TestState.hpp>

TestState::TestState(Skeleton::GameDataRef Data)
	: GraphicsSystem(Actors), OthersSystem(Actors), Data(Data) {}

void TestState::init() {
	this->actor = this->Actors.create<Actor>(this->Data, "scripts/bones.lua");
	this->GraphicsSystem.add<GraphicSystem>();
	this->OthersSystem.add<LogicSystem>();
}

void TestState::handleInput() {
	sf::Event event;
	while (this->Data->Window.pollEvent(event)) {
		if (sf::Event::Closed == event.type) {
			this->Data->Window.close();
		}
	}
}

void TestState::update(float dt) {
	this->GraphicsSystem.update(dt);
	this->OthersSystem.update(dt);
}

void TestState::draw() {
	ImGui::SFML::Update(this->Data->Window, this->Clock.restart());
	this->Data->Window.clear(sf::Color(125, 125, 125));
	for (auto entity : Actors.with<GraphicComponent>()) {
		this->Data->Window.draw(entity.get<GraphicComponent>().Sprite);
	}
	if (this->Data->DebugMode) {
		ImGui::Begin("Debug Test.");
		this->Data->logEngine();
		ImGui::Text("Current State: Test State");
		ImGui::End();
	}
	ImGui::EndFrame();
	ImGui::SFML::Render(this->Data->Window);
	this->Data->Window.display();
}