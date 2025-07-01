#include "MouseHitbox.hpp"
#include <algorithm>

#include "../Game.hpp"

#define s_to_w(vec2) (this->camera->GetScreenToWorld(vec2))
#define s_to_w(self, vec2) (self->camera->GetScreenToWorld(vec2))
#define w_to_s(vec2) (this->camera->GetWorldToScreen(vec2))
#define w_to_s(self, vec2) (self->camera->GetWorldToScreen(vec2))

bool OverlayHoverHandle(MouseHitbox* self) {
  RVector2 mouse_pos = RMouse::GetPosition();

  bool first = self->rec.CheckCollision(mouse_pos);
  bool second = std::ranges::none_of(self->exclude_recs, [self, mouse_pos](const RRectangle& rex) {
    RRectangle determined_ex_rec = {
        self->rec.GetPosition() + rex.GetPosition(),
        rex.GetSize()
    };

    return determined_ex_rec.CheckCollision(mouse_pos);
  });

  return first && second;
}
bool CameraHoverHandle(MouseHitbox* self) {
  RVector2 mouse_pos = s_to_w(self, RMouse::GetPosition());
  RRectangle determined_rec = {
    s_to_w(self, self->rec.GetPosition()),
    s_to_w(self, self->rec.GetSize())
  };

  bool first = determined_rec.CheckCollision(mouse_pos);
  bool second = std::ranges::none_of(self->exclude_recs, [self, mouse_pos, determined_rec](const RRectangle& rex) {
    RRectangle determined_ex_rec = {
        determined_rec.GetPosition() + s_to_w(self, rex.GetPosition()),
        s_to_w(self, rex.GetSize())
    };

    return determined_ex_rec.CheckCollision(mouse_pos);
  });

  return first && second;
}

void OverlayHitboxTextureUpdate(MouseHitbox* self) {
  if (self->hitbox_texture.IsValid()) {
    self->hitbox_texture.Unload();
  }

  RImage temp_image = RImage::Color(self->rec.width, self->rec.height, RColor::Red().Fade(0.3));

  for (const RRectangle& rex : self->exclude_recs) {
    RRectangle determined_ex_rec = {
      self->rec.GetPosition() + rex.GetPosition(),
      rex.GetSize()
    };

    RRectangle localEx = {
      determined_ex_rec.x - self->rec.x,
      determined_ex_rec.y - self->rec.y,
      determined_ex_rec.width,
      determined_ex_rec.height
    };
    temp_image.DrawRectangle(localEx, RColor::Blank());
  }

  RTexture2D texture = RTexture2D(temp_image);
  temp_image.Unload();
  self->hitbox_texture = std::move(texture);
}
void CameraHitboxTextureUpdate(MouseHitbox* self) {
  if (self->hitbox_texture.IsValid()) {
    self->hitbox_texture.Unload();
  }

  RRectangle determined_rec = {
    s_to_w(self, self->rec.GetPosition()),
    s_to_w(self, self->rec.GetSize())
  };

  RImage temp_image = RImage::Color(determined_rec.width, determined_rec.height, RColor::Red().Fade(0.3));

  for (const auto& rex : self->exclude_recs) {
    RRectangle determined_ex_rec = {
      determined_rec.GetPosition() + s_to_w(self, rex.GetPosition()),
      s_to_w(self, rex.GetSize())
    };

    RRectangle localEx = {
      determined_ex_rec.x - determined_rec.x,
      determined_ex_rec.y - determined_rec.y,
      determined_ex_rec.width,
      determined_ex_rec.height
    };
    temp_image.DrawRectangle(localEx, RColor::Blank());
  }

  RTexture2D texture = RTexture2D(temp_image);
  temp_image.Unload();
  self->hitbox_texture = std::move(texture);
}

void OverlayRender(MouseHitbox* self) {
  RVector2 determined_pos = self->rec.GetPosition();

  self->hitbox_texture.Draw(determined_pos, RColor::White());
}
void CameraRender(MouseHitbox* self) {
  RVector2 determined_pos = s_to_w(self, self->rec.GetPosition());

  self->hitbox_texture.Draw(determined_pos, RColor::White());
}



bool MouseHitbox::DragHandle(int i) const {
  if (!this->drag[i] && this->press[i]) return true;
  if (this->drag[i] && !this->down[i]) return false;
  return this->drag[i];
}

void MouseHitbox::SetPosition(const RVector2 position) {
  this->rec.SetPosition(position);
}

MouseHitbox::MouseHitbox(const RCamera2D* camera, const RRectangle rec, const std::vector<RRectangle>& exclude_recs, bool overlay) {
  this->camera = camera;
  this->rec = rec;
  this->exclude_recs = exclude_recs;
  this->overlay = overlay;

  if (overlay) {
    this->DeterminedHoverHandle = OverlayHoverHandle;
    this->DeterminedHitboxTextureUpdate = OverlayHitboxTextureUpdate;
    this->DeterminedRender = OverlayRender;
  } else {
    this->DeterminedHoverHandle = CameraHoverHandle;
    this->DeterminedHitboxTextureUpdate = CameraHitboxTextureUpdate;
    this->DeterminedRender = CameraRender;
  }
}
void MouseHitbox::Init() {
  this->DeterminedHitboxTextureUpdate(this);
}

void MouseHitbox::Enter() {

}
void MouseHitbox::Leave() {

}

void MouseHitbox::Update() {
  this->hover = this->DeterminedHoverHandle(this);
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
  if (Game::Instance().debug_mode)
    this->DeterminedRender(this);
}
