#pragma once
#include <raylib-cpp/raylib-cpp.hpp>
#include "../utils/interfaces/IScript.hpp"

class NodeEngine : public IScript {
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

  void Begin() override;
  void Enter() override;
  void Leave() override;
  void Update() override;
  void Render() override;
};
