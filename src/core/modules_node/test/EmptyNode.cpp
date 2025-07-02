#include "EmptyNode.hpp"

EmptyNode::EmptyNode(const RCamera2D *camera) : NodeBase(camera) {

}
EmptyNode::~EmptyNode() = default;
void EmptyNode::AdditionalInit() {

}

void EmptyNode::AdditionalEnter() {

}
void EmptyNode::AdditionalLeave() {

}

void EmptyNode::AdditionalUpdate() {

}
void EmptyNode::AdditionalRender() {

}
