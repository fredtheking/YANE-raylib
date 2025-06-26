#include <memory>
#include "Game.hpp"
#include "utils/Registry.hpp"
#include "scenes/GameScene.hpp"
#include "scenes/MenuScene.hpp"

int main(){
  Registry::AddScene(std::make_shared<MenuScene>());
  Registry::AddScene(std::make_shared<GameScene>());
  Game::Instance().Run(1);
}
