#ifndef GAME_OF_LIFE_HPP
#define GAME_OF_LIFE_HPP
#include "skeleton/Core/Logger.hpp"
#include <skeleton/Graphics/Renderer.hpp>
#include <skeleton/Nodes/DrawableNode.hpp>

class GameOfLife : public skeleton::DrawableNode {
  double acumulated_dt = 0;
  int cell_size = 10;
  int screen_h = 1080;
  int screen_w = 1920;
  int **cells;

private:
  // create int matrix to store the cells
  int ** create_cells(int screen_h, int screen_w) {
    int **cells = new int *[screen_h];
    for (int i = 0; i < screen_h; i++) {
      cells[i] = new int[screen_w];
    }
    return cells;
  }
public:
  bool is_ready_to_die = false;
  GameOfLife(int screen_h, int screen_w) : DrawableNode() {
    srand(time(NULL));
    this->name = "board";
    this->x = x;
    this->y = y;
    this->screen_h = screen_h;
    this->screen_w = screen_w;

    this->cells = new int *[screen_h];
    for (int i = 0; i < screen_h; i++) {
      this->cells[i] = new int[screen_w];
    }

    // create cells to cover the screen
    // taking in account the cell size will be horizontal and vertical
    // the x and y values will be the position of the square
    // the cell size will be the size of the square
    // and the last value will be if the cell is alive or not (random 50%)
    int num_cells_x = screen_w / cell_size;
    int num_cells_y = screen_h / cell_size;
    for (int i = 0; i < num_cells_x; i++) {
      for (int j = 0; j < num_cells_y; j++) {
        bool is_alive = rand() % 2;
        this->cells[i][j] = is_alive;
      }
    }
  };

  virtual ~GameOfLife(){};

  virtual void handle_draw() override {
    for (int i = 0; i < screen_w / cell_size; i++) {
      for (int j = 0; j < screen_h / cell_size; j++) {
        if (this->cells[i][j] == 1) {
          skeleton::Renderer::get_instance().draw_rect(
              i * cell_size, j * cell_size, cell_size, cell_size, 255, 255, 255,
              255);
        }
      }
    }
  };

  virtual void handle_fixed_update(double dt) override {
    this->acumulated_dt += dt;
    /*if (int(this->acumulated_dt) != int(this->acumulated_dt - dt)) {*/
      int **new_cells = new int *[screen_h];
      for (int i = 0; i < screen_h; i++) {
        new_cells[i] = new int[screen_w];
      }

      for (int i = 0; i < screen_w / cell_size; i++) {
        for (int j = 0; j < screen_h / cell_size; j++) {
          int alive_neighbours = 0;
          for (int x = -1; x < 2; x++) {
            for (int y = -1; y < 2; y++) {
              if (x == 0 && y == 0) {
                continue;
              }
              int new_x = i + x;
              int new_y = j + y;
              if (new_x < 0 || new_x >= screen_w / cell_size || new_y < 0 ||
                  new_y >= screen_h / cell_size) {
                continue;
              }
              if (this->cells[new_x][new_y] == 1) {
                alive_neighbours++;
              }
            }
          }
          if (this->cells[i][j] == 1) {
            if (alive_neighbours < 2 || alive_neighbours > 3) {
              new_cells[i][j] = 0;
            } else {
              new_cells[i][j] = 1;
            }
          } else {
            if (alive_neighbours == 3) {
              new_cells[i][j] = 1;
            } else {
              new_cells[i][j] = 0;
            }
          }
        }
      }

      for (int i = 0; i < screen_w / cell_size; i++) {
        for (int j = 0; j < screen_h / cell_size; j++) {
          this->cells[i][j] = new_cells[i][j];
        }
      }
    /*}*/
  };

  virtual void handle_update(double dt) override {}
};
#endif
