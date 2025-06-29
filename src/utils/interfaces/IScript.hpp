#pragma once

class IScript {
public:
  virtual ~IScript() = default;
  virtual void Init() = 0;
  virtual void Enter() = 0;
  virtual void Leave() = 0;
  virtual void Update() = 0;
  virtual void Render() = 0;
};