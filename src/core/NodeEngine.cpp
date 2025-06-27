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
  Vector2 determined_start = this->camera.GetScreenToWorld(RVector2::Zero());
  Vector2 determined_end = this->camera.GetScreenToWorld(Game::Instance().window->GetSize());

  int startX = (int)(determined_start.x / GRID_SPACING - 1) * GRID_SPACING;
  int endX   = (int)(determined_end.x   / GRID_SPACING + 1) * GRID_SPACING;

  int startY = (int)(determined_start.y / GRID_SPACING - 1) * GRID_SPACING;
  int endY   = (int)(determined_end.y   / GRID_SPACING + 1) * GRID_SPACING;

  for (int x = startX; x < endX; x += GRID_SPACING)
    DrawLine(x, startY, x, endY, this->grid_color);

  for (int y = startY; y < endY; y += GRID_SPACING)
    DrawLine(startX, y, endX, y, this->grid_color);
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
