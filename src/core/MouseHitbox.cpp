#include "MouseHitbox.hpp"
#include <algorithm>

static RVector2 translated_mouse_pos;


bool MouseHitbox::HoverHandle() const {
  return
    this->rec.CheckCollision(translated_mouse_pos) &&
    std::ranges::none_of(this->exclude_recs, [](const RRectangle& r) { return r.CheckCollision(translated_mouse_pos); })
  ;
}
bool MouseHitbox::DragHandle(int i) const {
  if (!this->drag[i] && this->press[i]) return true;
  if (this->drag[i] && !this->down[i]) return false;
  return this->drag[i];
}
void MouseHitbox::HitboxTextureUpdate() {
  RImage temp_image = RImage::Color(rec.width, rec.height, RColor::Red().Fade(0.3));


  for (const RRectangle& rex : exclude_recs) {
    RRectangle localEx = {
      rex.x - rec.x,
      rex.y - rec.y,
      rex.width,
      rex.height
    };
    temp_image.DrawRectangle(localEx, RColor::Blank());
  }


  RTexture2D texture = RTexture2D(temp_image);
  temp_image.Unload();
  this->hitbox_texture = std::move(texture);
}
void MouseHitbox::SetPosition(const RVector2 position) {
  this->rec.SetPosition(position);
}



MouseHitbox::MouseHitbox(const RCamera2D* camera, const RRectangle rec, const std::vector<RRectangle>& exclude_recs) {
  this->camera = camera;
  this->rec = rec;
  this->exclude_recs = exclude_recs;
}
void MouseHitbox::Init() {
  HitboxTextureUpdate();
}

void MouseHitbox::Enter() {

}
void MouseHitbox::Leave() {

}

void MouseHitbox::Update() {
  translated_mouse_pos = this->camera->GetScreenToWorld(RMouse::GetPosition());

  this->hover = HoverHandle();
  for (int i = 0; i < 3; ++i) {
    this->click[i] = RMouse::IsButtonPressed(i);
    this->press[i] = this->click[i] && this->hover;
    this->down[i] = RMouse::IsButtonDown(i);
    this->hold[i] = this->down[i] && this->hover;
    this->release[i] = RMouse::IsButtonReleased(i);
    this->drag[i] = DragHandle(i);
  }
}
void MouseHitbox::Render() {
  this->hitbox_texture.Draw(
    { 0, 0, this->rec.width, -this->rec.height },
    this->rec.GetPosition(),
    RColor::White()
  );
}
