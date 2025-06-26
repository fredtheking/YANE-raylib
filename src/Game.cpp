#include "Game.hpp"

#include "managers/PendingChangesManager.hpp"
#include "managers/SceneManager.hpp"

void Game::Setup(size_t start_scene_index) {
  this->window = new RWindow(1920, 1080, "Node Editor");
  this->window->SetConfigFlags(FLAG_WINDOW_ALWAYS_RUN | FLAG_MSAA_4X_HINT);
  this->audioDevice = new RAudioDevice();

  for (const std::shared_ptr<SceneBase>& scene: SceneManager::Instance().scenes_collection) {
    scene->InitName();
    scene->Begin();
  }

  SceneManager::Instance().Change(start_scene_index);
  PendingChangesManager::Instance().Apply();
}

void Game::Loop() {
  while (!this->window->ShouldClose()){
    this->Update();
    PendingChangesManager::Instance().Apply();
    this->window->BeginDrawing();
    this->window->ClearBackground(RColor::Black());
    this->Render();
    PendingChangesManager::Instance().Apply();
    this->window->EndDrawing();
  }
}

void Game::Close() const {
  delete this->audioDevice;
  delete this->window;
}

void Game::Run(size_t start_scene_index) {
  this->Setup(start_scene_index);
  this->Loop();
  this->Close();
}



void Game::Update() {
  if (RKeyboard::IsKeyPressed(KEY_F1))
    SceneManager::Instance().Previous();
  if (RKeyboard::IsKeyPressed(KEY_F2))
    SceneManager::Instance().Next();

  SceneManager::Instance().current_scene->Update();
}

void Game::Render() {
  SceneManager::Instance().current_scene->Render();

  this->window->DrawFPS(10, 10);
  RText::Draw(SceneManager::Instance().current_scene->name + " - " + std::to_string(SceneManager::Instance().current_index), 10, 30, 20, RColor::Orange());
}