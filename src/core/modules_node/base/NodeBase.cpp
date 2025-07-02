#include "NodeBase.hpp"

void NodeBase::RecalculateRec() {
  this->translated_rec = RRectangle(
    this->camera->GetScreenToWorld(this->rec.GetPosition()),
    this->camera->GetScreenToWorld(this->rec.GetSize())
  );
}


NodeBase::NodeBase(const RCamera2D* camera) {
  this->camera = camera;
}
void NodeBase::Init() {

}

void NodeBase::Enter() {

}
void NodeBase::Leave() {

}

void NodeBase::Update() {

}
void NodeBase::Render() {

}

void NodeBase::AdditionalUpdate() {

}
void NodeBase::AdditionalRender() {

}
