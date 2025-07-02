#include <memory>
#include "Game.hpp"
#include "utils/Registry.hpp"
#include "scenes/GameScene.hpp"
#include "scenes/TestScene.hpp"

int main(){
  Registry::AddScene(std::make_unique<TestScene>());
  Registry::AddScene(std::make_unique<GameScene>());
  Game::Instance().Run(1);
}
