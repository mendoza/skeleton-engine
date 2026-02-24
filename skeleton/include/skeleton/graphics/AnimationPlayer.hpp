#pragma once
#include <skeleton/math/types.hpp>
#include <string>
#include <unordered_map>

namespace skeleton::graphics {

struct AnimationPlayer {
  void load(const std::string &path);
  void merge(const std::string &path);

  void           play(const std::string &name);
  void           update(float dt);
  skeleton::Rect current_rect() const;
  skeleton::Flip current_flip() const;
  size_t         current_texture() const;
  int            frame_w() const { return frame_w_; }
  int            frame_h() const { return frame_h_; }

  struct Clip {
    size_t texture_key = 0;
    int row = 0;
    int frames = 1;
    float fps = 8.0f;
    bool loop = true;
    skeleton::Flip flip = skeleton::Flip::None;
  };

private:
  int frame_w_ = 0, frame_h_ = 0, spacing_ = 0, margin_ = 0;
  std::unordered_map<std::string, Clip> clips_;
  std::string current_;
  int         frame_   = 0;
  float       elapsed_ = 0.0f;
};

} // namespace skeleton::graphics
