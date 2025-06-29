#pragma once
#include <string>
#include "interfaces/IScript.hpp"

class SceneBase : public IScript {
protected:
  SceneBase() = default;
public:
  std::string name;
  virtual ~SceneBase() = default;

  virtual void InitName();
  void Init() override;

  void Enter() override;
  void Leave() override;

  void Update() override;
  void Render() override;
};
