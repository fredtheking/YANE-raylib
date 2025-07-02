#include "Registry.hpp"
#include "../managers/SceneManager.hpp"

void Registry::AddScene(std::unique_ptr<SceneBase> scene) {
  SceneManager::Instance().Add(std::move(scene));
}
