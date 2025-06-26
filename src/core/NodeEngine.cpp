#include "NodeEngine.hpp"

#include "../Game.hpp"

void NodeEngine::DrawViewportBackground() const {
  this->bg_color.DrawRectangle(this->camera.GetScreenToWorld(RVector2::Zero()), this->camera.GetScreenToWorld(
      this->size_infinite ?
      Game::Instance().window->GetSize() :
      this->size
    ));
}

void NodeEngine::DrawViewportGrid2D() const {
  Vector2 topLeft = this->camera.GetScreenToWorld(RVector2::Zero());
  Vector2 bottomRight = this->camera.GetScreenToWorld(
      this->size_infinite ?
      Game::Instance().window->GetSize() :
      this->size
    );

  int startX = (int)(topLeft.x / GRID_SPACING) * GRID_SPACING;
  int endX   = (int)(bottomRight.x / GRID_SPACING + 1) * GRID_SPACING;

  int startY = (int)(topLeft.y / GRID_SPACING) * GRID_SPACING;
  int endY   = (int)(bottomRight.y / GRID_SPACING + 1) * GRID_SPACING;

  for (int x = startX; x < endX; x += GRID_SPACING) {
    DrawLine(x, startY, x, endY, this->grid_color);
  }

  for (int y = startY; y < endY; y += GRID_SPACING) {
    DrawLine(startX, y, endX, y, this->grid_color);
  }
}




NodeEngine::NodeEngine(RVector2 size, RColor bg_color, RColor grid_color) {
  this->size = size;
  this->size_infinite = size == RVector2::One().Negate();
  this->bg_color = bg_color;
  this->grid_color = grid_color;
  this->camera = RCamera2D();
}
void NodeEngine::Begin() {

}

void NodeEngine::Enter() {

}
void NodeEngine::Leave() {

}

void NodeEngine::Update() {

}
void NodeEngine::Render() {
  this->camera.BeginMode();
  this->DrawViewportBackground();
  this->DrawViewportGrid2D();
  this->camera.EndMode();
}
