#pragma once
#include <raylib-cpp/raylib-cpp.hpp>
#include "NodePort.hpp"
#include "../../../utils/additions/UuidObject.hpp"
#include "../../../utils/interfaces/IScript.hpp"

class NodeBase : public IScript, public UuidObject {
protected:
  const RCamera2D* camera;
  RRectangle rec;
  RRectangle translated_rec;
  std::vector<NodePort> inputs;
  std::vector<NodePort> outputs;

  explicit NodeBase(const RCamera2D* camera);

  void RecalculateRec();

  void Init() final;
  void Enter() final;
  void Leave() final;
  void Update() final;
  void Render() final;

  virtual void AdditionalInit() = 0;
  virtual void AdditionalEnter() = 0;
  virtual void AdditionalLeave() = 0;
  virtual void AdditionalUpdate() = 0;
  virtual void AdditionalRender() = 0;
};
