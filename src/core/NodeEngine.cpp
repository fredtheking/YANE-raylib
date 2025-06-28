#include "NodeEngine.hpp"

#include "../Game.hpp"

RVector2 GetCameraNewOffset() {
  return Game::Instance().window->GetSize()/2;
}

void NodeEngine::RecalculateCameraOffset() {
  this->camera.offset = GetCameraNewOffset();
}

void NodeEngine::ResetCamera() {
  this->camera = RCamera2D(GetCameraNewOffset(), RVector2::Zero(), 0, 1);
}

Vector2 operator-(const Vector2 & lhs, const Vector2 & rhs) {
  return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
}

void NodeEngine::DrawViewportBackground() const {
  Game::Instance().window->ClearBackground(bg_color);
}

void NodeEngine::DrawViewportGrid2D() const {
  Vector2 topLeft = this->camera.GetScreenToWorld(RVector2::Zero());
  Vector2 bottomRight = this->camera.GetScreenToWorld(Game::Instance().window->GetSize());

  constexpr float intensity = 0.4f;
  float time = Game::Instance().window->GetTime() / 2;

  int startX = static_cast<int>(std::floor(topLeft.x / GRID_SPACING)) * GRID_SPACING;
  int endX   = static_cast<int>(std::ceil(bottomRight.x / GRID_SPACING)) * GRID_SPACING;

  int startY = static_cast<int>(std::floor(topLeft.y / GRID_SPACING)) * GRID_SPACING;
  int endY   = static_cast<int>(std::ceil(bottomRight.y / GRID_SPACING)) * GRID_SPACING;

  for (int x = startX, i = 0; x <= endX; x += GRID_SPACING, ++i) {
    float offset = sinf(time * 2.0f + i) * intensity;
    this->grid_color.DrawLine(
      { x + offset, topLeft.y },
      { x + offset, bottomRight.y }
    );
  }

  for (int y = startY, i = 0; y <= endY; y += GRID_SPACING, ++i) {
    float offset = sinf(time * 1.2f + i) * intensity;
    this->grid_color.DrawLine(
      { topLeft.x, y + offset },
      { bottomRight.x, y + offset }
    );
  }



  RColor::Red().Alpha(0.35).DrawLine(
    { 0.0f, topLeft.y },
    { 0.0f, bottomRight.y }
  );

  RColor::Blue().Alpha(0.35).DrawLine(
    { topLeft.x, 0.0f },
    { bottomRight.x, 0.0f }
  );
}




NodeEngine::NodeEngine(RColor bg_color, RColor grid_color) {
  this->bg_color = bg_color;
  this->grid_color = grid_color;
}
void NodeEngine::Begin() {
  ResetCamera();
}

void NodeEngine::Enter() {

}
void NodeEngine::Leave() {

}

void NodeEngine::Update() {
  if (Game::Instance().window->IsResized())
    RecalculateCameraOffset();

  this->camera.target = static_cast<RVector2>(this->camera.target).Clamp(RVector2(-BORDER_LIMIT, -BORDER_LIMIT), RVector2(BORDER_LIMIT, BORDER_LIMIT));
}
void NodeEngine::Render() {
  this->camera.BeginMode();
  this->DrawViewportBackground();
  this->DrawViewportGrid2D();
  this->camera.EndMode();
  RColor::Green().DrawText(RVector2(this->camera.GetTarget()).ToString(), 10, 70, 20);
}
