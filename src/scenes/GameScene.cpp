#include "GameScene.hpp"

#include <algorithm>

#include "../Game.hpp"
#include "../core/NodeEngine.hpp"

Vector2& operator+=(Vector2& lhs, const RVector2& rhs) {
  lhs.x += rhs.x;
  lhs.y += rhs.y;
  return lhs;
}

NodeEngine node_engine = {};
RVector2 dragOriginWorld;

void MoveCamera(RCamera2D& camera) {
  if (RMouse::IsButtonPressed(MOUSE_BUTTON_MIDDLE))
    dragOriginWorld = camera.GetScreenToWorld(RMouse::GetPosition());

  if (RMouse::IsButtonDown(MOUSE_BUTTON_MIDDLE)) {
    RVector2 currentWorld = camera.GetScreenToWorld(RMouse::GetPosition());
    camera.target += dragOriginWorld - currentWorld;
  }

  camera.target = RVector2(round(camera.target.x), round(camera.target.y));
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

  node_engine.camera.zoom += RMouse::GetWheelMoveV().y * 300 * Game::Instance().window->GetFrameTime();
  node_engine.camera.zoom = std::clamp<float>(node_engine.camera.zoom, 0.5, 3);

  constexpr int KEY_SKIP_SPEED = 1000000;
  if (RKeyboard::IsKeyPressed(KEY_LEFT))  node_engine.camera.target += RVector2(-KEY_SKIP_SPEED, 0);
  if (RKeyboard::IsKeyPressed(KEY_RIGHT)) node_engine.camera.target += RVector2(KEY_SKIP_SPEED, 0);
  if (RKeyboard::IsKeyPressed(KEY_UP))    node_engine.camera.target += RVector2(0, -KEY_SKIP_SPEED);
  if (RKeyboard::IsKeyPressed(KEY_DOWN))  node_engine.camera.target += RVector2(0, KEY_SKIP_SPEED);
}
void GameScene::Render() {
  node_engine.Render();
}
