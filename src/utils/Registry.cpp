#include "Registry.hpp"
#include "../managers/SceneManager.hpp"

void Registry::AddScene(std::shared_ptr<SceneBase> scene) {
  SceneManager::Instance().Add(std::move(scene));
}
