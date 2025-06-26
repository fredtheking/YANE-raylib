#include "GameScene.hpp"
#include "../Game.hpp"
#include "../core/NodeEngine.hpp"

NodeEngine node_engine = {RVector2(500, 500)};

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
}
void GameScene::Render() {
  node_engine.Render();
}
