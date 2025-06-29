#pragma once
#include <raylib-cpp/raylib-cpp.hpp>
#include "../utils/interfaces/IScript.hpp"

class MouseHitbox : public IScript {
  const RCamera2D* camera;
  RColor debug_color;

  RRectangle rec;
  std::vector<RRectangle> exclude_recs;

  MouseHitbox(
    const RCamera2D* camera,
    RRectangle rec,
    const std::vector<RRectangle> &exclude_recs
  );

  void Init() override;
  void Enter() override;
  void Leave() override;
  void Update() override;
  void Render() override;

public:
  bool IsHover();
};
