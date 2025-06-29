#pragma once
#include <raylib-cpp/raylib-cpp.hpp>
#include "NodePort.hpp"
#include "../../NodeEngine.hpp"
#include "../../../utils/additions/UuidObject.hpp"
#include "../../../utils/interfaces/IScript.hpp"

class NodeBase : public IScript, public UuidObject {
protected:
  const RCamera2D* camera;
  RRectangle rec;
  RRectangle translated_rec;
  std::vector<NodePort> inputs;
  std::vector<NodePort> outputs;

  const float HEADER_HEIGHT = NodeEngine::GRID_SPACING;

  NodeBase(const RCamera2D* camera);

  void RecalculateRec();

  void Init() override;
  void Enter() override;
  void Leave() override;
  void Update() final;
  void Render() final;

  virtual void AdditionalUpdate();
  virtual void AdditionalRender();
};
