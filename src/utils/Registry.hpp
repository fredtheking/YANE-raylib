#pragma once
#include <memory>
#include "SceneBase.hpp"

class Registry {
public:
  static void AddScene(std::unique_ptr<SceneBase> scene);
};
