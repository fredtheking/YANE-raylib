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

  NodeBase(const RCamera2D* camera);

  void RecalculateRec();

  void Init() override;
  void Enter() override;
  void Leave() override;
  void Update() final;
  void Render() final;

  virtual void AdditionalUpdate() = 0;
  virtual void AdditionalRender() = 0;
};
