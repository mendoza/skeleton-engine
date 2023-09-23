#include "TestScene.hpp"

TestScene::TestScene() { srand((unsigned)time(NULL)); }

TestScene::~TestScene() = default;

void TestScene::on_init() {
	setupLuaState();
	skeleton::ServiceLocator::get<skeleton::SkeletonRenderer>()
		->set_clear_color({0, 0, 0, 100});

	ecs.component<Position>();
	ecs.component<Square>();
	ecs.component<Velocity>();
	int width = skeleton::ServiceLocator::get<skeleton::SkeletonRenderer>()
					->get_window_width();
	int height = skeleton::ServiceLocator::get<skeleton::SkeletonRenderer>()
					 ->get_window_height();
	ecs.system<Position>("Cleaner").each(
		[width, height](flecs::entity e, Position &p) {
			if (p.x < 0 || p.x > width || p.y < 0 || p.y > height) {
				e.destruct();
			}
		});

	ecs.system<Position, Velocity>("Move").each([](Position &p, Velocity &v) {
		p.x += v.x;
		p.y += v.y;
	});

	for (float i = 0; i < 360; i++)
		ecs.entity().set([i](Position &p, Square &s, Velocity &v) {
			// calculate x and y for a circle in the middle of the screen
			float angle = i * 3.14159f / 180.0f;
			float x = 400 + cos(angle) * 200;
			float y = 300 + sin(angle) * 200;
			p = {x, y};

			uint8_t r = rand() % 256;
			uint8_t g = rand() % 256;
			uint8_t b = rand() % 256;
			s = {10, 10, {r, g, b, 255}};

			float speed = (rand() % 100) / 100.0f;
			v = {cos(angle) * speed, sin(angle) * speed};
		});
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
	skeleton::ServiceLocator::get<skeleton::SkeletonRenderer>()->add_texture(
		file_path, texture_name);

	this->script_on_update = L["on_update"];
	this->script_handle_input = L["handle_input"];
}

void TestScene::on_input(SDL_Event &event) { this->script_handle_input(event); }

void TestScene::on_update(float dt) {
	this->script_on_update(dt);
	ecs.progress(dt);
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
	flecs::query<Position, Square> q = ecs.query<Position, Square>();
	q.each([](flecs::entity e, Position &p, Square &s) {
		skeleton::ServiceLocator::get<skeleton::SkeletonRenderer>()->draw_rect(
			s.color, p.x, p.y, s.width, s.height);
	});
}
void TestScene::on_destroy() {}
