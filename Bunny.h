#include <gtkmm/drawingarea.h>

class Bunny {
  static constexpr float radius = 0.005;
  float m_x;
  float m_y;
  public:
  Bunny() : m_x(0.0), m_y(0.0) { }

  bool on_draw(Cairo::RefPtr<Cairo::Context> const& cr);
};
