#pragma once
#include <raylib-cpp/raylib-cpp.hpp>
#include "../utils/interfaces/IScript.hpp"

class MouseHitbox : public IScript {
  const RCamera2D* camera;
  RColor debug_color;

  RRectangle rec;
  std::vector<RRectangle> exclude_recs;
  RTexture2D hitbox_texture;

  bool HoverHandle() const;
  bool DragHandle(int i) const;
  void HitboxTextureUpdate();

public:
  MouseHitbox() = default;
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

  void SetPosition(RVector2 position);

  bool hover = false;
  bool click[3] = {false, false, false};
  bool press[3] = {false, false, false};
  bool down[3] = {false, false, false};
  bool hold[3] = {false, false, false};
  bool release[3] = {false, false, false};
  bool drag[3] = {false, false, false};
};
