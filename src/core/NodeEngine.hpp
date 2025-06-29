#pragma once
#include <raylib-cpp/raylib-cpp.hpp>
#include "HorizontalInfoBar.hpp"
#include "../utils/interfaces/IScript.hpp"

class NodeEngine final : public IScript {
  static constexpr int BORDER_LIMIT = 6000000;
  RColor bg_color;
  RColor grid_color;

  void RecalculateCameraOffset();

  void ResetCamera();
  void DrawViewportBackground() const;
  void DrawViewportGrid2D() const;

public:
  NodeEngine(
    RColor bg_color = RColor::DarkGray(),
    RColor grid_color = RColor::Gray()
  );

  static const int GRID_SPACING = 16;
  RCamera2D camera;
  HorizontalInfoBar infobar;

  void Init() override;
  void Enter() override;
  void Leave() override;
  void Update() override;
  void Render() override;
};
