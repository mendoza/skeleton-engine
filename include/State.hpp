#ifndef SKELETON_STATE_HPP
#define SKELETON_STATE_HPP

#include <ConsoleWidget.hpp>
#include <GameData.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <Utils.hpp>
#include <imgui-SFML.h>
#include <memory>
#include <sol.hpp>

namespace skeleton {
class State {
  public:
	skeleton::GameDataRef data;
	sf::Clock clock;
	sol::state L;
	ConsoleWidget console;
	bool is_open = false;

	State(skeleton::GameDataRef data) { this->data = data; }
	// User's Functions
	virtual void on_init() = 0;
	virtual void on_input(sf::Event event) = 0;
	virtual void on_update(float dt) = 0;
	virtual void on_draw(float dt) = 0;
	virtual void create_debug_window() = 0;

	// Engine's Functions
	virtual void pause() {}
	virtual void resume() {}
	virtual void init() { on_init(); }
	virtual void draw(float dt) { on_draw(dt); }
	virtual void handle_input() {
		sf::Event event;
		while (this->data->render_window.pollEvent(event)) {
			if (this->data->debug_mode)
				ImGui::SFML::ProcessEvent(event);
			on_input(event);

			switch (event.type) {
				case sf::Event::Closed: {
					this->data->render_window.close();
					break;
				}

				case sf::Event::Resized: {
					sf::FloatRect visibleArea(0, 0, event.size.width,
											  event.size.height);
					this->data->render_window.setView(sf::View(visibleArea));
					break;
				}

				default: {
					break;
				}
			}
		}
	}
	virtual void update(float dt) { this->on_update(dt); }

	virtual void set_engine_user_types() {
		skeleton::setLogger(L);
		skeleton::setEngineMetadata(L);
	}
};

typedef std::unique_ptr<State> StateRef;

}; // namespace skeleton

#endif