#include "HorizontalInfoBar.hpp"


RRectangle operator+(const RRectangle & lhs, const RRectangle & rhs) {
  return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.width + rhs.width, lhs.height + rhs.height};
}
RRectangle operator-(const RRectangle & lhs, const RRectangle & rhs) {
  return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.width - rhs.width, lhs.height - rhs.height};
}


static constexpr int LINE_THICK = 2;
static constexpr int SIDE_SPACE = 100;
static constexpr int UP_SPACE = 20;

static int width;
static RRectangle bar_rec;
static RRectangle tab_rec;


void HorizontalInfoBar::RecsUpdate() const {
  width = Game::Instance().window->GetWidth();
  bar_rec = RRectangle{0, this->pos_y, static_cast<float>(width), BAR_HEIGHT};
  tab_rec = RRectangle{static_cast<float>(width/2 - SIDE_SPACE), this->pos_y - UP_SPACE, static_cast<float>(SIDE_SPACE*2), UP_SPACE + 10};
}


HorizontalInfoBar::HorizontalInfoBar(const RColor bg_color, const RColor outline_color): mouse_hitbox() {
  this->bg_color = bg_color;
  this->outline_color = outline_color;
}
void HorizontalInfoBar::Init() {
  auto height = static_cast<float>(Game::Instance().window->GetHeight());

  this->active_pos_y = height-BAR_HEIGHT;
  this->rest_pos_y = this->pos_y = height;

  RecsUpdate();
  this->mouse_hitbox = MouseHitbox(this->camera, tab_rec - RRectangle(0, 0, 0, 10 - LINE_THICK), {});
  this->mouse_hitbox.Init();
}

void HorizontalInfoBar::Enter() {
  this->mouse_hitbox.Enter();
}
void HorizontalInfoBar::Leave() {
  this->mouse_hitbox.Leave();
}

void HorizontalInfoBar::Update() {
  this->mouse_hitbox.Update();
  this->mouse_hitbox.SetPosition(tab_rec.GetPosition());

  if (Game::Instance().window->IsResized())
    RecsUpdate();

  if (this->mouse_hitbox.press[MOUSE_BUTTON_LEFT])
    this->active = !this->active;

  float time = 20 * Game::Instance().window->GetFrameTime();

  if (this->active)
    this->pos_y = std::lerp(this->pos_y, this->active_pos_y, time);
  else {
    this->pos_y = std::lerp(this->pos_y, this->rest_pos_y, time);
  }
}
void HorizontalInfoBar::Render() {
  RecsUpdate();

  tab_rec.DrawRoundedLines(0.4, 10, LINE_THICK, this->outline_color);
  bar_rec.Draw(this->bg_color);
  (bar_rec + RRectangle(-LINE_THICK, 0, LINE_THICK * 2, LINE_THICK)).DrawLines(this->outline_color, LINE_THICK);
  tab_rec.DrawRounded(0.4, 10, this->bg_color);
  this->mouse_hitbox.Render();
}
