#pragma once
#include <SDL_mixer.h>
#include <sol/sol.hpp>
#include <string>
#include <unordered_map>

namespace skeleton::audio {

class AudioManager {
public:
  static AudioManager &get_instance() {
    static AudioManager instance;
    return instance;
  }
  AudioManager(const AudioManager &) = delete;
  AudioManager &operator=(const AudioManager &) = delete;

  void init();
  void shutdown();
  void load_bindings(const std::string &path);

  void bind_sound(const std::string &name, const std::string &path);
  void bind_music(const std::string &name, const std::string &path);

  int play(const std::string &name, int loops = 0);
  void stop_channel(int channel);

  void play_music(const std::string &name, int loops = -1);
  void stop_music();
  void pause_music();
  void resume_music();

  void set_sound_volume(int volume);
  void set_music_volume(int volume);

private:
  AudioManager() = default;
  ~AudioManager() = default;

  std::unordered_map<std::string, Mix_Chunk *> sounds_;
  std::unordered_map<std::string, Mix_Music *> music_;
};

void bind_audio(sol::state &lua);

} // namespace skeleton::audio
