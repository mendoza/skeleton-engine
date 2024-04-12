#ifndef SKELETON_UTILS_HPP
#define SKELETON_UTILS_HPP

#include "Logger.hpp"
#include "Renderer.hpp"
#include <SDL.h>
#include <SDL_keyboard.h>
#include <sol/sol.hpp>
namespace skeleton {

inline void setLogger(sol::state &L) {
  sol::usertype<skeleton::Logger> loggerUserType =
      L.new_usertype<skeleton::Logger>("Logger");

  loggerUserType["log"] = &skeleton::Logger::log;
  loggerUserType["warning"] = &skeleton::Logger::warning;
  loggerUserType["error"] = &skeleton::Logger::error;
  loggerUserType["create"] = &skeleton::Logger::get_instance;

  skeleton::Logger *logger = logger->get_instance();

  L["console"] = logger;
}

inline void setSDLTypes(sol::state &L) {
  sol::table skeleton = L["skeleton"];
  // 	"keyboard",
  // 	{{"right", SDLK_RIGHT}, {"left", SDLK_LEFT}, {"space", SDLK_SPACE}});

  // skeleton.new_enum<SDL_EventType>(
  // 	"event_type",
  // 	{{"key_pressed", SDL_KEYDOWN}, {"key_released", SDL_KEYUP}});

  // sol::usertype<SDL_Event> eventType = L.new_usertype<SDL_Event>("Event");

  // eventType["type"] = sol::readonly(&SDL_Event::type);

  // sol::usertype<SDL_KeyboardEvent> keyEventType =
  // 	L.new_usertype<SDL_KeyboardEvent>("KeyEvent");

  // keyEventType["keysym"] = sol::readonly(&SDL_KeyboardEvent::keysym);
}

inline void setExtraTypes(sol::state &L) {
  // sol::usertype<sf::Vector2f> sfVector2f = L.new_usertype<sf::Vector2f>(
  // 	"vector_2f",
  // 	sol::constructors<sf::Vector2f(), sf::Vector2f(float, float)>(), "x",
  // 	&sf::Vector2f::x, "y", &sf::Vector2f::y);
}
inline void setRenderService(sol::state &L) {
  // L.new_usertype<skeleton::SkeletonRenderer>(
  // "SkeletonRenderer", "update", &skeleton::SkeletonRenderer::update,
  // "clear", &skeleton::SkeletonRenderer::clear, "shutdown",
  // &skeleton::SkeletonRenderer::shutdown, "add_texture",
  // &skeleton::SkeletonRenderer::add_texture, "draw_texture",
  // &skeleton::SkeletonRenderer::draw_texture, "draw_rect",
  // &skeleton::SkeletonRenderer::draw_rect, "get_texture",
  // &skeleton::SkeletonRenderer::get_texture, "get_window_width",
  // &skeleton::SkeletonRenderer::get_window_width, "get_window_height",
  // &skeleton::SkeletonRenderer::get_window_height, "set_draw_color",
  // &skeleton::SkeletonRenderer::set_draw_color);

  sol::table skeleton = L["skeleton"];
  // skeleton["renderer"] =
  // skeleton::ServiceLocator::get<skeleton::SkeletonRenderer>();
}

inline void setEngineMetadata(sol::state &L) {
  sol::table skeleton = L.create_named_table("skeleton");
  setSDLTypes(L);
  setRenderService(L);
  setLogger(L);
  setExtraTypes(L);
}

} // namespace skeleton

#endif
