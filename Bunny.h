#pragma once

#include "clock.h"
#include "debug.h"
#include "statefultask/AIEngine.h"
#include <gtkmm/drawingarea.h>
#include <algorithm>

//forward declaration
class MyArea;

// Bunnies live in a pen of size 1.0 by 1.0,
// with the origin in the bottom-left.
class Bunny : public AIStatefulTask {
  MyArea& m_area;
  double m_radius;
  double m_x;
  double m_y;
  Cairo::RefPtr<Cairo::Pattern> m_pattern;

  //statefultask
  using direct_base_type = AIStatefulTask;
  enum design_state_type {
    start = direct_base_type::max_state,
    move_right,
    move_left,
    done,
  };
  char const* state_str_impl(state_type run_state) const override;
  void multiplex_impl(state_type run_state) override;

  public:
  Bunny(MyArea& area) :
      AIStatefulTask(DEBUG_ONLY(false)),
      m_area(area), m_radius(0.02), m_x(0.0), m_y(0.0), m_pattern(Cairo::SolidPattern::create_rgb(1.0, 0.0, 0.0))
  {
    clamp(m_x, m_y);
  }

  void clamp(double& x, double& y)
  {
    x = std::max(m_radius, std::min(x, 1.0 - m_radius));
    y = std::max(m_radius, std::min(y, 1.0 - m_radius));
  }

  bool on_draw(Cairo::RefPtr<Cairo::Context> const& cr, time_point const& time);
};
