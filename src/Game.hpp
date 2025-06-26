#pragma once
#include "raylib-cpp/raylib-cpp.hpp"

class Game {
  Game() = default;
  ~Game() = default;

  void Update();
  void Render();

  void Setup(size_t start_scene_index);
  void Loop();
  void Close() const;
public:
  Game(const Game&) = delete;
  Game& operator=(const Game&) = delete;

  static Game& Instance() {
    static Game singleton;
    return singleton;
  }

  RWindow* window;
  RAudioDevice* audioDevice;

  void Run(size_t start_scene_index = 0);
};