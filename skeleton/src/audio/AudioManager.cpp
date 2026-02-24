#include <SDL.h>
#include <skeleton/audio/AudioManager.hpp>
#include <skeleton/core/Logger.hpp>
#include <sol/sol.hpp>

namespace skeleton::audio {

void AudioManager::init() {
  if (SDL_Init(SDL_INIT_AUDIO) < 0) {
    skeleton::core::Logger::error("SDL audio init failed: " + std::string(SDL_GetError()));
    return;
  }
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    skeleton::core::Logger::error("SDL_mixer init failed: " + std::string(Mix_GetError()));
}

void AudioManager::shutdown() {
  for (auto &[name, chunk] : sounds_) Mix_FreeChunk(chunk);
  for (auto &[name, music] : music_) Mix_FreeMusic(music);
  sounds_.clear();
  music_.clear();
  Mix_CloseAudio();
}

void AudioManager::load_bindings(const std::string &path) {
  sol::state lua;
  lua.open_libraries(sol::lib::base);
  bind_audio(lua);
  lua.script_file(path);
}

void AudioManager::bind_sound(const std::string &name, const std::string &path) {
  if (sounds_.count(name)) return;
  Mix_Chunk *chunk = Mix_LoadWAV(path.c_str());
  if (!chunk) {
    skeleton::core::Logger::error("Failed to load sound: " + path);
    return;
  }
  sounds_[name] = chunk;
}

void AudioManager::bind_music(const std::string &name, const std::string &path) {
  if (music_.count(name)) return;
  Mix_Music *music = Mix_LoadMUS(path.c_str());
  if (!music) {
    skeleton::core::Logger::error("Failed to load music: " + path);
    return;
  }
  music_[name] = music;
}

int AudioManager::play(const std::string &name, int loops) {
  auto it = sounds_.find(name);
  if (it == sounds_.end()) return -1;
  return Mix_PlayChannel(-1, it->second, loops);
}

void AudioManager::stop_channel(int channel) {
  if (channel >= 0) Mix_HaltChannel(channel);
}

void AudioManager::play_music(const std::string &name, int loops) {
  auto it = music_.find(name);
  if (it == music_.end()) return;
  Mix_PlayMusic(it->second, loops);
}

void AudioManager::stop_music()   { Mix_HaltMusic(); }
void AudioManager::pause_music()  { Mix_PauseMusic(); }
void AudioManager::resume_music() { Mix_ResumeMusic(); }

void AudioManager::set_sound_volume(int volume) { Mix_Volume(-1, volume); }
void AudioManager::set_music_volume(int volume) { Mix_VolumeMusic(volume); }

void bind_audio(sol::state &lua) {
  lua.new_usertype<AudioManager>("__AudioManager",
    "bind_sound",        &AudioManager::bind_sound,
    "bind_music",        &AudioManager::bind_music,
    "play",              sol::overload(
      [](AudioManager &am, const std::string &name) { am.play(name); }
    ),
    "play_music",        sol::overload(
      [](AudioManager &am, const std::string &name) { am.play_music(name); }
    ),
    "stop_music",        &AudioManager::stop_music,
    "pause_music",       &AudioManager::pause_music,
    "resume_music",      &AudioManager::resume_music,
    "set_sound_volume",  &AudioManager::set_sound_volume,
    "set_music_volume",  &AudioManager::set_music_volume
  );
  lua["audio"] = &AudioManager::get_instance();
}

} // namespace skeleton::audio
