#pragma once
#include "../utils/SceneBase.hpp"

class MenuScene : public SceneBase {
public:
  void InitName() override;
  void Begin() override;

  void Enter() override;
  void Leave() override;

  void Update() override;
  void Render() override;
};