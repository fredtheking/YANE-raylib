#pragma once
#include "../base/NodeBase.hpp"

class EmptyNode final : public NodeBase {
public:
  explicit EmptyNode(const RCamera2D *camera);
  ~EmptyNode() override;

protected:
  void AdditionalInit() override;
  void AdditionalEnter() override;
  void AdditionalLeave() override;
  void AdditionalUpdate() override;
  void AdditionalRender() override;
};
