#include "MouseHitbox.hpp"
#include <algorithm>

bool OverlayHoverHandle(MouseHitbox* self) {
  RVector2 mouse_pos = RMouse::GetPosition();

  bool first = self->rec.CheckCollision(mouse_pos);
  bool second = std::ranges::none_of(self->exclude_recs, [mouse_pos](const RRectangle& r) { return r.CheckCollision(mouse_pos); });

  return first && second;
}
bool CameraHoverHandle(MouseHitbox* self) {
  RVector2 mouse_pos = self->camera->GetScreenToWorld(RMouse::GetPosition());
  RRectangle determined_rec = {
    self->camera->GetScreenToWorld(self->rec.GetPosition()),
    self->camera->GetScreenToWorld(self->rec.GetSize())
  };

  bool first = determined_rec.CheckCollision(mouse_pos);
  bool second = std::ranges::none_of(self->exclude_recs, [self, mouse_pos](const RRectangle& r) {
    RRectangle determined_ex_rec = {
        self->camera->GetScreenToWorld(self->rec.GetPosition()),
        self->camera->GetScreenToWorld(self->rec.GetSize())
      };

    return determined_ex_rec.CheckCollision(mouse_pos);
  });

  return first && second;
}


bool MouseHitbox::DragHandle(int i) const {
  if (!this->drag[i] && this->press[i]) return true;
  if (this->drag[i] && !this->down[i]) return false;
  return this->drag[i];
}
void OverlayHitboxTextureUpdate(MouseHitbox* self) {
  if (self->hitbox_texture.IsValid()) {
    self->hitbox_texture.Unload();
  }

  RImage temp_image = RImage::Color(self->rec.width, self->rec.height, RColor::Red().Fade(0.3));

  for (const RRectangle& rex : self->exclude_recs) {
    RRectangle localEx = {
      rex.x - self->rec.x,
      rex.y - self->rec.y,
      rex.width,
      rex.height
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
    self->camera->GetScreenToWorld(self->rec.GetPosition()),
    self->camera->GetScreenToWorld(self->rec.GetSize())
  };

  RImage temp_image = RImage::Color(determined_rec.width, determined_rec.height, RColor::Red().Fade(0.3));

  for (const RRectangle& rex : self->exclude_recs) {
    RRectangle determined_ex_rec = {
      self->camera->GetScreenToWorld(rex.GetPosition()),
      self->camera->GetScreenToWorld(rex.GetSize())
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
  self->hitbox_texture.Draw(
    { 0, 0, self->rec.width, -self->rec.height },
    self->rec.GetPosition(),
    RColor::White()
  );
}
void CameraRender(MouseHitbox* self) {
  RRectangle determined_rec = {
    self->camera->GetScreenToWorld(self->rec.GetPosition()),
    self->camera->GetScreenToWorld(self->rec.GetSize())
  };

  self->hitbox_texture.Draw(
    { 0, 0, determined_rec.width, -determined_rec.height },
    determined_rec.GetPosition(),
    RColor::White()
  );
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
  this->DeterminedRender(this);
}
