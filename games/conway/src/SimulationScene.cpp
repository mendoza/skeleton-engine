#include "SimulationScene.hpp"
#include <cstdlib>
#include <ctime>
#include <imgui.h>
#include <skeleton/debug/widget_registry.hpp>
#include <skeleton/graphics/Renderer.hpp>
#include <skeleton/math/types.hpp>

static const int CELL_SIZE = 10;

struct ConwayGrid {
    int cols, rows;
    std::vector<int> cells;
    std::vector<int> next;
};

static void register_debug_widgets() {
    static bool registered = false;
    if (registered) return;
    registered = true;

    skeleton::debug::register_widget<ConwayGrid>("Conway Grid", [](ConwayGrid &g) {
        ImGui::Text("Size: %d x %d", g.cols, g.rows);
        int alive = 0;
        for (int c : g.cells) alive += c;
        ImGui::Text("Alive cells: %d", alive);
    });
}

SimulationScene::SimulationScene(std::string name) : Scene(std::move(name)) {
    srand((unsigned)time(nullptr));
    register_debug_widgets();
}

void SimulationScene::on_init() {
    auto &r = skeleton::graphics::Renderer::get_instance();
    int cols = r.get_window_width()  / CELL_SIZE;
    int rows = r.get_window_height() / CELL_SIZE;

    auto entity = registry.create();
    auto &grid  = registry.emplace<ConwayGrid>(entity, cols, rows);
    grid.cells.resize(cols * rows);
    grid.next.resize(cols * rows, 0);
    for (auto &c : grid.cells) c = rand() % 2;
}

void SimulationScene::on_input(SDL_Event &) {}

void SimulationScene::on_update(double) {}

void SimulationScene::on_fixed_update(double) {
    auto view = registry.view<ConwayGrid>();
    for (auto [entity, grid] : view.each()) {
        for (int x = 0; x < grid.cols; x++) {
            for (int y = 0; y < grid.rows; y++) {
                int alive = 0;
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        if (dx == 0 && dy == 0) continue;
                        int nx = x + dx, ny = y + dy;
                        if (nx < 0 || nx >= grid.cols || ny < 0 || ny >= grid.rows) continue;
                        alive += grid.cells[nx + ny * grid.cols];
                    }
                }
                int cur = grid.cells[x + y * grid.cols];
                grid.next[x + y * grid.cols] =
                    (cur && (alive == 2 || alive == 3)) || (!cur && alive == 3) ? 1 : 0;
            }
        }
        std::swap(grid.cells, grid.next);
    }
}

void SimulationScene::on_draw() {
    auto &r    = skeleton::graphics::Renderer::get_instance();
    auto  view = registry.view<ConwayGrid>();
    for (auto [entity, grid] : view.each()) {
        for (int x = 0; x < grid.cols; x++) {
            for (int y = 0; y < grid.rows; y++) {
                if (!grid.cells[x + y * grid.cols]) continue;
                r.draw_rect(
                    {(float)(x * CELL_SIZE), (float)(y * CELL_SIZE),
                     (float)CELL_SIZE,       (float)CELL_SIZE},
                    {255, 255, 255, 255});
            }
        }
    }
}

void SimulationScene::on_destroy() {}

void SimulationScene::on_debug_ui() {
    ImGui::Begin("Debug");
    skeleton::debug::draw_all_entities(registry);
    ImGui::End();
}
