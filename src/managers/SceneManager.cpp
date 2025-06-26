#include "SceneManager.hpp"

#include <iostream>
#include <utility>

#include "PendingChangesManager.hpp"

void SceneManager::Previous() {
  if (scenes_collection.size() <= 1) return;
  current_index = (current_index - 1 + scenes_collection.size()) % scenes_collection.size();
  Change(current_index);
}

void SceneManager::Next() {
  if (scenes_collection.size() <= 1) return;
  current_index = (current_index + 1) % scenes_collection.size();
  Change(current_index);
}

void SceneManager::Add(std::shared_ptr<SceneBase> scene) {
  this->scenes_collection.push_back(scene);
}

void SceneManager::Change(int scene_id) {
  PendingChangesManager::Instance().Add([this, scene_id]() -> void {
    this->current_index = scene_id;
    this->current_scene = scenes_collection[scene_id];
  });
}
void SceneManager::Change(std::string scene_name) {
  for (int i = 0; i < this->scenes_collection.size(); ++i) {
    if (this->scenes_collection[i]->name == scene_name) {
      this->Change(i);
      return;
    }
  }
}




