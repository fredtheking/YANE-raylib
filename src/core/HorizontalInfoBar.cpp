#include "HorizontalInfoBar.hpp"


RRectangle operator+(const RRectangle & lfs, const RRectangle & rhs) {
  return {lfs.x + rhs.x, lfs.y + rhs.y, lfs.width + rhs.width, lfs.height + rhs.height};
}


HorizontalInfoBar::HorizontalInfoBar(const RColor bg_color, const RColor outline_color) {
  this->bg_color = bg_color;
  this->outline_color = outline_color;
}
void HorizontalInfoBar::Init() {
  auto height = static_cast<float>(Game::Instance().window->GetHeight());

  this->active_pos_y = height-BAR_HEIGHT;
  this->rest_pos_y = this->pos_y = height;
}

void HorizontalInfoBar::Enter() {

}
void HorizontalInfoBar::Leave() {

}

void HorizontalInfoBar::Update() {
  if (RKeyboard::IsKeyPressed(KEY_SPACE))
    this->active = !this->active;

  float time = 20 * Game::Instance().window->GetFrameTime();

  if (this->active)
    this->pos_y = std::lerp(this->pos_y, this->active_pos_y, time);
  else {
    this->pos_y = std::lerp(this->pos_y, this->rest_pos_y, time);
  }
}
void HorizontalInfoBar::Render() {
  static constexpr int LINE_THICK = 2;
  static constexpr int SIDE_SPACE = 100;
  static constexpr int UP_SPACE = 20;

  int width = Game::Instance().window->GetWidth();
  RRectangle bar_rec = {0, this->pos_y, static_cast<float>(width), BAR_HEIGHT};
  RRectangle tab_rec = {static_cast<float>(width/2 - SIDE_SPACE), this->pos_y - UP_SPACE, static_cast<float>(SIDE_SPACE*2), UP_SPACE + 10};

  tab_rec.DrawRoundedLines(0.4, 10, LINE_THICK, this->outline_color);
  bar_rec.Draw(this->bg_color);
  (bar_rec + RRectangle(-LINE_THICK, 0, LINE_THICK * 2, LINE_THICK)).DrawLines(this->outline_color, LINE_THICK);
  tab_rec.DrawRounded(0.4, 10, this->bg_color);
}
