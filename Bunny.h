#include <gtkmm/drawingarea.h>
#include "clock.h"
#include <algorithm>

// Bunnies live in a pen of size 1.0 by 1.0,
// with the origin in the bottom-left.
class Bunny {
  double m_radius;
  double m_x;
  double m_y;
  Cairo::RefPtr<Cairo::Pattern> m_pattern;

  public:
  Bunny() : m_radius(0.02), m_x(0.0), m_y(0.0), m_pattern(Cairo::SolidPattern::create_rgb(1.0, 0.0, 0.0))
  {
    clamp();
  }

  void clamp()
  {
    m_x = std::max(m_radius, std::min(m_x, 1.0 - m_radius));
    m_y = std::max(m_radius, std::min(m_y, 1.0 - m_radius));
  }

  bool on_draw(Cairo::RefPtr<Cairo::Context> const& cr, time_point const& time);
};
