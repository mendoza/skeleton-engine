#include <SDL.h>
#include <SDL_image.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_sdlrenderer2.h>
#include <imgui.h>
#include <skeleton/core/Logger.hpp>
#include <skeleton/graphics/Renderer.hpp>

namespace skeleton::graphics {

Renderer::Renderer() {
  skeleton::core::Logger::info("Created Renderer Service");
}

Renderer::~Renderer() {
  skeleton::core::Logger::info("Destroyed Renderer service");
}

void Renderer::create_window(std::string title, int width, int height,
                             bool debug_mode) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    skeleton::core::Logger::error("SDL could not initialize: " +
                                  std::string(SDL_GetError()));
    return;
  }

  window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, width, height,
                            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if (debug_mode) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io{ImGui::GetIO()};
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);
  }

  this->debug_mode = debug_mode;
  skeleton::core::Logger::info("Created window: " + title);
}

void Renderer::begin() {
  if (debug_mode) {
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
  }
  SDL_SetRenderDrawColor(renderer, draw_color.r, draw_color.g, draw_color.b,
                         draw_color.a);
  SDL_RenderClear(renderer);
}

void Renderer::end() {
  if (debug_mode) {
    ImGui::Render();
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
  }
  SDL_RenderPresent(renderer);
}

void Renderer::shutdown() {
  if (debug_mode) {
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
  }
  if (scene_texture_)
    SDL_DestroyTexture(scene_texture_);
  for (auto &[key, tex] : textures) {
    SDL_DestroyTexture(tex);
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

skeleton::Vec2 Renderer::to_screen(skeleton::Vec2 p) const {
  if (!active_camera)
    return p;
  int w = 0, h = 0;
  SDL_GetWindowSize(window, &w, &h);
  return active_camera->world_to_screen(p, (float)w, (float)h);
}

void Renderer::set_camera(const skeleton::Camera2D &cam) {
  active_camera = cam;
}

void Renderer::reset_camera() { active_camera.reset(); }

void Renderer::draw_rect(skeleton::Rect rect, skeleton::Color color) {
  skeleton::Vec2 pos = to_screen({rect.x, rect.y});
  float zoom = active_camera ? active_camera->zoom : 1.0f;
  SDL_Rect sdl_rect = {(int)pos.x, (int)pos.y, (int)(rect.w * zoom),
                       (int)(rect.h * zoom)};
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_RenderFillRect(renderer, &sdl_rect);
}

void Renderer::draw_texture(size_t key, skeleton::Rect *src,
                            skeleton::Rect *dst, float angle,
                            skeleton::Flip flip, uint8_t alpha,
                            skeleton::BlendMode blend) {
  auto it = textures.find(key);
  if (it == textures.end())
    return;

  SDL_Rect sdl_src, sdl_dst;
  SDL_Rect *p_src = nullptr, *p_dst = nullptr;
  if (src) {
    sdl_src = {(int)src->x, (int)src->y, (int)src->w, (int)src->h};
    p_src = &sdl_src;
  }
  if (dst) {
    skeleton::Vec2 pos = to_screen({dst->x, dst->y});
    float zoom = active_camera ? active_camera->zoom : 1.0f;
    sdl_dst = {(int)pos.x, (int)pos.y, (int)(dst->w * zoom),
               (int)(dst->h * zoom)};
    p_dst = &sdl_dst;
  }

  SDL_BlendMode sdl_blend;
  switch (blend) {
    case skeleton::BlendMode::Blend:
      sdl_blend = SDL_BLENDMODE_BLEND;
      break;
    case skeleton::BlendMode::Add:
      sdl_blend = SDL_BLENDMODE_ADD;
      break;
    case skeleton::BlendMode::Mod:
      sdl_blend = SDL_BLENDMODE_MOD;
      break;
    default:
      sdl_blend = SDL_BLENDMODE_NONE;
      break;
  }

  SDL_SetTextureBlendMode(it->second, sdl_blend);
  SDL_SetTextureAlphaMod(it->second, alpha);
  SDL_RenderCopyEx(renderer, it->second, p_src, p_dst, (double)angle, nullptr,
                   static_cast<SDL_RendererFlip>(static_cast<int>(flip)));
  SDL_SetTextureAlphaMod(it->second, 255);
  SDL_SetTextureBlendMode(it->second, SDL_BLENDMODE_NONE);
}

void Renderer::store_texture(size_t key, SDL_Texture *texture) {
  textures[key] = texture;
}

void Renderer::begin_scene_capture() {
  if (!scene_texture_) {
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    scene_texture_ = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                       SDL_TEXTUREACCESS_TARGET, w, h);
  }
  SDL_SetRenderTarget(renderer, scene_texture_);
  SDL_SetRenderDrawColor(renderer, draw_color.r, draw_color.g, draw_color.b,
                         draw_color.a);
  SDL_RenderClear(renderer);
}

void Renderer::end_scene_capture() { SDL_SetRenderTarget(renderer, nullptr); }

int Renderer::get_window_width() {
  int w, h;
  SDL_GetWindowSize(window, &w, &h);
  return w;
}

int Renderer::get_window_height() {
  int w, h;
  SDL_GetWindowSize(window, &w, &h);
  return h;
}

void Renderer::draw_line(skeleton::Vec2 a, skeleton::Vec2 b,
                         skeleton::Color color) {
  skeleton::Vec2 sa = to_screen(a);
  skeleton::Vec2 sb = to_screen(b);
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_RenderDrawLine(renderer, (int)sa.x, (int)sa.y, (int)sb.x, (int)sb.y);
}

void Renderer::set_draw_color(skeleton::Color color) {
  draw_color = {color.r, color.g, color.b, color.a};
}

void Renderer::set_debug_mode(bool dm) { debug_mode = dm; }

} // namespace skeleton::graphics
