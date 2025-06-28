#include "GameScene.hpp"

#include <algorithm>

#include "../Game.hpp"
#include "../core/NodeEngine.hpp"

Vector2& operator+=(Vector2& lhs, const RVector2& rhs) {
  lhs.x += rhs.x;
  lhs.y += rhs.y;
  return lhs;
}

NodeEngine node_engine = {RColor::Black(), RColor{13, 13, 13}};
RVector2 drag_origin_world;

void MoveCamera(RCamera2D& camera) {
  if (RMouse::IsButtonPressed(MOUSE_BUTTON_MIDDLE))
    drag_origin_world = camera.GetScreenToWorld(RMouse::GetPosition());

  if (RMouse::IsButtonDown(MOUSE_BUTTON_MIDDLE)) {
    RVector2 current_world = camera.GetScreenToWorld(RMouse::GetPosition());
    camera.target += drag_origin_world - current_world;
  }
}

void GameScene::InitName() {
  this->name = "GameScene";
}
void GameScene::Begin() {
  node_engine.Begin();
}

void GameScene::Enter() {
  node_engine.Enter();
}
void GameScene::Leave() {
  node_engine.Leave();
}

void GameScene::Update() {
  MoveCamera(node_engine.camera);
  node_engine.Update();


  if (RMouse::IsButtonDown(MOUSE_BUTTON_MIDDLE))
    node_engine.camera.target += RMouse::GetDelta().Negate() / node_engine.camera.zoom;

  node_engine.camera.zoom += RMouse::GetWheelMoveV().y * 0.1f;
  node_engine.camera.zoom = std::clamp<float>(node_engine.camera.zoom, 0.5, 3.0);

  constexpr int KEY_SKIP_SPEED = 1000000;
  if (RKeyboard::IsKeyPressed(KEY_LEFT))  node_engine.camera.target += RVector2(-KEY_SKIP_SPEED, 0);
  if (RKeyboard::IsKeyPressed(KEY_RIGHT)) node_engine.camera.target += RVector2(KEY_SKIP_SPEED, 0);
  if (RKeyboard::IsKeyPressed(KEY_UP))    node_engine.camera.target += RVector2(0, -KEY_SKIP_SPEED);
  if (RKeyboard::IsKeyPressed(KEY_DOWN))  node_engine.camera.target += RVector2(0, KEY_SKIP_SPEED);
}
void GameScene::Render() {
  node_engine.Render();
}
