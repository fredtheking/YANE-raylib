#pragma once
#include "../utils/SceneBase.hpp"

class TestScene : public SceneBase {
public:
  void InitName() override;
  void Init() override;

  void Enter() override;
  void Leave() override;

  void Update() override;
  void Render() override;
};