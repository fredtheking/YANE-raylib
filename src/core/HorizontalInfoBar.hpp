#pragma once
#include "../Game.hpp"
#include "../utils/interfaces/IScript.hpp"

class HorizontalInfoBar : public IScript {
  friend class NodeEngine;
  static constexpr float BAR_HEIGHT = 50;

  bool active = false;
  float active_pos_y;
  float rest_pos_y;
  float pos_y;

  RColor bg_color;
  RColor outline_color;
public:
  HorizontalInfoBar(
    RColor bg_color = RColor::DarkGray(),
    RColor outline_color = RColor::RayWhite()
  );

  void Init() override;
  void Enter() override;
  void Leave() override;
  void Update() override;
  void Render() override;
};
