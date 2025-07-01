#include <memory>
#include "Game.hpp"
#include "utils/Registry.hpp"
#include "scenes/GameScene.hpp"
#include "scenes/TestScene.hpp"

int main(){
  Registry::AddScene(std::make_shared<TestScene>());
  Registry::AddScene(std::make_shared<GameScene>());
  Game::Instance().Run(1);
}
