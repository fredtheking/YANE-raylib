#include "GameScene.hpp"
#include "../Game.hpp"
#include "../core/NodeEngine.hpp"

Vector2& operator+=(Vector2& lhs, const RVector2& rhs) {
  lhs.x += rhs.x;
  lhs.y += rhs.y;
  return lhs;
}

NodeEngine node_engine = {
  //RVector2(100)
};



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
    node_engine.camera.target += RMouse::GetDelta().Negate();
}
void GameScene::Render() {
  node_engine.Render();
}
