#include "Renderer.hpp"
#include "ResourceManager.hpp"
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_sdlrenderer2.h>
#include <imgui.h>

namespace skeleton {
Renderer::Renderer() {
  this->window = nullptr;
  this->renderer = nullptr;
  logger->info("Created Renderer Service");
}

void Renderer::create_window(std::string title, int width, int height,
                             bool debug_mode) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
  }

  SDL_Window *window = SDL_CreateWindow(
      title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width,
      height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if (debug_mode) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO &io{ImGui::GetIO()};
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);
  }

  this->debug_mode = debug_mode;
  this->window = window;
  this->renderer = renderer;
  logger->info("Created window and renderer");
}

Renderer::~Renderer() {
  SDL_DestroyWindow(this->window);
  SDL_DestroyRenderer(this->renderer);
  logger->info("Destroyed Renderer service");
}

void Renderer::begin() {
  if (this->debug_mode) {
    // Start the Dear ImGui frame
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
  }
  SDL_SetRenderDrawColor(this->renderer, this->draw_color.r, this->draw_color.g,
                         this->draw_color.b, this->draw_color.a);
  SDL_RenderClear(this->renderer);
}

void Renderer::end() {
  if (this->debug_mode) {
    ImGui::Render();
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
  }
  SDL_RenderPresent(this->renderer);
}

void Renderer::shutdown() {
  if (this->debug_mode) {
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
  }
  SDL_DestroyRenderer(this->renderer);
  SDL_DestroyWindow(this->window);
  SDL_Quit();
}

void Renderer::draw_rect(int x, int y, int w, int h, int r, int g, int b,
                         int a) {
  SDL_Rect rect = {x, y, w, h};
  SDL_SetRenderDrawColor(this->renderer, r, g, b, a);
  SDL_RenderFillRect(this->renderer, &rect);
}

int Renderer::get_window_width() {
  int w, h;
  SDL_GetWindowSize(this->window, &w, &h);
  return w;
}

int Renderer::get_window_height() {
  int w, h;
  SDL_GetWindowSize(this->window, &w, &h);
  return h;
}

void Renderer::set_draw_color(SDL_Color color) { this->draw_color = color; }

void Renderer::draw_texture(std::string tag, SDL_Rect *src_rect,
                            SDL_Rect *dst_rect) {
  Resource *resource = skeleton::ResourceManager::get_instance().get(tag);
  TextureResource *texture = dynamic_cast<TextureResource *>(resource);
  if (!texture) {
    return;
  }
  SDL_RenderCopy(this->renderer, texture->texture, src_rect, dst_rect);
}

void Renderer::set_debug_mode(bool debug_mode) {
  this->debug_mode = debug_mode;
}
} // namespace skeleton
