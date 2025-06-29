#include "MouseHitbox.hpp"
#include <algorithm>

MouseHitbox::MouseHitbox(const RCamera2D* camera, const RRectangle rec, const std::vector<RRectangle>& exclude_recs) {
  this->camera = camera;
  this->rec = rec;
  this->exclude_recs = exclude_recs;
}

static RVector2 translated_mouse_pos;

void MouseHitbox::Init() {

}

void MouseHitbox::Enter() {

}
void MouseHitbox::Leave() {

}

void MouseHitbox::Update() {
  translated_mouse_pos = this->camera->GetScreenToWorld(RMouse::GetPosition());
}
void MouseHitbox::Render() {

}

bool MouseHitbox::IsHover() {
  return
    this->rec.CheckCollision(translated_mouse_pos) &&
    std::ranges::none_of(this->exclude_recs, [](const RRectangle& r) { return r.CheckCollision(translated_mouse_pos); })
  ;
}
