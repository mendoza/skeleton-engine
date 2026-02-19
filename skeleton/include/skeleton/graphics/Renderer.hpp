#pragma once
#include "IRenderer.hpp"
#include <SDL.h>
#include <optional>
#include <string>
#include <unordered_map>

namespace skeleton::graphics {

class Renderer : public IRenderer {
public:
    static Renderer &get_instance() {
        static Renderer instance;
        return instance;
    }

    Renderer(const Renderer &) = delete;
    Renderer &operator=(const Renderer &) = delete;

    void create_window(std::string title, int width, int height, bool debug_mode) override;
    void begin() override;
    void end() override;
    void shutdown() override;

    int get_window_width() override;
    int get_window_height() override;

    void set_draw_color(skeleton::Color color) override;
    void draw_rect(skeleton::Rect rect, skeleton::Color color) override;
    void draw_texture(size_t key, skeleton::Rect *src, skeleton::Rect *dst) override;
    void draw_line(skeleton::Vec2 a, skeleton::Vec2 b, skeleton::Color color) override;
    void set_debug_mode(bool debug_mode) override;

    void set_camera(const skeleton::Camera2D &cam) override;
    void reset_camera() override;

    SDL_Renderer *get_sdl_renderer() { return renderer; }
    SDL_Window   *get_sdl_window()   { return window; }
    void store_texture(size_t key, SDL_Texture *texture);

private:
    Renderer();
    ~Renderer() override;

    bool debug_mode = false;
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_Color draw_color = {0, 0, 0, 255};
    std::unordered_map<size_t, SDL_Texture *> textures;
    std::optional<skeleton::Camera2D> active_camera;

    Vec2 to_screen(Vec2 p) const;
};

} // namespace skeleton::graphics
