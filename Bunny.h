#include <gtkmm/drawingarea.h>

class Bunny {
  static constexpr double radius = 0.02;
  double m_x;
  double m_y;
  public:
  Bunny() : m_x(0.0), m_y(0.0) { }

  bool on_draw(Cairo::RefPtr<Cairo::Context> const& cr);
};
