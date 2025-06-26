#pragma once
#include <memory>
#include "SceneBase.hpp"

class Registry {
public:
  static void AddScene(std::shared_ptr<SceneBase> scene);
};
