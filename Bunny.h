#pragma once

#include "clock.h"
#include "debug.h"
#include "statefultask/AIEngine.h"
#include <gtkmm/drawingarea.h>
#include <algorithm>

//forward declaration
class MyArea;

class Pos {
  private:
    double x;
    double y;

  public:
    Pos() {}
    Pos(Pos const& copy) : x(copy.getx()), y(copy.gety()) {}
    Pos(double const& newx, double const& newy) : x(newx), y(newy) {}
    Pos get() const { return Pos(*this); }
    double getx() const { return x; }
    double gety() const { return y; }
    double setx(double value) { return x = value; }
    double sety(double value) { return y = value; }
    double addx(double value) { return x += value; }
    double addy(double value) { return y += value; }
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
  pos_t pos;
  double m_radius;
  double m_deltax;
  double m_deltay;
  double m_speed;
  MyArea& m_area;
  Cairo::RefPtr<Cairo::Pattern> m_pattern;

  //statefultask
  using direct_base_type = AIStatefulTask;
  enum design_state_type {
    start = direct_base_type::max_state,
    change,
    move,
    done,
  };
  char const* state_str_impl(state_type run_state) const override;
  void multiplex_impl(state_type run_state) override;

  public:
  Bunny(MyArea& area) :
      AIStatefulTask(DEBUG_ONLY(false)),
      m_speed(0.05), m_area(area), m_pattern(Cairo::SolidPattern::create_rgb(1.0, 0.0, 0.0))
  {
    m_radius = (rand() % 3 + 1) / 100.0;
    pos_t::wat pos_w(pos);
    pos_w->clamp(m_radius);
  }

  bool is_in(pos_t::rat const& pos_r, Pos const& minpos = Pos(0.0, 0.0), Pos const& maxpos = Pos(1.0, 1.0)) const
  {
    return minpos.getx() + m_radius < pos_r->getx() && pos_r->getx() < maxpos.getx() - m_radius &&
           minpos.gety() + m_radius < pos_r->gety() && pos_r->gety() < maxpos.gety() - m_radius;
  }

  Pos get_pos()
  {
    pos_t::rat pos_r(pos);
    return *pos_r;
  }

  bool on_draw(Cairo::RefPtr<Cairo::Context> const& cr, time_point const& time);
};
