#pragma once

#include "clock.h"
#include "debug.h"
#include "statefultask/AIEngine.h"
#include <gtkmm/drawingarea.h>
#include <algorithm>

//forward declaration
class MyArea;

struct Pos{
  double x;
  double y;
  public:
  double getx() {return x;}
  double gety() {return y;}
  double setx(double value) {return x = value;}
  double sety(double value) {return y = value;}
  double addx(double value) {return x += value;}
  double addy(double value) {return y += value;}
  void clamp(double radius) 
  {
    x = std::max(radius, std::min(x, 1.0 - radius));
    y = std::max(radius, std::min(y, 1.0 - radius));
  }
};

// Bunnies live in a pen of size 1.0 by 1.0,
// with the origin in the bottom-left.
class Bunny : public AIStatefulTask {
  using pos_t = aithreadsafe::Wrapper<Pos, aithreadsafe::policy::Primitive<AIMutex>>;
  MyArea& m_area;
  double m_radius;
  pos_t pos;
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
      m_area(area), m_pattern(Cairo::SolidPattern::create_rgb(1.0, 0.0, 0.0))
  {
    m_radius = (rand() % 3 + 1) / 100.0;
    pos_t::wat pos_w(pos);
    pos_w->clamp(m_radius);
  }

  void clamp(pos_t::wat pos_w)
  {
    pos_w->setx(std::max(m_radius, std::min(pos_w->getx(), 1.0 - m_radius)));
    pos_w->sety(std::max(m_radius, std::min(pos_w->gety(), 1.0 - m_radius)));
  }

  bool on_draw(Cairo::RefPtr<Cairo::Context> const& cr, time_point const& time);
};
