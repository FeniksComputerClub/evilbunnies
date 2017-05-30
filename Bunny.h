#include "clock.h"
#include "debug.h"
#include "statefultask/AIEngine.h"
#include <gtkmm/drawingarea.h>
#include <algorithm>

// Bunnies live in a pen of size 1.0 by 1.0,
// with the origin in the bottom-left.
class Bunny : public AIStatefulTask {
  double m_radius;
  double m_x;
  double m_y;
  Cairo::RefPtr<Cairo::Pattern> m_pattern;

  //statefultask
  using direct_base_type = AIStatefulTask;
  enum design_state_type {
    Task_start = direct_base_type::max_state,
    Task_done,
  };
  char const* state_str_impl(state_type run_state) const override;
  void multiplex_impl(state_type run_state) override;

  public:
  Bunny() :
      AIStatefulTask(DEBUG_ONLY(true)),
      m_radius(0.02), m_x(0.0), m_y(0.0), m_pattern(Cairo::SolidPattern::create_rgb(1.0, 0.0, 0.0))
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
