#include "sys.h"
#include "Bunny.h"
#include "MyArea.h"
#include <thread>
#include <chrono>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

bool Bunny::on_draw(Cairo::RefPtr<Cairo::Context> const& cr, time_point const& /*time*/)
{
  //lock pos
  pos_t::wat pos_w(pos);

  cr->set_source(m_pattern);
  cr->arc(pos_w->getx(), pos_w->gety(), m_radius, 0.0, 2 * M_PI);
  cr->close_path()
  cr->fill_preserve();
  return true;
}

char const* Bunny::state_str_impl(state_type run_state) const
{
  switch(run_state)
  {
    AI_CASE_RETURN(start);
    AI_CASE_RETURN(move_right);
    AI_CASE_RETURN(move_left);
    AI_CASE_RETURN(done);
  }
  return "UNKNOWN";
}

void Bunny::multiplex_impl(state_type run_state)
{
  //lock pos
  pos_t::wat pos_w(pos);
  const double increment = 0.01;
  double previousx;
  switch(run_state)
  {
    case start:
      pos_w->addx((rand() % 100 + 1) / 100.0);
      set_state(move_right);
    case move_right:
      pos_w->addx(increment);
      previousx = pos_w->getx();
      pos_w->clamp(m_radius);
      if (pos_w->getx() != previousx){
        pos_w->addy(m_radius * 2);
        pos_w->clamp(m_radius);
        set_state(move_left);
      }
      wait(1);
      break;
    case move_left:
      pos_w->addx(0 - increment);
      previousx = pos_w->getx();
      pos_w->clamp(m_radius);
      if (pos_w->getx() != previousx){
        pos_w->addy(m_radius * 2);
        pos_w->clamp(m_radius);
        set_state(move_right);
      }
      wait(1);
      break;
    case done:
      finish();
      break;
  }
  m_area.queue_draw();
}
