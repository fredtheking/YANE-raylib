#include "Game.hpp"

#include "managers/PendingChangesManager.hpp"
#include "managers/SceneManager.hpp"

#if defined(_DEBUG) || !defined(NDEBUG)
    #define only_debug(...) do { __VA_ARGS__ } while (0)
#else
    #define only_debug(...) do {} while (0)
#endif


void Game::Setup(size_t start_scene_index) {
  this->window->SetConfigFlags(FLAG_WINDOW_ALWAYS_RUN | FLAG_MSAA_4X_HINT | FLAG_WINDOW_RESIZABLE);
  this->window = new RWindow(1920, 1080, "Node Editor");
  this->audioDevice = new RAudioDevice();
  //this->window->SetTargetFPS(60);

  only_debug( this->debug_mode = true; );

  for (const std::shared_ptr<SceneBase>& scene: SceneManager::Instance().scenes_collection) {
    scene->InitName();
    scene->Init();
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
  only_debug(
    if (RKeyboard::IsKeyPressed(KEY_F1))
      SceneManager::Instance().Previous();
    if (RKeyboard::IsKeyPressed(KEY_F2))
      SceneManager::Instance().Next();
    if (RKeyboard::IsKeyPressed(KEY_F3) || RKeyboard::IsKeyPressed(KEY_GRAVE))
      this->debug_mode = !this->debug_mode;
  );

  SceneManager::Instance().current_scene->Update();
}

void Game::Render() {
  SceneManager::Instance().current_scene->Render();

  this->window->DrawFPS(10, 10);
  RText::Draw(SceneManager::Instance().current_scene->name + " - i: " + std::to_string(SceneManager::Instance().current_index), 10, 30, 20, RColor::Orange());
}