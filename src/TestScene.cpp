#include "TestScene.hpp"

TestScene::TestScene(std::string tag) : Scene(tag) {
	srand((unsigned)time(NULL));
}

TestScene::~TestScene() = default;

void TestScene::on_init() {
	setupLuaState();
	skeleton::ServiceLocator::get<skeleton::SkeletonRenderer>()
		->set_clear_color({0, 0, 0, 100});

	int width = skeleton::ServiceLocator::get<skeleton::SkeletonRenderer>()
					->get_window_width();
	int height = skeleton::ServiceLocator::get<skeleton::SkeletonRenderer>()
					 ->get_window_height();

	ecs.component<Position>();
	ecs.component<Square>();
	ecs.component<Velocity>();

	for (int i = 0; i < 1000; i++) {
		auto e = ecs.entity().set(
			[i, width, height](Position &p, Velocity &v, Square &s) {
				// calculate position and velocity to form a circle from the
				// middle of the screen
				float angle = 2 * 3.14159 * float(i) / 1000.0f;
				p.x = width / 2 + cos(angle) * 100;
				p.y = height / 2 + sin(angle) * 100;

				v.x = cos(angle) * 0.1f;
				v.y = sin(angle) * 0.1f;
				int r = rand() % 255;
				int g = rand() % 255;
				int b = rand() % 255;
				s = {10, 10, r, g, b, 255};
			});
	}

	ecs.system<Position, const Velocity>("Move").iter(
		[](flecs::iter &it, Position *p, const Velocity *v) {
			for (auto i : it) {
				p[i].x += v[i].x * it.delta_time();
				p[i].y += v[i].y * it.delta_time();
			}
		});

	ecs.system<Position>("Remove").each(
		[width, height](flecs::entity e, Position p) {
			// Remove entities with position outside viewport
			if (p.x < 0 || p.x > width || p.y < 0 || p.y > height) {
				e.destruct();
			}
		});
}

void TestScene::setupLuaState() {
	this->script_manager->load_script_file("assets/scripts/test_state.lua");

	// L.open_libraries(sol::lib::base, sol::lib::math, sol::lib::string,
	//  sol::lib::io, sol::lib::os);
	// sol::table ac = L["actor_parameters"];
	// sol::table gc = ac["graphic_parameters"];
	// std::string file_path = gc["sprite_filepath"];
	// std::string texture_name = gc["sprite_name"];

	// skeleton::ServiceLocator::get<skeleton::SkeletonRenderer>()->add_texture(
	// file_path, texture_name);

	// this->script_on_update = L["on_update"];
	// this->script_handle_input = L["handle_input"];
}

void TestScene::on_input(SDL_Event &event) {
	//  this->script_handle_input(event);
}

void TestScene::on_update(float dt) {
	// std::cout << "TestScene update called" << std::endl;
}

void TestScene::on_update_physics(float dt) {
	// std::cout << "TestScene update physics called" << std::endl;
	ecs.progress(dt);
}

void TestScene::draw_debug_window() {
	// Create a window called "My First Tool", with a menu bar.
	bool my_tool_active = true;
	ImGui::Begin("Debug Window", &my_tool_active, ImGuiWindowFlags_MenuBar);
	if (ImGui::BeginMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */
			}
			if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */
			}
			if (ImGui::MenuItem("Close", "Ctrl+W")) {
				my_tool_active = false;
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
	ImGui::Text("Scene tag: %s", this->tag.c_str());
	// Display contents in a scrolling region
	auto query = ecs.query_builder<Position, Square>().build();
	ImGui::TextColored(ImVec4(1, 1, 0, 1), "Entities (%d)", query.count());
	ImGui::BeginChild("Scrolling");
	query.each([](flecs::iter itr, size_t it, Position &p, const Square &s) {
		ImGui::TextColored(ImVec4(s.r / 255.0f, s.g / 255.0f, s.b / 255.0f, 1),
						   "Entity #%d: (%.2f, %.2f)", it, p.x, p.y);
	});
	ImGui::EndChild();
	ImGui::End();
}

void TestScene::on_draw() {
	auto query = ecs.query_builder<Position, Square>().build();
	query.each([](Position &p, Square &s) {
		skeleton::ServiceLocator::get<skeleton::SkeletonRenderer>()->draw_rect(
			p.x, p.y, s.width, s.height, s.r, s.g, s.b, s.a);
	});
}

void TestScene::on_destroy() {}
