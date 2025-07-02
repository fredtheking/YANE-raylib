#pragma once
#include <memory>
#include <vector>
#include <raylib-cpp/raylib-cpp.hpp>
#include "HorizontalInfoBar.hpp"
#include "../utils/interfaces/IScript.hpp"
#include "modules_node/base/NodeBase.hpp"

class NodeEngine final : public IScript {
  static constexpr int BORDER_LIMIT = 6000000;
  RColor bg_color;
  RColor grid_color;

  void RecalculateCameraOffset();

  void ResetCamera();
  void DrawViewportBackground() const;
  void DrawViewportGrid2D() const;

public:
  NodeEngine(const NodeEngine&) = delete;
  NodeEngine& operator=(const NodeEngine&) = delete;
  NodeEngine(
    RColor bg_color = RColor::DarkGray(),
    RColor grid_color = RColor::Gray()
  );

  RCamera2D camera;
  HorizontalInfoBar infobar;
  std::vector<std::unique_ptr<NodeBase>> nodes;

  void Init() override;
  void Enter() override;
  void Leave() override;
  void Update() override;
  void Render() override;
};
