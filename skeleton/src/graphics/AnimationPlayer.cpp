#include <skeleton/core/ResourceManager.hpp>
#include <skeleton/graphics/AnimationPlayer.hpp>
#include <sol/sol.hpp>

namespace skeleton::graphics {

static void parse_clips(sol::table &def,
                        std::unordered_map<std::string, AnimationPlayer::Clip> &out) {
  size_t texture_key = skeleton::core::ResourceManager::get_instance()
                           .load_texture(def["texture"]);
  sol::table anims = def["animations"];
  for (auto &[k, v] : anims) {
    sol::table t = v;
    AnimationPlayer::Clip clip;
    clip.texture_key = texture_key;
    clip.row = t["row"];
    clip.frames = t["frames"];
    clip.fps = t.get_or("fps", 8.0f);
    clip.loop = t.get_or("loop", true);
    std::string flip = t.get_or<std::string>("flip", "none");
    if (flip == "horizontal") clip.flip = skeleton::Flip::Horizontal;
    else if (flip == "vertical") clip.flip = skeleton::Flip::Vertical;
    out[k.as<std::string>()] = clip;
  }
}

void AnimationPlayer::load(const std::string &path) {
  sol::state lua;
  lua.open_libraries(sol::lib::base);
  sol::table def = lua.script_file(path);
  frame_w_ = def["frame_w"];
  frame_h_ = def["frame_h"];
  spacing_ = def.get_or("spacing", 0);
  margin_ = def.get_or("margin", 0);
  parse_clips(def, clips_);
  if (!clips_.empty())
    current_ = clips_.begin()->first;
}

void AnimationPlayer::merge(const std::string &path) {
  sol::state lua;
  lua.open_libraries(sol::lib::base);
  sol::table def = lua.script_file(path);
  parse_clips(def, clips_);
}

void AnimationPlayer::play(const std::string &name) {
  if (name == current_) return;
  if (clips_.find(name) == clips_.end()) return;
  current_ = name;
  frame_ = 0;
  elapsed_ = 0.0f;
}

void AnimationPlayer::update(float dt) {
  auto it = clips_.find(current_);
  if (it == clips_.end()) return;
  const auto &clip = it->second;
  elapsed_ += dt;
  float frame_time = 1.0f / clip.fps;
  while (elapsed_ >= frame_time) {
    elapsed_ -= frame_time;
    frame_++;
    if (frame_ >= clip.frames)
      frame_ = clip.loop ? 0 : clip.frames - 1;
  }
}

skeleton::Rect AnimationPlayer::current_rect() const {
  auto it = clips_.find(current_);
  if (it == clips_.end()) return {};
  return {
    (float)(margin_ + frame_ * (frame_w_ + spacing_)),
    (float)(margin_ + it->second.row * (frame_h_ + spacing_)),
    (float)frame_w_,
    (float)frame_h_,
  };
}

skeleton::Flip AnimationPlayer::current_flip() const {
  auto it = clips_.find(current_);
  if (it == clips_.end()) return skeleton::Flip::None;
  return it->second.flip;
}

size_t AnimationPlayer::current_texture() const {
  auto it = clips_.find(current_);
  if (it == clips_.end()) return 0;
  return it->second.texture_key;
}

} // namespace skeleton::graphics
