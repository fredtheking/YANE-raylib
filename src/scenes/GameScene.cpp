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
  node_engine.Update();

  if (RMouse::IsButtonDown(MOUSE_BUTTON_MIDDLE))
    node_engine.camera.target += RMouse::GetDelta().Negate() / node_engine.camera.zoom;

  node_engine.camera.zoom += RMouse::GetWheelMoveV().y * 300 * Game::Instance().window->GetFrameTime();
  node_engine.camera.zoom = std::clamp<float>(node_engine.camera.zoom, 0.2f, 5);

  const int KEY_SKIP_SPEED = 10000;
  if (RKeyboard::IsKeyPressed(KEY_LEFT)) node_engine.camera.target += RVector2(-1, 0) * KEY_SKIP_SPEED;
  if (RKeyboard::IsKeyPressed(KEY_RIGHT)) node_engine.camera.target += RVector2(1, 0) * KEY_SKIP_SPEED;
  if (RKeyboard::IsKeyPressed(KEY_UP)) node_engine.camera.target += RVector2(0, -1) * KEY_SKIP_SPEED;
  if (RKeyboard::IsKeyPressed(KEY_DOWN)) node_engine.camera.target += RVector2(0, 1) * KEY_SKIP_SPEED;
}
void GameScene::Render() {
  node_engine.Render();
}
