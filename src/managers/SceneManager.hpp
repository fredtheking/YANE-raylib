#pragma once
#include <memory>
#include <vector>
#include "../utils/SceneBase.hpp"

class SceneManager {
  SceneManager() = default;
  ~SceneManager() = default;
public:
  SceneManager(const SceneManager&) = delete;
  SceneManager& operator=(const SceneManager&) = delete;

  static SceneManager& Instance() {
    static SceneManager singleton;
    return singleton;
  }

  size_t current_index = 0;
  SceneBase* current_scene = nullptr;
  std::vector<std::unique_ptr<SceneBase>> scenes_collection = {};

  void Previous();
  void Next();

  void Add(std::unique_ptr<SceneBase> scene);
  void Change(int scene_id);
  void Change(std::string scene_name);
};